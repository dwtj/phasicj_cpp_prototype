// Copyright 2019 David Johnston

#include <stdexcept>
#include <boost/filesystem/operations.hpp>

#include "jni.h"
#include "jvmti.h"

#include "phasicj/tracelogger/trace_logger.h"

namespace phasicj::tracelogger {

using ::std::runtime_error;
using ::std::filesystem::current_path;

// Attempts to create a new `jvmtiEnv` in this JVM and a new `TraceLogger`
// embedded in this `jvmtiEnv`.
void TraceLogger::AddNew(JavaVM &jvm) {
  auto jvmti_env{NewJvmtiEnv(jvm)};
  auto trace_logger{new TraceLogger(jvmti_env)};
}

TraceLogger::TraceLogger(jvmtiEnv* jvmti_env) :
    jvmti_env_{jvmti_env},
    jvmti_event_manager_{jvmti_env_},
    instance_manager_{jvmti_env},
    vector_clock_manager_{},
    trace_manager_{jvmti_env_, DefaultTraceLogDir()} { }

path TraceLogger::DefaultTraceLogDir() {
  return current_path();
}

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

}  // namespace phasicj::tracelogger
