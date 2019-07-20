// Copyright 2019 David Johnston

#ifndef PHASICJ_TRACELOGGER_TRACE_LOGGER_H_
#define PHASICJ_TRACELOGGER_TRACE_LOGGER_H_

#include "jni.h"
#include "jvmti.h"

#include "phasicj/jmmevents/jmm_action_listener.h"
#include "phasicj/tracelogger/vector_clock_manager.h"
#include "phasicj/tracelogger/trace_manager.h"

namespace phasicj::tracelogger {

class TraceLogger {

 public:
  explicit TraceLogger(::std::filesystem::path log_dir);

 private:
  VectorClockManager vector_clock_manager_;
  TraceManager trace_manager_;
};

}  // namespace phasicj::tracelogger

#endif  // PHASICJ_TRACELOGGER_TRACE_LOGGER_H_
