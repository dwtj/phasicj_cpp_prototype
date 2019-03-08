// Copyright 2019 David Johnston

#include <stdexcept>

#include "boost/log/trivial.hpp"

#include "phasicj/tracelogger/jvmticonfig/global_handler.h"
#include "phasicj/tracelogger/jvmticonfig/local_handler.h"
#include "phasicj/util/jvmti/threads.h"

namespace phasicj::tracelogger::jvmticonfig {

using ::std::runtime_error;

void GlobalHandler::ThreadStart(jvmtiEnv* jvmti_env,
                                JNIEnv* jni_env,
                                jthread thread) {
  LocalHandler::EmbedNew(*jvmti_env, *jni_env, thread);
  // TODO(dwtj): What else?
}

void GlobalHandler::ThreadEnd(jvmtiEnv* jvmti_env,
                              JNIEnv* jni_env,
                              jthread thread) {
  LocalHandler::DeleteEmbedded(*jvmti_env);
  // TODO(dwtj): What else?
}

void GlobalHandler::ClassPrepare(jvmtiEnv* jvmti_env,
                                 JNIEnv* jni_env,
                                 jthread thread,
                                 jclass klass) {
  // TODO(dwtj): Inspect this class's bytecode, and configure the JVMTI
  //  environment to emit relevant events from this class. In particular,
  //  - set breakpoints just after each monitor entry.
  //  - set field access/modification watches on volatile variables.

  // TODO(dwtj): Is `ClassPrepare` called on class redefinition. If not, then
  //  the invariant that breakpoints & field watches are set will not be
  //  preserved.
}

void GlobalHandler::VolatileFieldAccess(jvmtiEnv* jvmti_env,
                                        JNIEnv* jni_env,
                                        jthread thread,
                                        jmethodID method,
                                        jlocation location,
                                        jclass field_klass,
                                        jobject object,
                                        jfieldID field) {
  // TODO: Accessing a volatile variable
}

void GlobalHandler::VolatileFieldModification(jvmtiEnv* jvmti_env,
                                              JNIEnv* jni_env,
                                              jthread thread,
                                              jmethodID method,
                                              jlocation location,
                                              jclass field_klass,
                                              jobject object,
                                              jfieldID field,
                                              char signature_type,
                                              jvalue new_value) {
  LocalHandler& local_handler = LocalHandler::Embedded(*jvmti_env);
  local_handler.VectorClockTick();
}

void GlobalHandler::ObjectFree(jvmtiEnv* jvmti_env, jlong tag) {
  // TODO: Consider freeing objects asynchronously with a work queue.
}

void GlobalHandler::VMObjectAlloc(jvmtiEnv* jvmti_env,
                                  JNIEnv* jni_env,
                                  jthread thread,
                                  jobject object,
                                  jclass object_klass,
                                  jlong size) {
  // TODO
}

void GlobalHandler::EmbedNew(jvmtiEnv& jvmti_env) {
  auto Error = [](auto msg) {
    BOOST_LOG_TRIVIAL(error) << msg;
    throw runtime_error{msg};
  };

  GlobalHandler* handler{};
  jvmtiError err{};
  err =
      jvmti_env.GetEnvironmentLocalStorage(reinterpret_cast<void**>(&handler));
  switch (err) {
    case JVMTI_ERROR_NONE:
      if (handler == nullptr) {
        // Storage was empty. Ok to embed a new handler here.
        break;
      } else {
        Error("This thread's thread-local storage is already in use.");
      }
    case JVMTI_ERROR_NULL_POINTER:
      Error("`data_ptr == nullptr`.");
    // TODO: Give better descriptions for universal errors.
    default:
      Error("JVMTI returned an unexpected error code.");
  }

  // Try to allocate, initialize, and store a new `LocalHandler`.
  handler = new GlobalHandler();
  err = jvmti_env.SetEnvironmentLocalStorage(reinterpret_cast<void*>(&handler));
  switch (err) {
    case JVMTI_ERROR_NONE:
      // The new handler was stored successfully.
      return;
    case JVMTI_ERROR_INVALID_THREAD:
      Error("The given thread is not valid.");
    case JVMTI_ERROR_THREAD_NOT_ALIVE:
      Error("The given thread is not alive.");
    // TODO: Give better descriptions for universal errors.
    default:
      Error("JVMTI returned an unexpected error code.");
  }
}

void GlobalHandler::DeleteEmbedded(jvmtiEnv& jvmti_env) {
  constexpr auto Error = [](auto msg) {
    BOOST_LOG_TRIVIAL(error) << msg;
    throw runtime_error{msg};
  };

  GlobalHandler* handler{};
  jvmtiError err{};
  err =
      jvmti_env.GetEnvironmentLocalStorage(reinterpret_cast<void**>(&handler));
  switch (err) {
    case JVMTI_ERROR_NONE:
      break;  // The handler was successfully retrieved.
    // TODO: Give better descriptions for universal errors.
    default:
      Error("JVMTI returned an unexpected error code.");
  }

  delete handler;

  // Null old handler pointer.
  err = jvmti_env.SetEnvironmentLocalStorage(nullptr);
  switch (err) {
    case JVMTI_ERROR_NONE:
      return;  // Old handler pointer successfully nulled.
    case JVMTI_ERROR_INVALID_THREAD:
      Error("Current thread is invalid.");
    case JVMTI_ERROR_THREAD_NOT_ALIVE:
      Error("Current thread is not alive.");
    // TODO: Give better descriptions for universal errors.
    default:
      Error("JVMTI returned an unexpected error code.");
  }
}

GlobalHandler& GlobalHandler::Embedded(jvmtiEnv& jvmti_env) {
  constexpr auto CURRENT_THREAD = nullptr;
  constexpr auto Error = [](auto msg) {
    BOOST_LOG_TRIVIAL(error) << msg;
    throw runtime_error{msg};
  };

  GlobalHandler* handler{};
  jvmtiError err{};
  err = jvmti_env.GetThreadLocalStorage(CURRENT_THREAD,
                                        reinterpret_cast<void**>(&handler));
  switch (err) {
    case JVMTI_ERROR_NONE:
      break;  // Embedded handler was successfully retrieved
    case JVMTI_ERROR_NULL_POINTER:
      Error("This thread does not have an embedded handler.");
    // TODO: Give better descriptions for universal errors.
    default:
      Error("JVMTI returned an unexpected error code.");
  }

  return *handler;
}

}  // namespace phasicj::tracelogger::jvmticonfig
