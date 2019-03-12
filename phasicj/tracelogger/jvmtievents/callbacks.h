// Copyright 2019 David Johnston

#ifndef PHASICJ_TRACELOGGER_JVMTIEVENTS_CALLBACKS_H_
#define PHASICJ_TRACELOGGER_JVMTIEVENTS_CALLBACKS_H_

#include "jni.h"
#include "jvmti.h"

void JNICALL ThreadStart(jvmtiEnv *jvmti_env, JNIEnv *jni_env, jthread thread);

void JNICALL ThreadEnd(jvmtiEnv *jvmti_env, JNIEnv *jni_env, jthread thread);

void JNICALL ClassPrepare(jvmtiEnv *jvmti_env,
                          JNIEnv *jni_env,
                          jthread thread,
                          jclass klass);

void JNICALL FieldAccess(jvmtiEnv *jvmti_env,
                         JNIEnv *jni_env,
                         jthread thread,
                         jmethodID method,
                         jlocation location,
                         jclass field_klass,
                         jobject object,
                         jfieldID field);

void JNICALL FieldModification(jvmtiEnv *jvmti_env,
                               JNIEnv *jni_env,
                               jthread thread,
                               jmethodID method,
                               jlocation location,
                               jclass field_klass,
                               jobject object,
                               jfieldID field,
                               char signature_type,
                               jvalue new_value);

void JNICALL ObjectFree(jvmtiEnv *jvmti_env, jlong tag);

void JNICALL VMObjectAlloc(jvmtiEnv *jvmti_env,
                           JNIEnv *jni_env,
                           jthread thread,
                           jobject object,
                           jclass object_klass,
                           jlong size);

void JNICALL VMDeath(jvmtiEnv *jvmti_env, JNIEnv *jni_env);

#endif  // PHASICJ_TRACELOGGER_JVMTIEVENTS_CALLBACKS_H_