// Copyright 2019 David Johnston



#include "phasicj/tracelogger/jvmtiagent/lifetime_event_callbacks.h"
#include <stdexcept>
#include <string>

#include "boost/log/trivial.hpp"
#include "jni.h"  // NOLINT(build/include_subdir)

#include "google/protobuf/stubs/common.h"

namespace phasicj::tracelogger::jvmtiagent {

  using ::std::endl;
  using ::std::runtime_error;
  using ::std::string;
  using ::std::unique_ptr;

  // https://docs.oracle.com/en/java/javase/11/docs/specs/jvmti.html#onload
  jint OnLoad(JavaVM* jvm, char* options, void* reserved) {
    BOOST_LOG_TRIVIAL(info) << "JVM called Agent_OnLoad().";
    BOOST_LOG_TRIVIAL(info) << "Instantiating a new JVMTI agent instance...";
    // TODO(dwtj): Everything
    // WIP(dwtj): Removing Agent
//    auto agent = Agent::NewFromOnLoad(jvm, options, reserved);
//    if (!agent) {
//    BOOST_LOG_TRIVIAL(info) << "Failed to instantiate an agent.";
//    return JNI_EVERSION;  // NB(dwtj): JVM will be killed.
//    }

    BOOST_LOG_TRIVIAL(info) << "Verifying Protobuf version...";
    GOOGLE_PROTOBUF_VERIFY_VERSION;
    BOOST_LOG_TRIVIAL(info) << "Protobuf version verified.";

    return JNI_OK;
  }

  jint OnAttach(JavaVM *vm, char *options, void *reserved) {
    BOOST_LOG_TRIVIAL(info) << "JVM called Agent_OnAttach().";
    return JNI_ERR;  // Initialization with `OnAttach()` not yet supported.
  }

  void OnUnload(JavaVM* vm) {
    BOOST_LOG_TRIVIAL(info) << "JVM called Agent_OnUnload().";
    BOOST_LOG_TRIVIAL(info) << "Shutting down protobuf library.";
    google::protobuf::ShutdownProtobufLibrary();
  }

}  // namespace phasicj::tracelogger::jvmtiagent
