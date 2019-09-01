// Copyright 2019 David Johnston

#ifndef PHASICJ_JMM_VECTORCLOCKS_VECTOR_CLOCK_H_
#define PHASICJ_JMM_VECTORCLOCKS_VECTOR_CLOCK_H_

#include <cstdint>

namespace phasicj::jmm::vectorclocks {

class VectorClock {
  virtual void Tick(int64_t thread_id) = 0;
  virtual void Synchronize(VectorClock& other) = 0;
};

}  // namespace phasicj::jmm::vectorclocks

#endif  // PHASICJ_JMM_VECTORCLOCKS_VECTOR_CLOCK_H_
