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
/// only adds risk and gives little benefit, so I haven't included it. Here's
/// one hypothetical situation demonstrating why it maybe shouldn't be called.
/// 1. A process creates a JVM instance
/// 2. The agent is run alongside/within this JVM
/// 3. The JVM shuts down
/// 4. While shutting down, the agent calls `ShutdownProtobufLibrary()`
/// 5. The process attempts to use protobuf, but fails unexpectedly.
void OnUnload(JavaVM& jvm) {
  BOOST_LOG_TRIVIAL(info) << "Uninstalling PhasicJ Trace Logger from JVM...";
  trace_logger_manager_.Uninstall(jvm);
}

}  // namespace phasicj::tracelogger::agent
