// Copyright 2019 David Johnston

// A class to help build, update, synchronize, and serialize vector clocks.

#ifndef PHASICJ_TRACELOGGER_VECTOR_CLOCK_H_
#define PHASICJ_TRACELOGGER_VECTOR_CLOCK_H_

#include <cstdint>
#include <map>
#include <ostream>

namespace phasicj::tracelogger {

class VectorClock {
 public:
  VectorClock();
  void Tick(int64_t thread_id);
  void Synchronize(VectorClock& other);

 private:
  static void SynchronizeOneWay(const VectorClock& src, VectorClock& to);
  std::map<int64_t, int64_t> counters_;
};

}  // namespace phasicj::tracelogger

#endif  // PHASICJ_TRACELOGGER_VECTOR_CLOCK_H_
