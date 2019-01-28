// Copyright 2019 David Johnston

#include <ostream>

#include "phasicj/tracelogger/vector_clock.h"

namespace phasicj::tracelogger {

VectorClock::VectorClock() : counters_(), pb_counters_() {}

void VectorClock::Tick(::google::protobuf::uint64 thread_id) {
  ++counters_[thread_id];
}

void VectorClock::Synchronize(VectorClock& that) {
  SynchronizeOneWay(*this, that);
  SynchronizeOneWay(that, *this);
}

bool VectorClock::SerializeTo(std::ostream& out) {
  pb_counters_.clear_counters();
}

// Iterate over all elements of `src`. For each, try to find an element with
// the same key in `dest`. If there is no such element, add it with the value.
// Otherwise, if there is such an element, check to see which has the larger
// value. Copy the value over if `src` has the larger value.
void VectorClock::SynchronizeOneWay(const VectorClock& src, VectorClock& dest) {
  for (const auto& [src_key, src_val] : src.counters_) {
    auto dest_iter = dest.counters_.find(src_key);
    if (dest_iter == dest.counters_.end()) {
      // `dest` DOES NOT contain `src_key`.
      dest.counters_[src_key] = src_val;
    } else {
      // `dest` DOES contain `src_key`.
      auto& [_, dest_val] = *dest_iter;
      if (dest_val < src_val) {
        dest.counters_[src_key] = src_val;
      }
    }
  }
}

}  // namespace phasicj::tracelogger