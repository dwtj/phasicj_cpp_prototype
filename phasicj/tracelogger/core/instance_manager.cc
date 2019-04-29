// Copyright 2019 David Johnston

#include "jvmti.h"

#include "phasicj/tracelogger/core/instance_manager.h"

namespace phasicj::tracelogger::core {

InstanceManager::InstanceManager(jvmtiEnv* jvmti_env) : jvmti_env_{jvmti_env} {}

}  // namespace phasicj::tracelogger::core
