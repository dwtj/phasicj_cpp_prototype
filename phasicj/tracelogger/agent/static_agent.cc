// Copyright 2019 David Johnston

#include "jni.h"  // NOLINT(build/include_subdir)

#include "boost/log/trivial.hpp"

#include "phasicj/tracelogger/agent/agent.h"

using ::phasicj::tracelogger::agent::OnLoad;
using ::phasicj::tracelogger::agent::OnAttach;
using ::phasicj::tracelogger::agent::OnUnload;

extern "C" JNIEXPORT jint Agent_OnLoad_pjtracelogger(JavaVM* jvm,
                                                     char* options,
                                                     void* reserved) {
  BOOST_LOG_TRIVIAL(info)
    << "JVM starting agent via `Agent_OnLoad_pjtracelogger()`";
  return OnLoad(*jvm, options);
}

extern "C" JNIEXPORT jint Agent_OnAttach_pjtracelogger(JavaVM* jvm,
                                                       char* options,
                                                       void* reserved) {
  BOOST_LOG_TRIVIAL(info)
      << "JVM starting agent via Agent_OnLoad_pjtracelogger";
  return OnAttach(*jvm, options);
}

extern "C" JNIEXPORT void Agent_OnUnload_pjtracelogger(JavaVM* jvm) {
  BOOST_LOG_TRIVIAL(info)
      << "JVM stopping agent via Agent_OnLoad_pjtracelogger";
  OnUnload(*jvm);
}
