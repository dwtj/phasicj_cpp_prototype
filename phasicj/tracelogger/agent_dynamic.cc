// Copyright 2019 David Johnston

// Defines callback shims from a dynamically linked agent to the tracelogger
// agent implementation.

#include <type_traits>

#include "jni.h"     // NOLINT

#include "phasicj/tracelogger/agent.h"

namespace phasicj::tracelogger::agent_dynamic {

// [See](https://google.github.io/styleguide/cppguide.html#Static_and_Global_Variables)
static_assert(std::is_trivially_destructible<Agent>::value);
phasicj::tracelogger::Agent AGENT;

}

extern "C"
JNIEXPORT
jint Agent_OnLoad(JavaVM *vm, char *options, void *reserved) {
  return phasicj::tracelogger::agent_dynamic::AGENT.OnLoad(vm, options,
                                                           reserved);
}

extern "C"
JNIEXPORT
jint Agent_OnAttach(JavaVM *vm, char *options, void *reserved) {
  return phasicj::tracelogger::agent_dynamic::AGENT.OnAttach(vm, options,
                                                             reserved);
}

extern "C"
JNIEXPORT
void Agent_OnUnload(JavaVM *vm) {
  return phasicj::tracelogger::agent_dynamic::AGENT.OnUnload(vm);
}
