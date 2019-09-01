// Copyright 2019 David Johnston

#ifndef PHASICJ_JMM_JMMTRACE_H_
#define PHASICJ_JMM_JMMTRACE_H_

#include "phasicj/util/jvm/Threads.h"

namespace phasicj::jmm {

/// An interface by which the different kinds of Java Memory Model actions can
/// be reported.
class JmmTrace {
  virtual void Read(JvmThreadId thread_id) = 0;
  virtual void VolatileRead(JvmThreadId thread_id) = 0;

  virtual void Write(JvmThreadId thread_id) = 0;
  virtual void VolatileWrite(JvmThreadId thread_id) = 0;

  virtual void Lock(JvmThreadId thread_id) = 0;
  virtual void Unlock(JvmThreadId thread_id) = 0;

  virtual void ThreadStart(JvmThreadId thread_id) = 0;
  virtual void ThreadStop(JvmThreadId thread_id) = 0;

  virtual void External(JvmThreadId thread_id) = 0;
};

}  // namespace phasicj::jmm

#endif  //PHASICJ_JMM_JMMTRACE_H_
