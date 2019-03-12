// Copyright 2019 David Johnston

#include <stdexcept>

#include "jni.h"
#include "jvmti.h"

#include "phasicj/tracelogger/jvmticonfig/capabilities.h"
#include "phasicj/tracelogger/jvmtievents/manager.h"

namespace phasicj::tracelogger::jvmtievents {

using ::std::runtime_error;
using ::phasicj::tracelogger::jvmticonfig::ProvidesRequiredCapabilities;
using ::phasicj::tracelogger::jvmticonfig::INITIAL_REQUIRED_CAPABILITIES;

JvmtiEventManager::JvmtiEventManager(jvmtiEnv* jvmti_env) : jvmti_env_{jvmti_env} {
  if (!ProvidesRequiredCapabilities(*jvmti_env)) {
    throw runtime_error{
        // TODO(dwtj): Improve explanation.
        "JVMTI environment does not provide one or more required capabilities."
    };
  }

  jint err = jvmti_env->AddCapabilities(&INITIAL_REQUIRED_CAPABILITIES);
  if (err != JVMTI_ERROR_NONE) {
    // TODO(dwtj): Improve explanation.
    throw runtime_error{"Failed to add one or more required capabilities."};
  }
}


}  // namespace phasicj::tracelogger::jvmtievents
