// Copyright 2019 David Johnston

#ifndef PHASICJ_TRACELOGGER_TRACE_LOGGER_MANAGER_H_
#define PHASICJ_TRACELOGGER_TRACE_LOGGER_MANAGER_H_

#include <mutex>

#include "jvmti.h"  //NOLINT

#include "phasicj/tracelogger/trace_logger.h"

namespace phasicj::tracelogger {

class TraceLoggerManager {
 public:
  TraceLoggerManager() noexcept;
  ~TraceLoggerManager() noexcept;

  void Install(const JavaVM& jvm,
               ::std::optional<::std::filesystem::path> log_dir);
  void Uninstall(const JavaVM& jvm);

 private:
  ::std::mutex monitor_{};
  // TODO(dwtj): Add container for TraceLogger instances.

  static const ::std::filesystem::path DefaultTraceLogDir();
};

}  // namespace phasicj::tracelogger

#endif  // PHASICJ_TRACELOGGER_TRACE_LOGGER_MANAGER_H_
