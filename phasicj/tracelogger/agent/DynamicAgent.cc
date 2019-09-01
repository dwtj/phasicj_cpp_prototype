// Copyright 2019 David Johnston

#include "boost/log/trivial.hpp"

#include "jni.h"  // NOLINT(build/include_subdir)

#include "phasicj/tracelogger/agent/Agent.h"

using ::phasicj::tracelogger::agent::OnLoad;
using ::phasicj::tracelogger::agent::OnAttach;
using ::phasicj::tracelogger::agent::OnUnload;

extern "C" JNIEXPORT jint Agent_OnLoad(JavaVM* jvm,
                                       char* options,
                                       void* reserved) {
  BOOST_LOG_TRIVIAL(info)
    << "JVM starting PhasicJ Trace Logger agent via `Agent_OnLoad()`...";
  return OnLoad(*jvm, options);
}

extern "C" JNIEXPORT jint Agent_OnAttach(JavaVM *vm, char *options,
                                         void *reserved) {
  BOOST_LOG_TRIVIAL(info)
    << "JVM starting PhasicJ Trace Logger agent via `Agent_OnAttach()`...";
  return OnAttach(*vm, options);
}

extern "C" JNIEXPORT void Agent_OnUnload(JavaVM* vm) {
  BOOST_LOG_TRIVIAL(info)
    << "JVM stopping PhasicJ Trace Logger agent via `Agent_OnUnload()`...";
  OnUnload(*vm);
}
