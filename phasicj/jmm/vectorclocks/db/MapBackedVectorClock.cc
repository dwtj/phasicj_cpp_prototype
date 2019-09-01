// Copyright 2019 David Johnston

#include "MapBackedVectorClock.h"

#include <cstdint>
#include <ostream>

#include "phasicj/jmm/vectorclocks/db/MapBackedVectorClock.h"

namespace phasicj::jmm::vectorclocks::db {

using ::std::runtime_error;

MapBackedVectorClock::MapBackedVectorClock() : counters_{} {}

void MapBackedVectorClock::Tick(int64_t thread_id) {
  ++counters_[thread_id];
}

void MapBackedVectorClock::Synchronize(VectorClock &that) {
  // TODO(dwtj): Implement this.
  throw runtime_error{"This functionality has not yet been implemented."};
}

void MapBackedVectorClock::Synchronize(MapBackedVectorClock& that) {
  SynchronizeOneWay(*this, that);
  SynchronizeOneWay(that, *this);
}

// Iterate over all elements of `src`. For each, try to find an element with
// the same key in `dest`. If there is no such element, add it with the value.
// Otherwise, if there is such an element, check to see which has the larger
// value. Copy the value over if `src` has the larger value.
void MapBackedVectorClock::SynchronizeOneWay(const MapBackedVectorClock& src,
                                             MapBackedVectorClock& dest) {
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

}  // namespace phasicj::jmm::vectorclocks::db
