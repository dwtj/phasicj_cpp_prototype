// Copyright 2019 David Johnston

// Declares the `LocalHandler` class.
//
// ## `LocalHandler` Responsibilities
//
// - `LocalHandler` is the immediate handler for those JVMTI events which can
//   be handled thread-locally, that is, without any synchronization with other
//   event-handling threads.
//
// - `LocalHandler` is the root container for any thread-local state, that is,
//   state that is only ever accessed by a single event-handling thread. For
//   example, a thread's local vector clock is thread-local state.
//
// ## `LocalHandler` Instances Can Be "Embedded" in a JVMTI Environment
//
// For the trace logger, a `LocalHandler` instance needs to be accessed across
// different JVMTI callbacks by a single thread. Rather than using, say, global
// static storage, `LocalHandler` instances are stored inside of a JVMTI
// environment instance, specifically, a JVMTI environment's thread-local
// storage [1]. We say that a `LocalHandler` stored in this way is "embedded" in
// this JVMTI environment. Thus, when JVMTI callback occurs w.r.t. a particular
// JVMTI environment and on a particular JVMTI thread, this thread can lookup a
// `LocalHandler` instance "embedded" in this JVMTI environment and pass along
// the event.
//
// The `LocalHandler` class defines a number of static helper methods, to
// allocate, initialize, lookup, and destroy `LocalHandler` instances embedded
// in a JVMTI environment.
//
// [1](https://docs.oracle.com/en/java/javase/11/docs/specs/jvmti.html#GetThreadLocalStorage)

#ifndef PHASICJ_TRACELOGGER_JVMTIEVENTS_LOCAL_HANDER_H_
#define PHASICJ_TRACELOGGER_JVMTIEVENTS_LOCAL_HANDER_H_

#include <map>

#include "phasicj/vectorclock.pb.h"

#include "jni.h"
#include "jvmti.h"

namespace phasicj::tracelogger::jvmtievents {

class LocalHandler {
 public:
  explicit LocalHandler(jlong thread_id);

  // Called to indicate a that a non-volatile field access event is about to
  // be performed by this thread.
  void FieldAccess(jvmtiEnv* jvmti_env,
                   JNIEnv* jni_env,
                   jthread thread,
                   jmethodID method,
                   jlocation location,
                   jclass field_klass,
                   jobject object,
                   jfieldID field);

  // Called to indicate that a non-volatile field modification event is about to
  // be performed by this thread.
  void FieldModification(jvmtiEnv* jvmti_env,
                         JNIEnv* jni_env,
                         jthread thread,
                         jmethodID method,
                         jlocation location,
                         jclass field_klass,
                         jobject object,
                         jfieldID field,
                         char signature_type,
                         jvalue new_value);

  void VectorClockTick();

  void SynchronizeVectorClocks(VectorClock& other);

  // Allocates and initializes a new `LocalHandler` instance for the given
  // thread and embeds it in the current thread's thread-local storage within
  // the given JVMTI environment.
  //
  // If any non-null value is already stored in the given thread's thread-local
  // storage, then a `std::runtime_error` will be thrown.
  static void EmbedNew(jvmtiEnv& jvmti_env, JNIEnv& jni_env, jthread thread);

  // Retrieves and deletes the current thread's embedded `LocalHandler`. Also
  // sets the current thread's thread-local storage to `nullptr`.
  static void DeleteEmbedded(jvmtiEnv& jvmti_env);

  // Retrieves this thread's the currently embedded `LocalHandler`.
  static LocalHandler& Embedded(jvmtiEnv& jvmti_env);

 private:
  ::google::protobuf::uint64 thread_id_;
  ::google::protobuf::uint64 counter_;
  std::map<::google::protobuf::uint64, ::google::protobuf::uint64> counters_;
  VectorClock vector_clock_;
};

}  // namespace phasicj::tracelogger::jvmtievents

#endif  // PHASICJ_TRACELOGGER_JVMTIEVENTS_LOCAL_HANDER_H_
