// Copyright 2019 David Johnston

#include "jni.h"
#include "jvmti.h"

#include "phasicj/tracelogger/core/trace_logger.h"

namespace phasicj::tracelogger::core {

TraceLogger::TraceLogger(VectorClockManager* vector_clock_manager,
                         TagManager* tag_manager,
                         TraceManager* trace_manager) :
    vector_clock_manager_{vector_clock_manager},
    tag_manager_{tag_manager},
    trace_manager_{trace_manager} { }

void TraceLogger::ThreadStart(jvmtiEnv* jvmti_env, JNIEnv* jni_env, jthread thread) {
  // TODO(dwtj)
}

void TraceLogger::ThreadEnd(jvmtiEnv* jvmti_env,
                              JNIEnv* jni_env,
                              jthread thread) {
  // TODO(dwtj)
}

void TraceLogger::VolatileRead(jvmtiEnv& jvmti_env,
                  JNIEnv& jni_env,
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

void TraceLogger::VolatileWrite(jvmtiEnv& jvmti_env,
                   JNIEnv& jni_env,
                   jthread thread,
                   jmethodID method,
                   jlocation location,
                   jclass field_klass,
                   jobject object,
                   jfieldID field) {
  // TODO(dwtj)
}

void TraceLogger::NonVolatileRead(jvmtiEnv& jvmti_env,
                     JNIEnv& jni_env,
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

void TraceLogger::NonVolatileWrite(jvmtiEnv& jvmti_env,
                      JNIEnv& jni_env,
                      jthread thread,
                      jmethodID method,
                      jlocation location,
                      jclass field_klass,
                      jobject object,
                      jfieldID field) {
  // TODO(dwtj)
}

}  // namespace phasicj::tracelogger::jvmticonfig
