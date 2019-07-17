// Copyright 2019 David Johnston

#include <stdexcept>

#include "boost/log/trivial.hpp"

#include "jni.h"

#include "phasicj/tracelogger/core/trace_logger.h"
#include "phasicj/tracelogger/agent/agent.h"

namespace phasicj::tracelogger::agent {

using ::phasicj::tracelogger::core::TraceLogger;
using ::std::runtime_error;

/*
  if (!ProvidesRequiredCapabilities(*jvmti_env)) {
    throw runtime_error{
        // TODO(dwtj): Improve explanation.
        "JVMTI environment does not provide one or more required capabilities."
    };
  }

  jint err = jvmti_env->AddCapabilities(&INITIAL_REQUIRED_CAPABILITIES);
  if (err != JVMTI_ERROR_NONE) {
    // TODO(dwtj): Improve explanation.
    throw runtime_error{"Failed to add one or more required capabilities."};
  }
  */

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

}  // namespace phasicj::tracelogger::agent
