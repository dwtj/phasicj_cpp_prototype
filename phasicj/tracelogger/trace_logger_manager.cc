// Copyright 2019 David Johnston

#include <filesystem>
#include <stdexcept>

#include "google/protobuf/stubs/common.h"

#include "phasicj/tracelogger/trace_logger_manager.h"

namespace phasicj::tracelogger {

using ::std::scoped_lock;
using ::std::filesystem::current_path;
using ::std::filesystem::path;
using ::std::optional;
using ::std::runtime_error;

namespace {

jvmtiEnv* GetNewJvmtiEnv(JavaVM& jvm) {
  jvmtiEnv* env = nullptr;
  jint err = jvm.GetEnv(reinterpret_cast<void**>(&env),
                        TraceLoggerManager::REQUESTED_JVMTI_VERSION);
  switch (err) {
    case JNI_OK:
      if (env != nullptr) {
        return env;
      } else {
        throw runtime_error{"The JVM didn't return a valid JVMTI environment."};
      }
    case JNI_EDETACHED:
      throw runtime_error{"The current thread isn't attached to this JVM."};
    case JNI_EVERSION:
      throw runtime_error{"This JVM can't provide the required JVMTI version."};
    default:
      throw runtime_error{"An unfamiliar error code was returned from GetEnv"};
  }
}


}

void TraceLoggerManager::Install(JavaVM& jvm, const optional<path>& log_dir) {
  scoped_lock monitor {monitor_};

  PreCheckEnvironment();
  trace_logger_ = new TraceLogger{log_dir.value_or(DefaultTraceLogDir())};

  jvmtiEnv* env = GetNewJvmtiEnv(jvm);
  // TODO(dwtj): Move the logic of configuring a jvmtiEnv into `jmmevents::jmm_action_adapter`
  // TODO(dwtj): Install trace logger into env.
}

void TraceLoggerManager::Uninstall(const JavaVM& jvm) {
  scoped_lock monitor {monitor_};
  // TODO(dwtj): Everything!
}

void TraceLoggerManager::PreCheckEnvironment() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;
}

const path TraceLoggerManager::DefaultTraceLogDir() {
  return current_path();
}

}  // namespace phasicj::tracelogger
