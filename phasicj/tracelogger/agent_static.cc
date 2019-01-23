// Copyright 2019 David Johnston

// Defines callback shims from a statically linked agent to a tracelogger
// agent instance accessed via a namespaced global variable.

#include <iostream>
#include <stdexcept>
#include <string>

#include "jni.h"  // NOLINT(build/include_subdir)

#include "phasicj/tracelogger/agent.h"
#include "phasicj/tracelogger/agent_static.h"

using phasicj::tracelogger::Agent;

using std::cerr;
using std::endl;
using std::runtime_error;
using std::string;

namespace phasicj::tracelogger::agent_static {
static Agent* AGENT;
}  // namespace phasicj::tracelogger::agent_static

using phasicj::tracelogger::agent_static::AGENT;

// https://docs.oracle.com/en/java/javase/11/docs/specs/jvmti.html#onload
extern "C" JNIEXPORT jint Agent_OnLoad_pjtracelogger(JavaVM* jvm,
                                                     char* options,
                                                     void* reserved) {
  try {
    AGENT = new Agent{*jvm, string{options}};
    return JNI_OK;
  } catch (runtime_error& ex) {
    // NB(dwtj): The JVM will be killed.
    cerr << "Failed to start PhasicJ TraceLogger Agent: " << ex.what() << endl;
    return JNI_EVERSION;
  }
}

extern "C" JNIEXPORT jint Agent_OnAttach_pjtracelogger(JavaVM *vm,
                                                       char *options,
                                                       void *reserved) {
  // Note(dwtj): This agent is not yet designed to be started in the live phase.
  return JNI_ERR;
}

extern "C" JNIEXPORT void Agent_OnUnload_pjtracelogger(JavaVM *vm) {
  delete AGENT;
}
