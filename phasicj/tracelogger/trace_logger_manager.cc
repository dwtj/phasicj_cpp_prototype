// Copyright 2019 David Johnston

#include <filesystem>

#include "google/protobuf/stubs/common.h"

#include "phasicj/tracelogger/trace_logger_manager.h"

namespace phasicj::tracelogger {

using ::std::scoped_lock;
using ::std::filesystem::current_path;
using ::std::filesystem::path;
using ::std::optional;
using ::std::move;

void TraceLoggerManager::Install(const JavaVM& jvm, const optional<path>& log_dir) {
  scoped_lock monitor {monitor_};
  PreCheckEnvironment();
  log_dir.value_or(DefaultTraceLogDir());
  // TODO(dwtj): Everything!
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
