// Copyright 2019 David Johnston

#ifndef PHASICJ_TRACELOGGER_CORE_AGENT_H_
#define PHASICJ_TRACELOGGER_CORE_AGENT_H_

#include "jni.h"
#include "jvmti.h"

#include "phasicj/tracelogger/core/vector_clock_manager.h"
#include "phasicj/tracelogger/core/tag_manager.h"
#include "phasicj/tracelogger/core/trace_manager.h"

namespace phasicj::tracelogger::core {

class TraceLogger {
 public:
  TraceLogger(VectorClockManager* vector_clock_manager,
              TagManager* tag_manager,
              TraceManager* trace_manager);


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

 private:
  VectorClockManager* vector_clock_manager_;
  TagManager* tag_manager_;
  TraceManager* trace_manager_;
};

}  // namespace phasicj::tracelogger::jvmticonfig

#endif  // PHASICJ_TRACELOGGER_CORE_AGENT_H_
