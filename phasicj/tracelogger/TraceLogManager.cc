// Copyright 2019 David Johnston

#include <filesystem>
#include <stdexcept>

#include "phasicj/tracelogger/TraceLogManager.h"

namespace phasicj::tracelogger {

using ::std::scoped_lock;
using ::std::filesystem::current_path;
using ::std::filesystem::path;
using ::std::optional;
using ::std::runtime_error;

void TraceLoggerManager::Install(JavaVM& jvm, const optional<path>& log_dir) {
  scoped_lock monitor {monitor_};

  if (trace_logger_ != nullptr) {
    throw runtime_error{
        "A trace logger has already been installed into a JVM. "
        "We do not yet support installing additional trace loggers."
    };
  }

  trace_logger_ = new TraceLogger{jvm, log_dir.value_or(DefaultTraceLogDir())};
}

void TraceLoggerManager::Uninstall(const JavaVM& jvm) {
  scoped_lock monitor {monitor_};
  // TODO(dwtj): Everything!
}

const path TraceLoggerManager::DefaultTraceLogDir() {
  return current_path();
}

}  // namespace phasicj::tracelogger
