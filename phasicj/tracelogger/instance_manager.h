// Copyright 2019 David Johnston

#ifndef PHASICJ_TRACELOGGER_INSTANCE_MANAGER_H_
#define PHASICJ_TRACELOGGER_INSTANCE_MANAGER_H_

#include "jvmti.h"

namespace phasicj::tracelogger {

class InstanceManager {
 public:
  explicit InstanceManager(jvmtiEnv* jvmti_env);

 private:
  jvmtiEnv* jvmti_env_;
};

}  // namespace phasicj::tracelogger

#endif  // PHASICJ_TRACELOGGER_INSTANCE_MANAGER_H_
