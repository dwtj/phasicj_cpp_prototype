// Copyright 2019 David Johnston
#include <stdexcept>
#include <string>

#include "jni.h"    // NOLINT(build/include_subdir)
#include "jvmti.h"  // NOLINT(build/include_subdir)

#include "boost/log/trivial.hpp"

#include "phasicj/tracelogger/agent/agent.h"
#include "phasicj/tracelogger/jvmticonf/capabilities.h"
#include "phasicj/tracelogger/jvmtievents/jvmti_callbacks.h"

#include "//phasicj/tracelogger/jvmticonf/initialize_environment.h"

namespace phasicj::tracelogger::jvmticonfig {

using ::std::make_unique;
using ::std::optional;
using ::std::runtime_error;
using ::std::string;

using ::phasicj::tracelogger::jvmticonfig::INITIAL_AGENT_CALLBACKS;
using ::phasicj::tracelogger::jvmticonfig::INITIAL_EVENT_NOTIFICATION_CONFIGS;
using ::phasicj::tracelogger::jvmticonfig::INITIAL_REQUIRED_CAPABILITIES;
using ::phasicj::tracelogger::jvmticonfig::ProvidesRequiredCapabilities;

void init(JVMTIEnv* jvmti_env) {
    // https://docs.oracle.com/en/java/javase/11/docs/specs/jvmti.html#jvmtiEnvAccess
  auto JVMTI_VERSION = JVMTI_VERSION_1_2;

  jint err = jvm.GetEnv(reinterpret_cast<void**>(&jvmti_env_), JVMTI_VERSION);
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
        "Failed to add this jvmtiagent as JVMTI environment-local storage."};
  }

  err = jvmti_env_->SetEventCallbacks(&INITIAL_AGENT_CALLBACKS,
                                      sizeof(jvmtiEventCallbacks));
  if (err != JVMTI_ERROR_NONE) {
    throw runtime_error{"Failed to set one or more event callbacks."};
  }

  for (auto& config : INITIAL_EVENT_NOTIFICATION_CONFIGS) {
    err = jvmti_env_->SetEventNotificationMode(
        config.mode, config.event_type, config.thread);
    if (err != JVMTI_ERROR_NONE) {
      throw runtime_error{"Failed to set an event notification mode."};
    }
  }
}
