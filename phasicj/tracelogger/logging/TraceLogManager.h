// Copyright 2019 David Johnston

#ifndef PHASICJ_TRACELOGGER_LOGGING_TRACE_LOG_MANAGER_H_
#define PHASICJ_TRACELOGGER_LOGGING_TRACE_LOG_MANAGER_H_

#include "phasicj/util/jvm/Threads.h"
#include "phasicj/tracelogger/logging/TraceLog.h"

namespace phasicj::tracelogger::logging {

class TraceLogManager {
  virtual TraceLog open(JvmThreadId id) = 0;
};

}  // namespace phasicj::tracelogger::logging

#endif  // PHASICJ_TRACELOGGER_LOGGING_TRACE_LOG_MANAGER_H_
