// Copyright 2019 David Johnston

/// Supports access to and synchronization between vector clocks. A vector clock
/// stored here may be associated with either a JVM volatile variable instance
/// or a JVM monitor instance.

#ifndef PHASICJ_JMM_VECTORCLOCKS_DB_VECTOR_CLOCK_MANAGER_H_
#define PHASICJ_JMM_VECTORCLOCKS_DB_VECTOR_CLOCK_MANAGER_H_

namespace phasicj::jmm::vectorclocks::db {

class VectorClockDb {
 public:
  VectorClockDb() noexcept;
};

}  // namespace phasicj::jmm::vectorclocks::db

#endif  // PHASICJ_JMM_VECTORCLOCKS_VECTOR_CLOCK_MANAGER_H_
