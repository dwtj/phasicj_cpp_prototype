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
using ::std::unique_ptr;
using ::std::make_unique;

namespace {
TraceLoggerManager trace_logger_{};
}

/// @warning This code is NOT thread safe. It may not behave correctly when
/// the agent is used by multiple JVM instances within a single process.
/// Theoretically, a single process can contain multiple JVMs. This can be done,
/// for example, via the JNI Invocation API. If within one process, more than
/// one JVM is configured to use the PhasicJ TraceLogger agent, then this
/// callback will be called more than one time, and one call can interfere with
/// the others.
// TODO(dwtj): Does C++ have a way to use something like Java's static monitors?
// TODO(dwtj): Consider using the `options` string.
jint OnLoad(JavaVM& jvm, char* options) {

  BOOST_LOG_TRIVIAL(info) << "Verifying Google Protobuf Version for PhasicJ...";
  GOOGLE_PROTOBUF_VERIFY_VERSION;
  try {
    // TODO(dwtj)
    trace_logger_ = make_unique<TraceLogger>();
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

  google::protobuf::ShutdownProtobufLibrary();
}

}  // namespace phasicj::tracelogger::agent
