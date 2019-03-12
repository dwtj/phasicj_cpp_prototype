// Copyright 2019 David Johnston

#ifndef PHASICJ_TRACELOGGER_CORE_TRACE_H_
#define PHASICJ_TRACELOGGER_CORE_TRACE_H_

#include "jni.h"
#include "jvmti.h"

#include "phasicj/tracelogger/core/trace_log.h"
#include "phasicj/tracelogger/core/vector_clock.h"

namespace phasicj::tracelogger::core {

using ::std::filesystem::path;
using ::phasicj::tracelogger::core::TraceLog;

class Trace {
 public:
  Trace(jlong thread_id, path&& log_path);

  void NonVolatileRead(jvmtiEnv *jvmti_env,
                     JNIEnv *jni_env,
                     jthread thread,
                     jmethodID method,
                     jlocation location,
                     jclass field_klass,
                     jobject object,
                     jfieldID field);

  void NonVolatileWrite(jvmtiEnv *jvmti_env,
                         JNIEnv *jni_env,
                         jthread thread,
                         jmethodID method,
                         jlocation location,
                         jclass field_klass,
                         jobject object,
                         jfieldID field,
                         char signature_type,
                         jvalue new_value);

  void VolatileRead(jvmtiEnv *jvmti_env,
                     JNIEnv *jni_env,
                     jthread thread,
                     jmethodID method,
                     jlocation location,
                     jclass field_klass,
                     jobject object,
                     jfieldID field);

  void VolatileWrite(jvmtiEnv *jvmti_env,
                         JNIEnv *jni_env,
                         jthread thread,
                         jmethodID method,
                         jlocation location,
                         jclass field_klass,
                         jobject object,
                         jfieldID field,
                         char signature_type,
                         jvalue new_value);

  void VectorClockTick();

  void SynchronizeVectorClocks(VectorClock &other);

 private:
  TraceLog trace_log_;
  int64_t thread_id_;
  int64_t counter_;
  std::map<int64_t, int64_t> counters_;
  VectorClock vector_clock_;
};

}  // namespace phasicj::tracelogger::core

#endif  // PHASICJ_TRACELOGGER_CORE_TRACE_H_
