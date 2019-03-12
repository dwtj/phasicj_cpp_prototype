// Copyright 2019 David Johnston

#include "jni.h"
#include "jvmti.h"

#include "phasicj/tracelogger/core/agent.h"

using ::phasicj::tracelogger::core::Agent;

void JNICALL ThreadStart(jvmtiEnv *jvmti_env, JNIEnv *jni_env, jthread thread) {
  Agent::ReceiverFor(*jvmti_env).ThreadStart(*jvmti_env, *jni_env, thread);
}

void JNICALL ThreadEnd(jvmtiEnv *jvmti_env, JNIEnv *jni_env, jthread thread) {
  Agent::ReceiverFor(*jvmti_env).ThreadEnd(*jvmti_env, *jni_env, thread);
}

void JNICALL ClassPrepare(jvmtiEnv *jvmti_env,
                          JNIEnv *jni_env,
                          jthread thread,
                          jclass klass) {
  Agent::ReceiverFor(*jvmti_env).ClassPrepare(*jvmti_env,
                                              *jni_env,
                                              thread,
                                              klass);
}

void JNICALL FieldAccess(jvmtiEnv *jvmti_env,
                         JNIEnv *jni_env,
                         jthread thread,
                         jmethodID method,
                         jlocation location,
                         jclass field_klass,
                         jobject object,
                         jfieldID field) {
  Agent::ReceiverFor(*jvmti_env).FieldAccess(*jvmti_env,
                                             *jni_env,
                                             thread,
                                             method,
                                             location,
                                             field_klass,
                                             object,
                                             field);
}

void JNICALL FieldModification(jvmtiEnv *jvmti_env,
                               JNIEnv *jni_env,
                               jthread thread,
                               jmethodID method,
                               jlocation location,
                               jclass field_klass,
                               jobject object,
                               jfieldID field,
                               char signature_type,
                               jvalue new_value) {
  Agent::ReceiverFor(*jvmti_env).FieldModification(*jvmti_env,
                                                   *jni_env,
                                                   thread,
                                                   method,
                                                   location,
                                                   field_klass,
                                                   object,
                                                   field,
                                                   signature_type,
                                                   new_value);
}

void JNICALL ObjectFree(jvmtiEnv *jvmti_env, jlong tag) {
  Agent::ReceiverFor(*jvmti_env).ObjectFree(*jvmti_env, tag);
}

void JNICALL VMObjectAlloc(jvmtiEnv *jvmti_env,
                           JNIEnv *jni_env,
                           jthread thread,
                           jobject object,
                           jclass object_klass,
                           jlong size) {
  Agent::ReceiverFor(*jvmti_env).VMObjectAlloc(*jvmti_env,
                                               *jni_env,
                                               thread,
                                               object,
                                               object_klass,
                                               size);
}

void JNICALL VMDeath(jvmtiEnv *jvmti_env, JNIEnv *jni_env) {
  Agent::ReceiverFor(*jvmti_env).VMDeath(*jvmti_env, *jni_env);
}
