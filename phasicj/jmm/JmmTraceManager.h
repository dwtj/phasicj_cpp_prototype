// Copyright 2019 David Johnston

#ifndef PHASICJ_JMMEVENTS_JMMTRACEMANAGER_H_
#define PHASICJ_JMMEVENTS_JMMTRACEMANAGER_H_

#include "phasicj/jmmevents/jmm_trace.h"

namespace phasicj::jmmevents {

class JmmTraceManager {
  virtual JmmTrace* New(JvmThreadId thread_id) = 0;
  virtual void Free(JvmThreadId thread_id) = 0;
};

}  // namespace phasicj::jmm

#endif  //PHASICJ_JMMEVENTS_JMMTRACEMANAGER_H_
