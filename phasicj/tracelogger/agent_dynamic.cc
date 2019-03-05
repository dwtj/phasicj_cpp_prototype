// Copyright 2019 David Johnston

// Defines callback shims from a dynamically linked agent to a tracelogger
// agent instance accessed via a namespaced global variable.

#include <iostream>
#include <stdexcept>
#include <string>

#include "boost/log/trivial.hpp"
#include "jni.h"  // NOLINT(build/include_subdir)

#include "google/protobuf/stubs/common.h"

#include "phasicj/tracelogger/agent.h"

using std::endl;
using std::runtime_error;
using std::string;
using std::unique_ptr;

using phasicj::tracelogger::Agent;

namespace phasicj::tracelogger::agent_dynamic {
Agent* AGENT;
}  // namespace phasicj::tracelogger::agent_dynamic

using phasicj::tracelogger::agent_dynamic::AGENT;

// https://docs.oracle.com/en/java/javase/11/docs/specs/jvmti.html#onload
extern "C" JNIEXPORT jint Agent_OnLoad(JavaVM* jvm,
                                       char* options,
                                       void* reserved) {
  BOOST_LOG_TRIVIAL(info) << "JVM called Agent_OnLoad().";
  BOOST_LOG_TRIVIAL(info) << "Instantiating a new agent instance.";
  auto agent = Agent::NewFromOnLoad(jvm, options, reserved);
  if (!agent) {
    BOOST_LOG_TRIVIAL(info) << "Failed to instantiate a compatible agent.";
    return JNI_EVERSION;  // NB(dwtj): JVM will be killed.
  }

  AGENT = agent.value();

  BOOST_LOG_TRIVIAL(info) << "Verifying Protobuf version.";
  GOOGLE_PROTOBUF_VERIFY_VERSION;
  BOOST_LOG_TRIVIAL(info) << "Protobuf version verified.";

  return JNI_OK;
}

extern "C" JNIEXPORT jint Agent_OnAttach(JavaVM *vm, char *options,
                                         void *reserved) {
  BOOST_LOG_TRIVIAL(info) << "JVM called Agent_OnAttach().";
  return JNI_ERR;  // Initialization with `OnAttach()` not yet supported.
}

extern "C" JNIEXPORT void Agent_OnUnload(JavaVM* vm) {
  BOOST_LOG_TRIVIAL(info) << "JVM called Agent_OnUnload().";
  delete AGENT;

  BOOST_LOG_TRIVIAL(info) << "Shutting down protobuf library.";
  google::protobuf::ShutdownProtobufLibrary();
}
