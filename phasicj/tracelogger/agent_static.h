// Copyright 2019 David Johnston

#ifndef PHASICJ_TRACELOGGER_AGENT_STATIC_H_
#define PHASICJ_TRACELOGGER_AGENT_STATIC_H_

#include "jni.h"  // NOLINT(build/include_subdir)

#include "phasicj/tracelogger/agent.h"

extern "C" JNIEXPORT jint Agent_OnLoad_pjtracelogger(JavaVM *vm, char *options,
                                                     void *reserved);

extern "C" JNIEXPORT jint Agent_OnAttach_pjtracelogger(JavaVM *vm,
                                                       char *options,
                                                       void *reserved);

extern "C" JNIEXPORT void Agent_OnUnload_pjtracelogger(JavaVM *vm);

#endif  // PHASICJ_TRACELOGGER_AGENT_STATIC_H_
