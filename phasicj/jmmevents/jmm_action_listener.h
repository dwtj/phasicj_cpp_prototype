// Copyright 2019 David Johnston

#ifndef PHASICJ_JMMEVENTS_ACTIONLISTENER_H_
#define PHASICJ_JMMEVENTS_ACTIONLISTENER_H_

#include <cstdint>
#include "jvmti.h"  //NOLINT

namespace phasicj::jmmevents {

/// An interface by which the different kinds of Java Memory Model actions can
/// be reported via callback.
class JmmActionListener {
  virtual void Read(int64_t thread_id) = 0;
  virtual void VolatileRead(int64_t thread_id) = 0;

  virtual void Write(int64_t thread_id) = 0;
  virtual void VolatileWrite(int64_t thread_id) = 0;

  virtual void Lock(int64_t thread_id) = 0;
  virtual void Unlock(int64_t thread_id) = 0;

  virtual void ThreadStart(int64_t thread_id) = 0;
  virtual void ThreadStop(int64_t thread_id) = 0;

  virtual void External(int64_t thread_id) = 0;

  // The JVM is terminating. No more JMM actions events will be sent after after
  // this event.
  virtual void JvmDeath() = 0;
};

}  // namespace phasicj::jmmevents

#endif  // PHASICJ_JMMEVENTS_ACTIONLISTENER_H_
