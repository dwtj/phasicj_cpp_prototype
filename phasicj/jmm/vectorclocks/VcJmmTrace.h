// Copyright 2019 David Johnston

#ifndef PHASICJ_JMM_VECTORCLOCKS_VCJMMTRACE_H_
#define PHASICJ_JMM_VECTORCLOCKS_VCJMMTRACE_H_

#include "jni.h"
#include "jvmti.h"

#include "phasicj/jmm/vectorclocks/VectorClock.h"

namespace phasicj::jmm::vectorclocks {

class VcJmmTrace {
 public:
  virtual void Read(const VectorClock& vc) = 0;
  virtual void VolatileRead(const VectorClock& vc) = 0;

  virtual void Write(const VectorClock& vc) = 0;
  virtual void VolatileWrite(const VectorClock& vc) = 0;

  virtual void Lock(const VectorClock& vc) = 0;
  virtual void Unlock(const VectorClock& vc) = 0;

  virtual void ThreadStart(const VectorClock& vc) = 0;
  virtual void ThreadStop(const VectorClock& vc) = 0;

  virtual void External(const VectorClock& vc) = 0;
};

}  // namespace phasicj::jmm::vectorclocks

#endif  // PHASICJ_JMM_VECTORCLOCKS_VCJMMTRACE_H_
