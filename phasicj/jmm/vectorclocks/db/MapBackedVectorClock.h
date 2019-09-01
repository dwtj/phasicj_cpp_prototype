// Copyright 2019 David Johnston

#ifndef PHASICJ_JMM_VECTORCLOCKS_DB_MAPBACKEDVECTORCLOCK_H_
#define PHASICJ_JMM_VECTORCLOCKS_DB_MAPBACKEDVECTORCLOCK_H_

#include <cstdint>
#include <map>
#include <ostream>

#include "phasicj/jmm/vectorclocks/VectorClock.h"

namespace phasicj::jmm::vectorclocks::db {

/// A class to help build, update, synchronize, and serialize vector clocks. The
/// backing store for the vector clocks's counters is just a simple `::std::map`
/// instance.
class MapBackedVectorClock : public ::phasicj::jmm::vectorclocks::VectorClock {
 public:
  MapBackedVectorClock();
  void Tick(int64_t thread_id) override;
  void Synchronize(VectorClock& other) override;

 private:
  void Synchronize(MapBackedVectorClock& other);
  static void SynchronizeOneWay(const MapBackedVectorClock& src,
                                MapBackedVectorClock& to);
  ::std::map<int64_t, int64_t> counters_;
};

}  // namespace phasicj::jmm::vectorclocks::db

#endif  // PHASICJ_JMM_VECTORCLOCKS_DB_MAPBACKEDVECTORCLOCK_H_
