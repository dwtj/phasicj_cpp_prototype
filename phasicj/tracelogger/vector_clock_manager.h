// Copyright 2019 David Johnston

// Supports mutually-exclusive access to vector clocks associated with live JVM
// volatile variables and monitors.

#ifndef PHASICJ_TRACELOGGER_VECTOR_CLOCK_MANAGER_H_
#define PHASICJ_TRACELOGGER_VECTOR_CLOCK_MANAGER_H_

namespace phasicj::tracelogger {

class VectorClockManager {
 public:
  VectorClockManager() noexcept;
};

}  // namespace phasicj::tracelogger

#endif //PHASICJ_TRACELOGGER_VECTOR_CLOCK_MANAGER_H_
