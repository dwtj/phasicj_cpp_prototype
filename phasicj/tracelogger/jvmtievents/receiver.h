// Copyright 2019 David Johnston

// `Reciever` receives the low-level JVMTI events and forwards them to the
// appropriate `tracelogger` component, possibly as a higher-level event. For
// example, a JVMTI `FieldModification` event is forwarded to the `TraceLogger`
// component as either a `VolatileWrite` or a `NonVolatileWrite`.

#ifndef PHASICJ_EVENT_ADAPTER_H
#define PHASICJ_EVENT_ADAPTER_H

#include "jni.h"
#include "jvmti.h"

#include "phasicj/tracelogger/core/trace_logger.h"
#include "phasicj/tracelogger/jvmtievents/manager.h"

namespace phasicj::tracelogger::jvmtievents {

using ::phasicj::tracelogger::core::TraceLogger;
using ::phasicj::tracelogger::jvmtievents::JvmtiEventManager;

class JvmtiEventReceiver {
 public:

  JvmtiEventReceiver(JvmtiEventManager* event_manager,
                     TraceLogger* trace_logger);

  void ThreadStart(jvmtiEnv& jvmti_env, JNIEnv& jni_env, jthread thread);

  void ThreadEnd(jvmtiEnv& jvmti_env, JNIEnv& jni_env, jthread thread);

  void ClassPrepare(jvmtiEnv& jvmti_env,
                    JNIEnv& jni_env,
                    jthread thread,
                    jclass klass);

  void FieldAccess(jvmtiEnv& jvmti_env,
                   JNIEnv& jni_env,
                   jthread thread,
                   jmethodID method,
                   jlocation location,
                   jclass field_klass,
                   jobject object,
                   jfieldID field);

  void FieldModification(jvmtiEnv& jvmti_env,
                         JNIEnv& jni_env,
                         jthread thread,
                         jmethodID method,
                         jlocation location,
                         jclass field_klass,
                         jobject object,
                         jfieldID field,
                         char signature_type,
                         jvalue new_value);

  void ObjectFree(jvmtiEnv& jvmti_env, jlong tag);

  void VMObjectAlloc(jvmtiEnv& jvmti_env,
                     JNIEnv& jni_env,
                     jthread thread,
                     jobject object,
                     jclass object_klass,
                     jlong size);

  void VMDeath(jvmtiEnv& jvmti_env, JNIEnv& jni_env);

 private:
  JvmtiEventManager* event_manager_;
  TraceLogger* trace_logger_;
};

}  // namespace phasicj::tracelogger::jvmtievents

#endif //PHASICJ_EVENT_ADAPTER_H
