// Copyright 2019 David Johnston

#include "phasicj/jmmevents/jvmti_event_adapter.h"
#include "phasicj/jmmevents/jvmti_capabilities.h"

namespace phasicj::jmmevents {

JvmtiEventAdapter::JvmtiEventAdapter(JavaVM &jvm, JmmActionListener* listener) :
  jvmti_env_ {NewJvmtiEnv(jvm)}, listener_{listener} { }

JvmtiEventAdapter::~JvmtiEventAdapter() {
  // TODO(dwtj): Everything!
}

jvmtiEnv* JvmtiEventAdapter::NewJvmtiEnv(JavaVM& jvm) {
  jint err;
  jvmtiEnv *jvmti_env = nullptr;

  err = jvm.GetEnv(reinterpret_cast<void **>(&jvmti_env),
                   MINIMUM_REQUIRED_JVMTI_VERSION);
  if (err != JNI_OK) {
    throw runtime_error {
        // TODO(dwtj): Improve explanation with more specific description.
        "Could not obtain a compatible JVMTI environment from this JVM."
    };
  }

  if (!ProvidesRequiredCapabilities(*jvmti_env)) {
    throw runtime_error{
        // TODO(dwtj): Improve explanation with more specific description.
        "JVMTI environment does not provide one or more required capabilities."
    };
  }

  err = jvmti_env->AddCapabilities(&INITIAL_REQUIRED_CAPABILITIES);
  if (err != JVMTI_ERROR_NONE) {
    // TODO(dwtj): Improve explanation.
    throw runtime_error{"Failed to add one or more required capabilities."};
  }

  return jvmti_env;
}

}  // namespace phasicj::jmmevents
