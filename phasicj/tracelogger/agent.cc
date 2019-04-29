// Copyright 2019 David Johnston

#include <stdexcept>

#include "boost/log/trivial.hpp"

#include "jni.h"

#include "phasicj/tracelogger/core/trace_logger.h"
#include "phasicj/tracelogger/agent.h"

namespace phasicj::tracelogger {

using ::phasicj::tracelogger::core::TraceLogger;
using ::std::runtime_error;

// TODO(dwtj): Consider using the `options` string.
jint OnLoad(JavaVM& jvm, char* options) {
  BOOST_LOG_TRIVIAL(info) << "Loading PhasicJ Trace Logger into JVM...";
  BOOST_LOG_TRIVIAL(info) << "Verifying Google Protobuf Version for PhasicJ...";
  GOOGLE_PROTOBUF_VERIFY_VERSION;
  try {
    TraceLogger::AddNew(jvm);
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

}  // namespace phasicj::tracelogger
