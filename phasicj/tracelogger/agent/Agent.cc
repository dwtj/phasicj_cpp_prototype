// Copyright 2019 David Johnston

#include <stdexcept>
#include <mutex>

#include "boost/log/trivial.hpp"

#include "jni.h"

#include "phasicj/tracelogger/TraceLogManager.h"
#include "phasicj/tracelogger/agent/Agent.h"

namespace phasicj::tracelogger::agent {

using ::phasicj::tracelogger::TraceLoggerManager;
using ::std::runtime_error;
using ::std::optional;

namespace {
TraceLoggerManager trace_logger_manager_{};
}

/// @warning The JVMTI OnLoad/OnAttach/OnUnload callbacks need to be thread
/// safe because, theoretically, a single process can contain multiple JVM
/// instances. If within one process, more than one JVM is configured to use the
/// PhasicJ TraceLogger Agent, then this callback will be called more than once,
/// possibly with concurrent interference. This might not currently be doable in
/// practice (Hotspot's JNI Invocation API does not support it as of
/// 2019-08-18), but it could be done in principle.
///
// TODO(dwtj): Consider using the `options` string (e.g. to set log method/path)
jint OnLoad(JavaVM& jvm, const char* options) {
  try {
    BOOST_LOG_TRIVIAL(info) << "Installing PhasicJ Trace Logger into JVM...";
    trace_logger_manager_.Install(jvm, {});
    return JNI_OK;
  } catch (runtime_error& ex) {
    BOOST_LOG_TRIVIAL(error) << ex.what();
    return JNI_ERR;
  }
}

jint OnAttach(JavaVM& jvm, const char* options) {
  BOOST_LOG_TRIVIAL(error)
    << "PhasicJ TraceLogger initialization via `OnAttach()` is not supported.";
  return JNI_ERR;
}

/// @warning `google::protobuf::ShutdownProtobufLibrary()` is not called
/// anywhere during cleanup. Currently, I think that `ShutdownProtobufLibrary()`
/// only adds risk and gives little benefit, so I haven't included it. If
/// `ShutdownProtobufLibrary()` is called during `OnUnload()`, any subsequent
/// attempts to use the Protobuf library will fail (e.g. if another JVM
/// with TraceLogger is started, or if code after JVM shutdown uses Protobuf).
void OnUnload(JavaVM& jvm) {
  BOOST_LOG_TRIVIAL(info) << "Uninstalling PhasicJ Trace Logger from JVM...";
  trace_logger_manager_.Uninstall(jvm);
}

}  // namespace phasicj::tracelogger::agent
