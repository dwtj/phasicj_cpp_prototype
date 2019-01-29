// Copyright 2019 David Johnston

// TODO: Rewrite doc.
//
// [1](https://docs.oracle.com/en/java/javase/11/docs/specs/jvmti.html)

#include <stdexcept>
#include <string>

#include "jni.h"    // NOLINT(build/include_subdir)
#include "jvmti.h"  // NOLINT(build/include_subdir)

#include "boost/log/trivial.hpp"

#include "phasicj/execution.pb.h"
#include "phasicj/tracelogger/agent.h"
#include "phasicj/tracelogger/jvmticonf/capabilities.h"
#include "phasicj/tracelogger/jvmtievents/jvmti_callbacks.h"

namespace phasicj::tracelogger {

using ::std::make_unique;
using ::std::optional;
using ::std::runtime_error;
using ::std::string;

using ::phasicj::tracelogger::jvmtievents::INITIAL_AGENT_CALLBACKS;
using ::phasicj::tracelogger::jvmtievents::INITIAL_EVENT_NOTIFICATION_CONFIGS;
using ::phasicj::tracelogger::jvmticonf::INITIAL_REQUIRED_CAPABILITIES;
using ::phasicj::tracelogger::jvmticonf::ProvidesRequiredCapabilities;

optional<Agent*> Agent::NewFromOnLoad(JavaVM* jvm,
                                      char* options,
                                      void* reserved) {
  string opts{(options == nullptr) ? "" : options};
  try {
    return new Agent{*jvm, opts};
  } catch (runtime_error& ex) {
    BOOST_LOG_TRIVIAL(error)
        << "Failed to make an agent from an OnLoad event. " << ex.what();
    return {};
  }
}

Agent::Agent(JavaVM& jvm, const string& options) {
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
        "Failed to add this agent as JVMTI environment-local storage."};
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

Agent::~Agent() noexcept {
  jvmti_env_->DisposeEnvironment();
  jvmti_env_ = nullptr;
};

}  // namespace phasicj::tracelogger
