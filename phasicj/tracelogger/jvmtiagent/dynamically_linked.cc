// Copyright 2019 David Johnston

#include <iostream>
#include <stdexcept>
#include <string>

#include "boost/log/trivial.hpp"
#include "jni.h"  // NOLINT(build/include_subdir)

#include "google/protobuf/stubs/common.h"

#include "phasicj/tracelogger/jvmtiagent/lifetime_event_callbacks.h"

extern "C" JNIEXPORT jint Agent_OnLoad(JavaVM* jvm,
                                       char* options,
                                       void* reserved) {
  return ::phasicj::tracelogger::jvmtiagent::OnLoad(jvm, options, reserved);
}

extern "C" JNIEXPORT jint Agent_OnAttach(JavaVM *vm, char *options,
                                         void *reserved) {
  return ::phasicj::tracelogger::jvmtiagent::OnAttach(vm, options, reserved);
}

extern "C" JNIEXPORT void Agent_OnUnload(JavaVM* vm) {
  return ::phasicj::tracelogger::jvmtiagent::OnUnload(vm);
}
