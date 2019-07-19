// Copyright 2019 David Johnston

#ifndef PHASICJ_TRACELOGGER_TRACE_LOGGER_MANAGER_H_
#define PHASICJ_TRACELOGGER_TRACE_LOGGER_MANAGER_H_

#include <mutex>

#include "jvmti.h"  //NOLINT

namespace phasicj::tracelogger {

class TraceLoggerManager {
 public:
  void Install(const JavaVM& jvm);
  void Uninstall(const JavaVM& jvm);

 private:
  std::mutex monitor_{};
};

}  // namespace phasicj::tracelogger

#endif  // PHASICJ_TRACELOGGER_TRACE_LOGGER_MANAGER_H_
