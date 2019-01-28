// Copyright 2019 David Johnston

// This function defines the functions which are meant to be registered with
// JVMTI as event callbacks. See the header file for more info.

#include "jni.h"
#include "jvmti.h"

#include "phasicj/tracelogger/jvmtievents/global_handler.h"
#include "phasicj/tracelogger/jvmtievents/local_handler.h"
#include "phasicj/util/jvmti/misc.h"

#include "phasicj/tracelogger/jvmtievents/jvmti_callbacks.h"

namespace phasicj::tracelogger::jvmtievents {

using ::phasicj::util::jvmti::IsFieldVolatile;

void JNICALL ThreadStart(jvmtiEnv* jvmti_env, JNIEnv* jni_env, jthread thread) {
  GlobalHandler::Embedded(*jvmti_env).ThreadStart(jvmti_env, jni_env, thread);
}

void JNICALL ThreadEnd(jvmtiEnv* jvmti_env, JNIEnv* jni_env, jthread thread) {
  GlobalHandler::Embedded(*jvmti_env).ThreadEnd(jvmti_env, jni_env, thread);
}

void JNICALL ClassPrepare(jvmtiEnv* jvmti_env,
                          JNIEnv* jni_env,
                          jthread thread,
                          jclass klass) {
  GlobalHandler::Embedded(*jvmti_env)
      .ClassPrepare(jvmti_env, jni_env, thread, klass);
}

void JNICALL FieldAccess(jvmtiEnv* jvmti_env,
                         JNIEnv* jni_env,
                         jthread thread,
                         jmethodID method,
                         jlocation location,
                         jclass field_klass,
                         jobject object,
                         jfieldID field) {
  LocalHandler::Embedded(*jvmti_env)
      .FieldAccess(jvmti_env,
                   jni_env,
                   thread,
                   method,
                   location,
                   field_klass,
                   object,
                   field);
}

void JNICALL FieldModification(jvmtiEnv* jvmti_env,
                               JNIEnv* jni_env,
                               jthread thread,
                               jmethodID method,
                               jlocation location,
                               jclass field_klass,
                               jobject object,
                               jfieldID field,
                               char signature_type,
                               jvalue new_value) {
  // If this field is volatile, synchronization is needed; so forward the event
  // to the global handler. Otherwise, forward it to the local handler.
  // TODO(dwtj): Consider using a thread-local cache for this decision.
  if (IsFieldVolatile(jvmti_env, field_klass, field)) {
    GlobalHandler::Embedded(*jvmti_env)
        .VolatileFieldModification(jvmti_env,
                                   jni_env,
                                   thread,
                                   method,
                                   location,
                                   field_klass,
                                   object,
                                   field,
                                   signature_type,
                                   new_value);
  } else {
    LocalHandler::Embedded(*jvmti_env);
  }
}

void JNICALL ObjectFree(jvmtiEnv* jvmti_env, jlong tag) {
  GlobalHandler::Embedded(*jvmti_env).ObjectFree(jvmti_env, tag);
}

void JNICALL VMObjectAlloc(jvmtiEnv* jvmti_env,
                           JNIEnv* jni_env,
                           jthread thread,
                           jobject object,
                           jclass object_klass,
                           jlong size) {
  GlobalHandler::Embedded(*jvmti_env)
      .VMObjectAlloc(jvmti_env, jni_env, thread, object, object_klass, size);
}

}  // namespace phasicj::tracelogger::jvmtievents
