// Copyright 2019 David Johnston

#ifndef PHASICJ_TRACELOGGER_JVMTIEVENTS_MANAGER_H_
#define PHASICJ_TRACELOGGER_JVMTIEVENTS_MANAGER_H_

#include "jvmti.h"

namespace phasicj::tracelogger::jvmtievents {

class JvmtiEventManager {
 public:
  JvmtiEventManager(jvmtiEnv* jvmti_env);

 private:
  jvmtiEnv* jvmti_env_;
};

}

#endif  // PHASICJ_TRACELOGGER_JVMTIEVENTS_MANAGER_H_
