// Copyright 2019 David Johnston

// TODO(dwtj): Fix this garbage WIP documentation!

// `TraceLogger` is a container class for all components in the PhasicJ
// `tracelogger` JVMTI agent. This class is responsible for correctly starting
// and stopping the agent and its components.
//
// - A `jvmtiEnv` is dedicated to supporting a `TraceLogger` Instance
//
// - A single `TraceLogger` instance and its components need to be accessed across
// different JVMTI callbacks by different threads. Rather than using, say,
// global static storage, a single `Agent` instance is stored inside of a JVMTI
// environment instance, specifically, in a JVMTI environment's environment-
// local storage [1].
//
// - We say that an `Agent` stored in this way is "embedded" in
// this JVMTI environment. Thus, when JVMTI callback occurs on a thread, that
// thread can lookup the `Agent` instance "embedded" in the given JVMTI
// environment and forward the event for processing.
//
// [1](https://docs.oracle.com/en/java/javase/11/docs/specs/jvmti.html#GetEnvironmentLocalStorage)


#ifndef PHASICJ_TRACELOGGER_CORE_TRACE_LOGGER_H_
#define PHASICJ_TRACELOGGER_CORE_TRACE_LOGGER_H_

#include "jni.h"
#include "jvmti.h"

#include "phasicj/tracelogger/vector_clock_manager.h"
#include "phasicj/tracelogger/instance_manager.h"
#include "phasicj/tracelogger/trace_manager.h"

namespace phasicj::tracelogger {

using ::phasicj::jmmevents::JmmActionListener;

class TraceLogger : JMMActionListener {
 private:
  jvmtiEnv* jvmti_env_;
  InstanceManager instance_manager_;
  VectorClockManager vector_clock_manager_;
  TraceManager trace_manager_;

  static path DefaultTraceLogDir();
  static jvmtiEnv* NewJvmtiEnv(JavaVM& jvm);

  explicit TraceLogger(jvmtiEnv* jvmti_env);

 public:
  static constexpr auto MINIMUM_REQUIRED_JVMTI_VERSION = JVMTI_VERSION_1_2;

  static void AddNew(JavaVM &jvm);

  void ThreadStart(jvmtiEnv* jvmti_env, JNIEnv* jni_env, jthread thread);

  void ThreadEnd(jvmtiEnv* jvmti_env, JNIEnv* jni_env, jthread thread);

  void VolatileRead(jvmtiEnv& jvmti_env,
                    JNIEnv& jni_env,
                    jthread thread,
                    jmethodID method,
                    jlocation location,
                    jclass field_klass,
                    jobject object,
                    jfieldID field,
                    char signature_type,
                    jvalue new_value);

  void VolatileWrite(jvmtiEnv& jvmti_env,
                     JNIEnv& jni_env,
                     jthread thread,
                     jmethodID method,
                     jlocation location,
                     jclass field_klass,
                     jobject object,
                     jfieldID field);

  void NonVolatileRead(jvmtiEnv& jvmti_env,
                       JNIEnv& jni_env,
                       jthread thread,
                       jmethodID method,
                       jlocation location,
                       jclass field_klass,
                       jobject object,
                       jfieldID field,
                       char signature_type,
                       jvalue new_value);

  void NonVolatileWrite(jvmtiEnv& jvmti_env,
                        JNIEnv& jni_env,
                        jthread thread,
                        jmethodID method,
                        jlocation location,
                        jclass field_klass,
                        jobject object,
                        jfieldID field);
};

}  // namespace phasicj::tracelogger

#endif  // PHASICJ_TRACELOGGER_TRACE_LOGGER_H_
