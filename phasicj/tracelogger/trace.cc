// Copyright 2019 David Johnston

#include "boost/numeric/conversion/cast.hpp"

#include "jni.h"
#include "jvmti.h"

#include "phasicj/tracelogger/trace.h"

namespace phasicj::tracelogger {

using ::boost::numeric_cast;

Trace::Trace(jlong thread_id, path&& log_path)
    : trace_log_{log_path},
      thread_id_{numeric_cast<int64_t>(thread_id)},
      counter_{0},
      counters_{},
      vector_clock_{} {}

void Trace::NonVolatileRead(jvmtiEnv *jvmti_env,
                     JNIEnv *jni_env,
                     jthread thread,
                     jmethodID method,
                     jlocation location,
                     jclass field_klass,
                     jobject object,
                     jfieldID field) {
  // TODO(dwtj)
}

void Trace::NonVolatileWrite(jvmtiEnv *jvmti_env,
                         JNIEnv *jni_env,
                         jthread thread,
                         jmethodID method,
                         jlocation location,
                         jclass field_klass,
                         jobject object,
                         jfieldID field,
                         char signature_type,
                         jvalue new_value) {
  // TODO(dwtj)
}

void Trace::VolatileRead(jvmtiEnv *jvmti_env,
                     JNIEnv *jni_env,
                     jthread thread,
                     jmethodID method,
                     jlocation location,
                     jclass field_klass,
                     jobject object,
                     jfieldID field) {
  // TODO(dwtj)
}

void Trace::VolatileWrite(jvmtiEnv *jvmti_env,
                         JNIEnv *jni_env,
                         jthread thread,
                         jmethodID method,
                         jlocation location,
                         jclass field_klass,
                         jobject object,
                         jfieldID field,
                         char signature_type,
                         jvalue new_value) {
  // TODO(dwtj)
}

void Trace::VectorClockTick() {
  vector_clock_.Tick(thread_id_);
}

}  // namespace phasicj::tracelogger
