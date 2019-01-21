// Copyright 2019 David Johnston

// Defines callback shims from a dynamically linked agent to a tracelogger
// agent instance accessed via a namespaced global variable.

#include <optional>

#include "jni.h"  // NOLINT(build/include_subdir)

#include "phasicj/tracelogger/agent.h"

using std::optional;

namespace phasicj::tracelogger::agent_dynamic {
static optional<Agent> AGENT;
}  // namespace phasicj::tracelogger::agent_dynamic

using phasicj::tracelogger::Agent;
using phasicj::tracelogger::agent_dynamic::AGENT;

// Note(dwtj): If this returns an error code, the JVM will terminate. See:
//   https://docs.oracle.com/en/java/javase/11/docs/specs/jvmti.html#onload
extern "C" JNIEXPORT jint Agent_OnLoad(JavaVM *vm, char *options,
                                       void *reserved) {
  auto AGENT = Agent::NewFromOnLoadEvent(vm, options, reserved);
  return AGENT ? JNI_OK : JNI_ERR;
}

extern "C" JNIEXPORT jint Agent_OnAttach(JavaVM *vm, char *options,
                                         void *reserved) {
  // Note(dwtj): This agent is not yet designed to be started in the live phase.
  return JNI_ERR;
}

extern "C" JNIEXPORT void Agent_OnUnload(JavaVM* vm) { AGENT.reset(); }
