// Copyright 2019 David Johnston

// Declares the `GlobalHandler` class.
//
// ## `GobalHandler` Responsibilities
//
// - `GlobalHandler` is the immediate handler for those JVMTI events which
//   cannot be handled thread-locally, that is, those events which require
//   synchronization with other event-handling threads.
//
// - `GlobalHandler` is the root container for thread-global state, that is,
//   state that is accessed by various event-handling threads (e.g. a JVM
//   monitor's vector clock).
//
// ## A Single `GlobalHandler` Instance Can Be Embedded in a JVMTI environment
//
// For the trace logger, a `GlobalHandler` instance needs to be accessed across
// different JVMTI callbacks by different threads. Rather than using, say,
// global static storage, a single `GlobalHandler` instance is stored inside of
// a JVMTI environment instance, specifically, in a JVMTI environment's
// environment-local storage [1]. We say that a `GlobalHandler` stored in this
// way is embedded" in this JVMTI environment. Thus, when JVMTI callback occurs
// on a thread, that thread can lookup the `GlobalHandler` instance "embedded"
// in the given JVMTI environment and pass along the event.
//
// The `GlobalHandler` class defines a number of static helper methods, to
// allocate, initialize, lookup, and destroy the `GlobalHandler` instance
// embedded in a JVMTI environment.
//
// [1](https://docs.oracle.com/en/java/javase/11/docs/specs/jvmti.html#GetEnvironmentLocalStorage)

#ifndef PHASICJ_TRACELOGGER_JVMTICONFIG_GLOBAL_HANDLER_H_
#define PHASICJ_TRACELOGGER_JVMTICONFIG_GLOBAL_HANDLER_H_

#include "jni.h"
#include "jvmti.h"

namespace phasicj::tracelogger::jvmticonfig {

class GlobalHandler {
 public:
  void ThreadStart(jvmtiEnv* jvmti_env, JNIEnv* jni_env, jthread thread);

  void ThreadEnd(jvmtiEnv* jvmti_env, JNIEnv* jni_env, jthread thread);

  void ClassPrepare(jvmtiEnv* jvmti_env,
                    JNIEnv* jni_env,
                    jthread thread,
                    jclass klass);

  void VolatileFieldAccess(jvmtiEnv* jvmti_env,
                           JNIEnv* jni_env,
                           jthread thread,
                           jmethodID method,
                           jlocation location,
                           jclass field_klass,
                           jobject object,
                           jfieldID field);

  void VolatileFieldModification(jvmtiEnv* jvmti_env,
                                 JNIEnv* jni_env,
                                 jthread thread,
                                 jmethodID method,
                                 jlocation location,
                                 jclass field_klass,
                                 jobject object,
                                 jfieldID field,
                                 char signature_type,
                                 jvalue new_value);

  void ObjectFree(jvmtiEnv* jvmti_env, jlong tag);

  void VMObjectAlloc(jvmtiEnv* jvmti_env,
                     JNIEnv* jni_env,
                     jthread thread,
                     jobject object,
                     jclass object_klass,
                     jlong size);

  // Allocates and initializes a new `GlobalHandler` instance and embeds it into
  // the given JVMTI environment.
  //
  // If anything was previously stored in the this JVMTI environment's
  // environment local storage, a `std::runtime_error` will be thrown.
  static void EmbedNew(jvmtiEnv& jvmti_env);

  // Retrieves and deletes the current thread's embedded `GlobalHandler`. Also
  // sets the current environment-local storage to `nullptr`.
  static void DeleteEmbedded(jvmtiEnv& jvmti_env);

  // Retrieves the currently embedded `GlobalHandler`.
  static GlobalHandler& Embedded(jvmtiEnv& jvmti_env);
};

}  // namespace phasicj::tracelogger::jvmticonfig

#endif  // PHASICJ_TRACELOGGER_JVMTICONFIG_GLOBAL_HANDLER_H_
