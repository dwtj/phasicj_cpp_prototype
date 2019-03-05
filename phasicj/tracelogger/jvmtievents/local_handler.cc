// Copyright 2019 David Johnston

#include <cstdint>
#include <ostream>
#include <stdexcept>
#include <string>

#include "boost/log/trivial.hpp"
#include "boost/numeric/conversion/cast.hpp"

#include "jni.h"
#include "jvmti.h"

#include "phasicj/tracelogger/jvmtievents/local_handler.h"
#include "phasicj/util/jvmti/threads.h"

using ::std::ostream;
using ::std::runtime_error;
using ::std::string;

using ::boost::numeric_cast;
using ::phasicj::util::jvmti::GetThreadId;

namespace phasicj::tracelogger::jvmtievents {

LocalHandler::LocalHandler(jlong thread_id)
    : thread_id_(numeric_cast<int64_t>(thread_id)),
      counter_(0),
      counters_(),
      vector_clock_() {}

void LocalHandler::FieldAccess(jvmtiEnv* jvmti_env,
                               JNIEnv* jni_env,
                               jthread thread,
                               jmethodID method,
                               jlocation location,
                               jclass field_klass,
                               jobject object,
                               jfieldID field) {
  VectorClockTick();
  // TODO: Log this event.
}

void LocalHandler::FieldModification(jvmtiEnv* jvmti_env,
                                     JNIEnv* jni_env,
                                     jthread thread,
                                     jmethodID method,
                                     jlocation location,
                                     jclass field_klass,
                                     jobject object,
                                     jfieldID field,
                                     char signature_type,
                                     jvalue new_value) {
  VectorClockTick();
  // TODO: Log this event.
}

void LocalHandler::VectorClockTick() {
  vector_clock_.Tick(thread_id_);
}

void LocalHandler::EmbedNew(jvmtiEnv& jvmti_env,
                            JNIEnv& jni_env,
                            jthread thread) {
  auto Error = [](auto msg) {
    BOOST_LOG_TRIVIAL(error) << msg;
    throw runtime_error{msg};
  };

  // Get this thread's ID by calling `Thread.threadId()`.
  auto thread_id = GetThreadId(jni_env, thread);
  if (!thread_id) {
    Error("Failed to get this Java Thread's `threadId()`.");
  }

  LocalHandler* handler{};
  jvmtiError err{};
  err = jvmti_env.GetThreadLocalStorage(thread,
                                        reinterpret_cast<void**>(&handler));
  switch (err) {
    case JVMTI_ERROR_NONE:
      if (handler == nullptr) {
        break;  // Storage was empty. Ok to embed a new handler here.
      } else {
        Error("This thread's thread-local storage is already in use.");
      }
    case JVMTI_ERROR_NULL_POINTER:
      Error("`data_ptr == nullptr`.");
    case JVMTI_ERROR_INVALID_THREAD:
      Error("Given thread is invalid.");
    case JVMTI_ERROR_THREAD_NOT_ALIVE:
      Error("The given thread is not alive");
    // TODO: Give better descriptions for universal errors.
    default:
      Error("JVMTI returned an unexpected error code.");
  }

  // Try to allocate, initialize, and store a new `LocalHandler`.
  handler = new LocalHandler(thread_id.value());
  err = jvmti_env.SetThreadLocalStorage(thread,
                                        reinterpret_cast<void*>(handler));
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

void LocalHandler::DeleteEmbedded(jvmtiEnv& jvmti_env) {
  constexpr auto CURRENT_THREAD = nullptr;
  constexpr auto Error = [](auto msg) {
    BOOST_LOG_TRIVIAL(error) << msg;
    throw runtime_error{msg};
  };

  LocalHandler* handler{};
  jvmtiError err{};
  err = jvmti_env.GetThreadLocalStorage(CURRENT_THREAD,
                                        reinterpret_cast<void**>(&handler));
  switch (err) {
    case JVMTI_ERROR_NONE:
      break;  // The handler was successfully retrieved.
    case JVMTI_ERROR_INVALID_THREAD:
      Error("Current thread is invalid.");
    case JVMTI_ERROR_THREAD_NOT_ALIVE:
      Error("Current thread is not alive.");
    // TODO: Give better descriptions for universal errors.
    default:
      Error("JVMTI returned an unexpected error code.");
  }

  delete handler;

  // Null old handler pointer.
  err = jvmti_env.SetThreadLocalStorage(CURRENT_THREAD, nullptr);
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

LocalHandler& LocalHandler::Embedded(jvmtiEnv& jvmti_env) {
  constexpr auto CURRENT_THREAD = nullptr;
  constexpr auto Error = [](auto msg) {
    BOOST_LOG_TRIVIAL(error) << msg;
    throw runtime_error{msg};
  };

  LocalHandler* handler{};
  jvmtiError err{};
  err = jvmti_env.GetThreadLocalStorage(CURRENT_THREAD,
                                        reinterpret_cast<void**>(&handler));
  switch (err) {
    case JVMTI_ERROR_NONE:
      break;  // Embedded handler was successfully retrieved
    case JVMTI_ERROR_NULL_POINTER:
      Error("This thread does not have an embedded handler.");
    case JVMTI_ERROR_INVALID_THREAD:
      Error("JVMTI thinks that the current thread is invalid");
    case JVMTI_ERROR_THREAD_NOT_ALIVE:
      Error("The current thread is not alive (somehow).");
    // TODO: Give better descriptions for universal errors.
    default:
      Error("JVMTI returned an unexpected error code.");
  }

  return *handler;
}

}  // namespace phasicj::tracelogger::jvmtievents
