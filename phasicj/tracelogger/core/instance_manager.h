// Copyright 2019 David Johnston

#ifndef PHASICJ_TRACELOGGER_CORE_INSTANCE_MANAGER_H_
#define PHASICJ_TRACELOGGER_CORE_INSTANCE_MANAGER_H_

#include "jvmti.h"

namespace phasicj::tracelogger::core {

class InstanceManager {
 public:
  explicit InstanceManager(jvmtiEnv* jvmti_env);

 private:
  jvmtiEnv* jvmti_env_;
};

}  // namespace phasicj::tracelogger::core

#endif  // PHASICJ_TRACELOGGER_CORE_INSTANCE_MANAGER_H_
