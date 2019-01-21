// Copyright 2019 David Johnston

// Defines callback shims from a dynamically linked agent to a tracelogger
// agent instance accessed via a namespaced global variable.

#include <type_traits>

#include "jni.h"  // NOLINT(build/include_subdir)

#include "phasicj/tracelogger/agent.h"

namespace phasicj::tracelogger::agent_dynamic {
static Agent* AGENT = nullptr;
}  // namespace phasicj::tracelogger::agent_dynamic

using phasicj::tracelogger::Agent;
using phasicj::tracelogger::agent_dynamic::AGENT;

// Note(dwtj): If this returns an error code, the JVM will terminate. See:
//   https://docs.oracle.com/en/java/javase/11/docs/specs/jvmti.html#onload
extern "C" JNIEXPORT jint Agent_OnLoad(JavaVM *vm, char *options,
                                       void *reserved) {
  AGENT = Agent::MaybeNewFromOnLoadEvent(vm, options, reserved);
  return AGENT == nullptr ? JNI_ERR : JNI_OK;
}

extern "C" JNIEXPORT jint Agent_OnAttach(JavaVM *vm, char *options,
                                         void *reserved) {
  // Note(dwtj): This agent is not yet designed to be started in the live phase.
  return JNI_ERR;
}

extern "C" JNIEXPORT void Agent_OnUnload(JavaVM* vm) { delete AGENT; }
