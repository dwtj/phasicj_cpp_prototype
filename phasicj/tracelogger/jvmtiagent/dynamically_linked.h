// Copyright 2019 David Johnston

// Callbacks which start/stop the tracelogger JVMTI agent when it is dynamically
// linked into the JVM.

#ifndef PHASICJ_TRACELOGGER_AGENT_DYNAMIC_H_
#define PHASICJ_TRACELOGGER_AGENT_DYNAMIC_H_

#include "jni.h"  // NOLINT(build/include_subdir)

#include "phasicj/tracelogger/agent.h"

extern "C" JNIEXPORT jint Agent_OnLoad(JavaVM *vm, char *options,
                                       void *reserved);

extern "C" JNIEXPORT jint Agent_OnAttach(JavaVM *vm, char *options,
                                         void *reserved);

extern "C" JNIEXPORT void Agent_OnUnload(JavaVM *vm);

#endif  // PHASICJ_TRACELOGGER_AGENT_DYNAMIC_H_
