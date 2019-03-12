// Copyright 2019 David Johnston

#include "jni.h"
#include "jvmti.h"

#include "phasicj/tracelogger/jvmtievents/receiver.h"

namespace phasicj::tracelogger::jvmtievents {

using ::phasicj::tracelogger::jvmtievents::JvmtiEventManager;
using ::phasicj::tracelogger::core::TraceLogger;

JvmtiEventReceiver::JvmtiEventReceiver(JvmtiEventManager *event_manager,
                                       TraceLogger* trace_logger) :
                                       event_manager_{event_manager},
                                       trace_logger_{trace_logger} { }



void JvmtiEventReceiver::ThreadStart(jvmtiEnv& jvmti_env, JNIEnv& jni_env, jthread thread) {
  // TODO(dwtj)
}

void JvmtiEventReceiver::ThreadEnd(jvmtiEnv& jvmti_env, JNIEnv& jni_env, jthread thread) {
  // TODO(dwtj)
}

void JvmtiEventReceiver::ClassPrepare(jvmtiEnv& jvmti_env,
                          JNIEnv& jni_env,
                          jthread thread,
                          jclass klass) {
  // TODO(dwtj): Inspect this class's bytecode, and configure the JVMTI
  //  environment to emit relevant events from this class. In particular,
  //  - set breakpoints just after each monitor entry.
  //  - set field access/modification watches on volatile variables.

  // TODO(dwtj): Is `ClassPrepare` called on class redefinition. If not, then
  //  the invariant that breakpoints & field watches are set will not be
  //  preserved.

  // TODO(dwtj)
}

void JvmtiEventReceiver::FieldAccess(jvmtiEnv& jvmti_env,
                         JNIEnv& jni_env,
                         jthread thread,
                         jmethodID method,
                         jlocation location,
                         jclass field_klass,
                         jobject object,
                         jfieldID field) {
  // TODO(dwtj)
}

void JvmtiEventReceiver::FieldModification(jvmtiEnv& jvmti_env,
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

void JvmtiEventReceiver::ObjectFree(jvmtiEnv& jvmti_env, jlong tag) {
  // TODO(dwtj)
}

void JvmtiEventReceiver::VMObjectAlloc(jvmtiEnv& jvmti_env,
                           JNIEnv& jni_env,
                           jthread thread,
                           jobject object,
                           jclass object_klass,
                           jlong size) {
  // TODO(dwtj)
}

void JvmtiEventReceiver::VMDeath(jvmtiEnv& jvmti_env, JNIEnv& jni_env) {
  // TODO(dwtj)
}

}
