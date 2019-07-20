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

using ::google::protobuf::ShutdownProtobufLibrary;

// TODO(dwtj): This is not actually noexcept.
TraceLoggerManager::TraceLoggerManager() noexcept {
  GOOGLE_PROTOBUF_VERIFY_VERSION;
}

// TODO(dwtj): This may not actually be noexcept
TraceLoggerManager::~TraceLoggerManager() noexcept {
  ShutdownProtobufLibrary();
}

void TraceLoggerManager::Install(const JavaVM &jvm, optional<path> log_dir) {
  scoped_lock monitor {monitor_};
  log_dir.value_or(DefaultTraceLogDir());
  // TODO(dwtj: Everything!
}

void TraceLoggerManager::Uninstall(const JavaVM &jvm) {
  scoped_lock monitor {monitor_};
  // TODO(dwtj): Everything!
}

const path TraceLoggerManager::DefaultTraceLogDir() {
  return current_path();
}

}  // namespace phasicj::tracelogger
