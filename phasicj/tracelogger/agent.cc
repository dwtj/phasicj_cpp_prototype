// Copyright 2019 David Johnston

// This class implements the actual agent logic. The class does not follow
// conventional RAII discipline. Instances of it are expected to have static
// storage duration. Resources which it manages are primarily provided by the
// JVM and managed during callbacks from the JVM to an agent instance.
//
// More information about these various callbacks and the details of the
// JVM/agent contract are available in [the JVMTI
// documentation](https://docs.oracle.com/en/java/javase/11/docs/specs/jvmti.html).

#include "jni.h"  // NOLINT(build/include_subdir)
#include "jvmti.h"  // NOLINT(build/include_subdir)

#include "phasicj/execution.pb.h"
#include "phasicj/tracelogger/agent.h"

namespace phasicj::tracelogger {

// Warning(dwtj): If `REQUIRED_CAPABILITIES` is changed, so should the checks
// in `ProvidesRequiredCapabilities()`.
// TODO(dwtj): How can we avoid this field name repetition?
const jvmtiCapabilities REQUIRED_CAPABILITIES = {
    .can_tag_objects = 0,
    .can_generate_field_modification_events = 1,
    .can_generate_field_access_events = 1,
};

bool Agent::ProvidesRequiredCapabilities(jvmtiEnv& env) {
  jvmtiCapabilities c;
  env.GetPotentialCapabilities(&c);
  return c.can_generate_field_modification_events &&
         c.can_generate_field_access_events;
}

// Note(dwtj): `options` is non-null, i.e. it is at least a 0-length string.
// Note(dwtj): As of `JVMTI_VERSION_11`, `reserved` is still unused.
Agent* Agent::MaybeNewFromOnLoadEvent(JavaVM* vm, char* options,
                                      void* reserved) {
  // TODO(dwtj): If there are any unexpected options, log a warning.
  jvmtiEnv* jvmti_env = nullptr;
  jint err = vm->GetEnv(reinterpret_cast<void**>(&jvmti_env), JVMTI_VERSION_9);

  if (err != JNI_OK) {
    return nullptr;
  }
  if (jvmti_env == nullptr) {
    return nullptr;
  }
  if (!ProvidesRequiredCapabilities(*jvmti_env)) {
    return nullptr;
  }

  return new Agent{jvmti_env};
}

Agent::Agent(jvmtiEnv* env) : jvmti_env_(env) {
  jvmti_env_->AddCapabilities(&REQUIRED_CAPABILITIES);
}

}  // namespace phasicj::tracelogger
