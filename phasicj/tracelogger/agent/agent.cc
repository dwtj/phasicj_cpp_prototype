// Copyright 2019 David Johnston

#include <stdexcept>
#include <mutex>

#include "boost/log/trivial.hpp"

#include "jni.h"

#include "phasicj/tracelogger/trace_logger_manager.h"
#include "phasicj/tracelogger/agent/agent.h"

namespace phasicj::tracelogger::agent {

using ::phasicj::tracelogger::TraceLoggerManager;
using ::std::runtime_error;
using ::std::optional;

namespace {
// TODO(dwtj): During construction, this may throw an exception, and because it
//  is performed during static storage initialization (i.e. before main()) it
//  cannot be caught.
TraceLoggerManager trace_logger_manager_{};
}

/// @warning The JVMTI OnLoad/OnAttach/OnUnload callbacks need to be thread
/// safe because, theoretically, a single process can contain multiple JVMs.
/// This may be rare, but it can be done (e.g. using the JNI Invocation API).
/// If within one process, more than one JVM is configured to use the PhasicJ
/// TraceLogger Agent, then this callback will be called more than once,
/// possibly with concurrent interference.
// TODO(dwtj): Consider using the `options` string.
jint OnLoad(JavaVM& jvm, const char* options) {
  trace_logger_manager_.Install(jvm, {});

  try {
    // TODO(dwtj)
    return JNI_OK;
  } catch (runtime_error& ex) {
    BOOST_LOG_TRIVIAL(error) << ex.what();
    return JNI_ERR;
  }
}

jint OnAttach(JavaVM& jvm, char* options) {
  BOOST_LOG_TRIVIAL(error) << "Initialization with `OnAttach()` not supported.";
  return JNI_ERR;
}

void OnUnload(JavaVM& jvm) {
  BOOST_LOG_TRIVIAL(info) << "Unloading PhasicJ Trace Logger from JVM...";

}

}  // namespace phasicj::tracelogger::agent
