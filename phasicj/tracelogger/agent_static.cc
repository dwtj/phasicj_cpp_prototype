// Copyright 2019 David Johnston

// Defines callback shims from a statically linked agent to a tracelogger
// agent instance accessed via a namespaced global variable.

#include <iostream>
#include <type_traits>

#include "jni.h"  // NOLINT(build/include_subdir)

#include "phasicj/tracelogger/agent.h"
#include "phasicj/tracelogger/agent_static.h"

namespace phasicj::tracelogger::agent_static {

static Agent AGENT;

}  // namespace phasicj::tracelogger::agent_static

extern "C" JNIEXPORT jint Agent_OnLoad_pjtracelogger(JavaVM *vm, char *options,
                                                     void *reserved) {
  jint ret{phasicj::tracelogger::agent_static::AGENT.OnAttach(vm, options,
                                                              reserved)};
  return ret;
}

extern "C" JNIEXPORT jint Agent_OnAttach_pjtracelogger(JavaVM *vm,
                                                       char *options,
                                                       void *reserved) {
  jint ret{phasicj::tracelogger::agent_static::AGENT.OnAttach(vm, options,
                                                              reserved)};
  return ret;
}

extern "C" JNIEXPORT void Agent_OnUnload_pjtracelogger(JavaVM *vm) {
  phasicj::tracelogger::agent_static::AGENT.OnUnload(vm);
  return;
}
