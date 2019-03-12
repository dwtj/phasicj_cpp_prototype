// Copyright 2019 David Johnston

#include <iostream>
#include <stdexcept>
#include <string>

#include "jni.h"  // NOLINT(build/include_subdir)

#include "phasicj/tracelogger/core/agent.h"
#include "phasicj/tracelogger/linkage/dynamic.h"

extern "C" JNIEXPORT jint Agent_OnLoad(JavaVM* jvm,
                                       char* options,
                                       void* reserved) {
  return ::phasicj::tracelogger::core::Agent::OnLoad(*jvm, options);
}

extern "C" JNIEXPORT jint Agent_OnAttach(JavaVM *vm, char *options,
                                         void *reserved) {
  return ::phasicj::tracelogger::core::Agent::OnAttach(*vm, options);
}

extern "C" JNIEXPORT void Agent_OnUnload(JavaVM* vm) {
  ::phasicj::tracelogger::core::Agent::OnUnload(*vm);
}
