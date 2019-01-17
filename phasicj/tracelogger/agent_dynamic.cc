// Copyright 2019 David Johnston

// Defines callback shims from a dynamically linked agent to a tracelogger
// agent instance accessed via a namespaced global variable.

#include <type_traits>

#include "jni.h"  // NOLINT(build/include_subdir)

#include "phasicj/tracelogger/agent.h"

namespace phasicj {
namespace tracelogger {
namespace agent_dynamic {

static Agent AGENT;

}  // namespace agent_dynamic
}  // namespace tracelogger
}  // namespace phasicj

extern "C" JNIEXPORT jint Agent_OnLoad(JavaVM *vm, char *options,
                                       void *reserved) {
  return phasicj::tracelogger::agent_dynamic::AGENT.OnLoad(vm, options,
                                                           reserved);
}

extern "C" JNIEXPORT jint Agent_OnAttach(JavaVM *vm, char *options,
                                         void *reserved) {
  return phasicj::tracelogger::agent_dynamic::AGENT.OnAttach(vm, options,
                                                             reserved);
}

extern "C" JNIEXPORT void Agent_OnUnload(JavaVM *vm) {
  return phasicj::tracelogger::agent_dynamic::AGENT.OnUnload(vm);
}
