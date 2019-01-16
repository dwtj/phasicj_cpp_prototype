// Copyright 2019 David Johnston

// Defines callback shims from a statically linked agent to the tracelogger
// agent implementation.

#include <type_traits>
#include <iostream>

#include "jni.h"

#include "phasicj/tracelogger/agent.h"
#include "phasicj/tracelogger/agent_static.h"

namespace phasicj::tracelogger::agent_static {

// [See](https://google.github.io/styleguide/cppguide.html#Static_and_Global_Variables)
static_assert(std::is_trivially_destructible<Agent>::value);
Agent AGENT;

}

extern "C"
JNIEXPORT
jint Agent_OnLoad_pjtracelogger(JavaVM *vm, char *options, void *reserved) {
  jint ret {phasicj::tracelogger::agent_static::AGENT.OnAttach(vm, options,
                                                               reserved)};
  return ret;
}

extern "C"
JNIEXPORT
jint Agent_OnAttach_pjtracelogger(JavaVM* vm, char* options, void* reserved) {
  jint ret {phasicj::tracelogger::agent_static::AGENT.OnAttach(vm, options,
                                                               reserved)};
  return ret;
}

extern "C"
JNIEXPORT
void Agent_OnUnload_pjtracelogger(JavaVM *vm) {
  phasicj::tracelogger::agent_static::AGENT.OnUnload(vm);
  return;
}