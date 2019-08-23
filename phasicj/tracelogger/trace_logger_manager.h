// Copyright 2019 David Johnston

#ifndef PHASICJ_TRACELOGGER_TRACE_LOGGER_MANAGER_H_
#define PHASICJ_TRACELOGGER_TRACE_LOGGER_MANAGER_H_

#include <mutex>

#include "jvmti.h"  //NOLINT

#include "phasicj/tracelogger/trace_logger.h"

namespace phasicj::tracelogger {

/// Manages the creation, installation, uninstallation, and deletion of a
/// `TraceLogger` instance within a JVM instance. Currently, it can only manage
/// one TraceLogger/JVM relationship. The class is implemented in a thread-safe
/// way (see `monitor_`) to detect invalid concurrent usage and to prevent
/// memory visibility issues.
// TODO(dwtj): Make this class able to manage the `TraceLogger` instances of
//  multiple JVMs. Currently, it can only manage one JVM even though in
//  principle, more than one JVM might exist within a process. Fortunately, this
//  is an unlikely use case since (as of 2019/08/16) it appears that the Hotspot
//  JVM does not yet support more than one JVM instance within a process.
class TraceLoggerManager {
 public:
  TraceLoggerManager() noexcept = default;
  ~TraceLoggerManager() noexcept = default;

  void Install(const JavaVM& jvm,
               const ::std::optional<::std::filesystem::path>& log_dir);
  void Uninstall(const JavaVM& jvm);

 private:
  ::std::mutex monitor_{};
  ::std::optional<TraceLogger> trace_logger_ {};

  static void PreCheckEnvironment();

  static const ::std::filesystem::path DefaultTraceLogDir();
};

}  // namespace phasicj::tracelogger

#endif  // PHASICJ_TRACELOGGER_TRACE_LOGGER_MANAGER_H_
