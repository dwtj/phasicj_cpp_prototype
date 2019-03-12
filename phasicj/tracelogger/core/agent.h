// Copyright 2019 David Johnston

// TODO(dwtj): Improve documentation

// `Agent` is a container for all components in the PhasicJ `tracelogger` JVMTI
// agent. This class is responsible for correctly starting and stopping the
// agent and its components.
//
// ## Exactly One `Agent` Instance Is Expected To Be Embedded in a `jvmtiEnv`
//
// A single `Agent` instance and its components need to be accessed across
// different JVMTI callbacks by different threads. Rather than using, say,
// global static storage, a single `Agent` instance is stored inside of a JVMTI
// environment instance, specifically, in a JVMTI environment's environment-
// local storage [1]. We say that an `Agent` stored in this way is "embedded" in
// this JVMTI environment. Thus, when JVMTI callback occurs on a thread, that
// thread can lookup the `Agent` instance "embedded" in the given JVMTI
// environment and forward the event for processing.
//
// [1](https://docs.oracle.com/en/java/javase/11/docs/specs/jvmti.html#GetEnvironmentLocalStorage)

#ifndef PHASICJ_TRACELOGGER_CORE_STARTUP_H_
#define PHASICJ_TRACELOGGER_CORE_STARTUP_H_

#include "jni.h"
#include "jvmti.h"

#include "phasicj/tracelogger/core/trace_logger.h"
#include "phasicj/tracelogger/core/tag_manager.h"
#include "phasicj/tracelogger/core/trace_manager.h"
#include "phasicj/tracelogger/core/vector_clock_manager.h"
#include "phasicj/tracelogger/jvmtievents/manager.h"
#include "phasicj/tracelogger/jvmtievents/receiver.h"

#include "phasicj/tracelogger/core/agent.h"

namespace phasicj::tracelogger::core {

using ::phasicj::tracelogger::jvmtievents::JvmtiEventManager;
using ::phasicj::tracelogger::jvmtievents::JvmtiEventReceiver;

class Agent {
 public:
  Agent(JavaVM& jvm);

  static jint OnLoad(JavaVM& vm, char* options);
  static jint OnAttach(JavaVM& vm, char* options);
  static void OnUnload(JavaVM& vm);

  static JvmtiEventReceiver& ReceiverFor(jvmtiEnv& jvmti_env);
  static void DeleteAgentEmbeddedIn(jvmtiEnv& jvmti_env);

 private:
  jvmtiEnv* jvmti_env_;
  JvmtiEventManager jvmti_event_manager_;
  JvmtiEventReceiver jvmti_event_receiver_;
  TagManager tag_manager_;
  VectorClockManager vector_clock_manager_;
  TraceManager trace_manager_;
  TraceLogger trace_logger_;

  void Embed();
  ~Agent();

  static constexpr auto MINIMUM_REQUIRED_JVMTI_VERSION = JVMTI_VERSION_1_2;
  static constexpr auto CURRENT_THREAD = nullptr;

  static path DefaultTraceLogDir();
  static void CheckRuntimeDependencies();
  static jvmtiEnv* NewJvmtiEnv(JavaVM& jvm);
  static void SetEmbeddedAgentPtr(jvmtiEnv&, Agent*);
  static Agent* GetEmbeddedAgentPtr(jvmtiEnv&);
};

}  // namespace phasicj::tracelogger::core

#endif  // PHASICJ_TRACELOGGER_CORE_STARTUP_H_
