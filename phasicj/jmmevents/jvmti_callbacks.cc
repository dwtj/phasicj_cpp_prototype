// Copyright 2019 David Johnston

#include "jni.h"
#include "jvmti.h"

void JNICALL phasicj_jmmevents_ThreadStart(jvmtiEnv* jvmti_env,
                                           JNIEnv* jni_env,
                                           jthread thread) {
  // TODO(dwtj): Replace with refactored receiver
  // Agent::EmbeddedReciever(*jvmti_env).ThreadStart(*jvmti_env, *jni_env,
  // thread);
}

void JNICALL phasicj_jmmevents_ThreadEnd(jvmtiEnv* jvmti_env,
                                         JNIEnv* jni_env,
                                         jthread thread) {
  // TODO(dwtj): Replace with refactored receiver
  // Agent::EmbeddedReciever(*jvmti_env).ThreadEnd(*jvmti_env, *jni_env,
  // thread);
}

void JNICALL phasicj_jmmevents_ClassPrepare(jvmtiEnv* jvmti_env,
                                            JNIEnv* jni_env,
                                            jthread thread,
                                            jclass klass) {
  // TODO(dwtj): Replace with refactored receiver
  /*
  Agent::EmbeddedReciever(*jvmti_env).ClassPrepare(*jvmti_env,
                                              *jni_env,
                                              thread,
                                              klass);
                                              */
}

void JNICALL phasicj_jmmevents_FieldAccess(jvmtiEnv* jvmti_env,
                                           JNIEnv* jni_env,
                                           jthread thread,
                                           jmethodID method,
                                           jlocation location,
                                           jclass field_klass,
                                           jobject object,
                                           jfieldID field) {
  // TODO(dwtj): Replace with refactored receiver
  /*
  Agent::EmbeddedReciever(*jvmti_env).FieldAccess(*jvmti_env,
                                             *jni_env,
                                             thread,
                                             method,
                                             location,
                                             field_klass,
                                             object,
                                             field);
                                             */
}

void JNICALL phasicj_jmmevents_FieldModification(jvmtiEnv* jvmti_env,
                                                 JNIEnv* jni_env,
                                                 jthread thread,
                                                 jmethodID method,
                                                 jlocation location,
                                                 jclass field_klass,
                                                 jobject object,
                                                 jfieldID field,
                                                 char signature_type,
                                                 jvalue new_value) {
  // TODO(dwtj): Replace with refactored receiver
  /*
  Agent::EmbeddedReciever(*jvmti_env).FieldModification(*jvmti_env,
                                                   *jni_env,
                                                   thread,
                                                   method,
                                                   location,
                                                   field_klass,
                                                   object,
                                                   field,
                                                   signature_type,
                                                   new_value);
                                                   */
}

void JNICALL phasicj_jmmevents_ObjectFree(jvmtiEnv* jvmti_env, jlong tag) {
  // TODO(dwtj): Replace with refactored receiver
  // Agent::EmbeddedReciever(*jvmti_env).ObjectFree(*jvmti_env, tag);
}

void JNICALL phasicj_jmmevents_VMObjectAlloc(jvmtiEnv* jvmti_env,
                                             JNIEnv* jni_env,
                                             jthread thread,
                                             jobject object,
                                             jclass object_klass,
                                             jlong size) {
  // TODO(dwtj): Replace with refactored receiver
  /*
  Agent::EmbeddedReciever(*jvmti_env).VMObjectAlloc(*jvmti_env,
                                               *jni_env,
                                               thread,
                                               object,
                                               object_klass,
                                               size);
                                               */
}

// TODO(dwtj): The documentation of the `VMDeath` JVMTI event says that no
//  events will be triggered on a JVMTI environment after a `VMDeath` event.
//  However, might there be events which are still running? Presumably,
//  background threads are still allowed to run, but I don't think that I'll
//  be using any of those.
void JNICALL phasicj_jmmevents_VMDeath(jvmtiEnv* jvmti_env, JNIEnv* jni_env) {
  // TODO(dwtj): Everything!
  // DeleteEmbeddedTraceLogger(jvmti_env);
  // jvmti_env.DisposeEnvironment();
}
