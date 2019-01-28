// Copyright 2019 David Johnston

// A class to help build, update, synchronize, and serialize vector clocks.

#ifndef PHASICJ_TRACELOGGER_VECTOR_CLOCK_H_
#define PHASICJ_TRACELOGGER_VECTOR_CLOCK_H_

#include <map>
#include <ostream>

#include "phasicj/vectorclock.pb.h"

namespace phasicj::tracelogger {

class VectorClock {
 public:
  VectorClock();
  void Tick(::google::protobuf::uint64 thread_id);
  void Synchronize(VectorClock& other);
  bool SerializeTo(std::ostream& out);

 private:
  static void SynchronizeOneWay(const VectorClock& src, VectorClock& to);
  std::map<::google::protobuf::uint64, ::google::protobuf::uint64> counters_;
  ::phasicj::VectorClock pb_counters_;
};

}  // namespace phasicj::tracelogger

#endif  // PHASICJ_TRACELOGGER_VECTOR_CLOCK_H_
