// Copyright 2019 David Johnston

#include "google/protobuf/stubs/common.h"

#include "jni.h"
#include "jvmti.h"

#include "phasicj/tracelogger/core/tag_manager.h"
#include "phasicj/tracelogger/core/trace_manager.h"
#include "phasicj/tracelogger/core/agent.h"

namespace phasicj::tracelogger::core {

using ::std::make_unique;
using ::std::unique_ptr;
using ::std::optional;
using ::std::runtime_error;
using ::std::string;
using ::std::filesystem::current_path;
using ::phasicj::tracelogger::jvmtievents::JvmtiEventReceiver;

jint Agent::OnLoad(JavaVM& jvm, char* options) {
  return JNI_ERR;  // TODO(dwtj)
}

jint Agent::OnAttach(JavaVM& jvm, char* options) {
  return JNI_ERR;  // Initialization with `OnAttach()` not supported.
}

void Agent::OnUnload(JavaVM& jvm) {
  // TODO(dwtj)
}

Agent::Agent(JavaVM& jvm) :
    jvmti_env_{NewJvmtiEnv(jvm)},
    jvmti_event_manager_{jvmti_env_},
    jvmti_event_receiver_{&jvmti_event_manager_, &trace_logger_},
    tag_manager_{jvmti_env_},
    vector_clock_manager_{},
    trace_manager_{jvmti_env_, DefaultTraceLogDir()},
    trace_logger_{&vector_clock_manager_, &tag_manager_, &trace_manager_} {
  CheckRuntimeDependencies();
  Embed();
}

path Agent::DefaultTraceLogDir() {
  return current_path();
}

void Agent::CheckRuntimeDependencies() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;
}

jvmtiEnv* Agent::NewJvmtiEnv(JavaVM& jvm) {
  jvmtiEnv *jvmti_env = nullptr;

  jint err = jvm.GetEnv(reinterpret_cast<void **>(&jvmti_env),
                        MINIMUM_REQUIRED_JVMTI_VERSION);
  if (err != JNI_OK) {
    throw runtime_error {
      // TODO(dwtj): Improve explanation.
      "Could not obtain a compatible JVMTI environment from this JVM."
    };
  }


  return jvmti_env;
}

void Agent::Embed() {
  auto Error = [](auto msg) {
    throw runtime_error{msg};
  };

  assert(GetEmbeddedAgentPtr(*jvmti_env_) == nullptr);
  SetEmbeddedAgentPtr(*jvmti_env_, this);
}

void Agent::DeleteAgentEmbeddedIn(jvmtiEnv& jvmti_env) {
  delete GetEmbeddedAgentPtr(jvmti_env);
  SetEmbeddedAgentPtr(jvmti_env, nullptr);
}

JvmtiEventReceiver& Agent::ReceiverFor(jvmtiEnv& jvmti_env) {
  return GetEmbeddedAgentPtr(jvmti_env)->jvmti_event_receiver_;
}

void Agent::SetEmbeddedAgentPtr(jvmtiEnv& jvmti_env, Agent* agent) {
  constexpr auto Error = [](auto msg) {
    throw runtime_error{msg};
  };

  jint err = jvmti_env.SetThreadLocalStorage(CURRENT_THREAD, agent);
  switch (err) {
    case JVMTI_ERROR_NONE:
      return;  // Old handler pointer successfully nulled.
    case JVMTI_ERROR_INVALID_THREAD:
      Error("Current thread is invalid.");
    case JVMTI_ERROR_THREAD_NOT_ALIVE:
      Error("Current thread is (somehow) not alive.");
    // TODO: Give better descriptions for universal errors.
    default:
      Error("JVMTI returned an unexpected error code.");
  }
}

Agent* Agent::GetEmbeddedAgentPtr(jvmtiEnv& jvmti_env) {
  constexpr auto Error = [](auto msg) {
    throw runtime_error{msg};
  };

  Agent* agent{};
  jvmtiError err = jvmti_env.GetEnvironmentLocalStorage(
      reinterpret_cast<void**>(&agent));
  switch (err) {
    case JVMTI_ERROR_NONE:
    case JVMTI_ERROR_NULL_POINTER:
      break;
    default:
      Error("JVMTI returned an unexpected error code.");
  }

  return agent;
}

Agent::~Agent() {
  google::protobuf::ShutdownProtobufLibrary();
}

}  // namespace phasicj::tracelogger::core
