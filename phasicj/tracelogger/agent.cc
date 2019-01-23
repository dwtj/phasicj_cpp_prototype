// Copyright 2019 David Johnston

// This class implements the actual agent logic. The class does not follow
// conventional RAII discipline. Instances of it are expected to have static
// storage duration. Resources which it manages are primarily provided by the
// JVM and managed during callbacks from the JVM to an agent instance.
//
// More information about these various callbacks and the details of the
// JVM/agent contract are available in [the JVMTI
// documentation](https://docs.oracle.com/en/java/javase/11/docs/specs/jvmti.html).

#include <stdexcept>
#include <string>

#include "jni.h"    // NOLINT(build/include_subdir)
#include "jvmti.h"  // NOLINT(build/include_subdir)

#include "phasicj/execution.pb.h"
#include "phasicj/tracelogger/agent.h"
#include "phasicj/tracelogger/agent_callbacks.h"

namespace phasicj::tracelogger {

using std::optional;
using std::runtime_error;
using std::string;

// Warning(dwtj): If `INITIAL_REQUIRED_CAPABILITIES` is changed, so should the
// checks in `ProvidesRequiredCapabilities()`.
// TODO(dwtj): How can we avoid this field name repetition?
constexpr jvmtiCapabilities INITIAL_REQUIRED_CAPABILITIES = {
    .can_tag_objects = 0,
    .can_generate_field_modification_events = 1,
    .can_generate_field_access_events = 1,
};

bool Agent::ProvidesRequiredCapabilities(jvmtiEnv& jvmti_env) {
  jvmtiCapabilities c;
  jvmti_env.GetPotentialCapabilities(&c);
  return c.can_generate_field_modification_events &&
         c.can_generate_field_access_events;
}

Agent::Agent(JavaVM& jvm, const string& options) {
  // https://docs.oracle.com/en/java/javase/11/docs/specs/jvmti.html#jvmtiEnvAccess
  jint err =
      jvm.GetEnv(reinterpret_cast<void**>(&jvmti_env_), JVMTI_VERSION_1_2);
  if (err != JNI_OK) {
    throw runtime_error{
        "Could not obtain a compatible JVMTI environment from this JVM."};
  }

  if (!ProvidesRequiredCapabilities(*jvmti_env_)) {
    throw runtime_error{
        "JVMTI environment does not provide one or more required "
        "capabilities."};
  }
  err = jvmti_env_->AddCapabilities(&INITIAL_REQUIRED_CAPABILITIES);
  if (err != JVMTI_ERROR_NONE) {
    throw runtime_error{"Failed to add one or more required capabilities."};
  }

  err = jvmti_env_->SetEnvironmentLocalStorage(reinterpret_cast<void*>(this));
  if (err != JVMTI_ERROR_NONE) {
    throw runtime_error{
        "Failed to add this agent as JVMTI environment-local storage."};
  }

  err = jvmti_env_->SetEventCallbacks(&INITIAL_AGENT_CALLBACKS,
                                      sizeof(jvmtiEventCallbacks));
  if (err != JVMTI_ERROR_NONE) {
    throw runtime_error{"Failed to set one or more event callbacks."};
  }

  for (auto& config : INITIAL_AGENT_EVENT_NOTIFICATION_CONFIGS) {
    err = jvmti_env_->SetEventNotificationMode(
        config.mode, config.event_type, config.thread);
    if (err != JVMTI_ERROR_NONE) {
      throw runtime_error{"Failed to set an event notification mode."};
    }
  }
}

Agent::Agent(Agent&& other) noexcept = default;

Agent::~Agent() noexcept {
  jvmti_env_->DisposeEnvironment();
  jvmti_env_ = nullptr;
};

void Agent::FieldAccess(jvmtiEnv* jvmti_env,
                        JNIEnv* jni_env,
                        jthread thread,
                        jmethodID method,
                        jlocation location,
                        jclass field_klass,
                        jobject object,
                        jfieldID field) {
  // TODO(dwtj): Everything.
}

void Agent::FieldModification(jvmtiEnv* jvmti_env,
                              JNIEnv* jni_env,
                              jthread thread,
                              jmethodID method,
                              jlocation location,
                              jclass field_klass,
                              jobject object,
                              jfieldID field,
                              char signature_type,
                              jvalue new_value) {
  // TODO(dwtj): Everything.
}

}  // namespace phasicj::tracelogger
