// Copyright 2019 David Johnston

// Callbacks which start/stop the tracelogger JVMTI agent when it is statically
// linked into the JVM.

#include <iostream>
#include <stdexcept>
#include <string>

#include "jni.h"  // NOLINT(build/include_subdir)

#include "boost/log/trivial.hpp"

#include "phasicj/tracelogger/jvmtiagent/statically_linked.h"
#include "phasicj/tracelogger/jvmtiagent/lifetime_event_callbacks.h"

extern "C" JNIEXPORT jint Agent_OnLoad_pjtracelogger(JavaVM* jvm,
                                                     char* options,
                                                     void* reserved) {
  return ::phasicj::tracelogger::jvmtiagent::OnLoad(jvm, options, reserved);
}

extern "C" JNIEXPORT jint Agent_OnAttach_pjtracelogger(JavaVM* jvm,
                                                       char* options,
                                                       void* reserved) {
  return ::phasicj::tracelogger::jvmtiagent::OnAttach(jvm, options, reserved);
}

extern "C" JNIEXPORT void Agent_OnUnload_pjtracelogger(JavaVM* jvm) {
  ::phasicj::tracelogger::jvmtiagent::OnUnload(jvm);
}
