// Copyright 2019 David Johnston

// According to the JVMTI documentation, Java native agents are linked into a
// JVM in one of two ways: dynamically or statically. This file defines
// agent's lifetime functions for dynamically linked
//
// Defines the dynamically linked tracelogger agent.

#include "jni.h"     // NOLINT

#include "phasicj/tracelogger/agent_static.h"

extern "C"
JNIEXPORT
jint Agent_OnLoad(JavaVM *vm, char *options,
                                       void *reserved) {
  return Agent_OnLoad_pjtracelogger(vm, options, reserved);
}

extern "C"
JNIEXPORT
jint Agent_OnAttach(JavaVM *vm, char *options, void *reserved) {
  return Agent_OnAttach_pjtracelogger(vm, options, reserved);
}

extern "C"
JNIEXPORT
void Agent_OnUnload(JavaVM *vm) {
  return Agent_OnUnload_pjtracelogger(vm);
}
