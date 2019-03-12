// Copyright 2019 David Johnston

// TODO(dwtj): Java thread IDs may be re-used [1]. It doesn't appear that the
//  hotspot JVM does this, but some JVMTI-compliant JVM may do this. Thus, this
//  agent currently behaves incorrectly when thread IDs are reused. In
//  particular, the old thread's trace log file will be clobbered by the new
//  thread's trace log. Maybe I should at least check for thread ID reuse.
//
//  [1] https://docs.oracle.com/en/java/javase/11/docs/api/java.base/java/lang/Thread.html#getId()


#include <cassert>
#include <filesystem>
#include <stdexcept>

#include "boost/log/trivial.hpp"

#include "jvmti.h"

#include "phasicj/util/jvmti/threads.h"
#include "phasicj/tracelogger/core/trace.h"
#include "phasicj/tracelogger/core/trace_log.h"
#include "phasicj/tracelogger/core/trace_manager.h"

namespace phasicj::tracelogger::core {

using ::std::filesystem::path;
using ::std::move;
using ::std::runtime_error;
using ::std::to_string;
using ::phasicj::util::jvmti::GetThreadId;

TraceManager::TraceManager(jvmtiEnv* jvmti_env, path trace_log_dir) :
    jvmti_env_(jvmti_env),
    trace_log_dir_(move(trace_log_dir))
{
  if (jvmti_env == nullptr) {
    throw std::runtime_error{
      "Cannot construct trace manager with null JVMTI environment."
    };
  }
}

// It is an error if the given `jthread` does not represent the thread calling
// this function.
void TraceManager::AllocateTrace(jvmtiEnv& jvmti_env, JNIEnv& jni_env, jthread thread) {
  auto Error = [](auto msg) { throw runtime_error{msg}; };

  auto thread_id = GetThreadId(jni_env, thread);
  if (!thread_id) {
    Error("Failed to get this Java Thread's `threadId()`.");
  }

  if (GetTracePtr() != nullptr) {
    Error("This thread's thread-local storage is already in use.");
  }

  auto log_path {TraceLogPathFor(thread_id.value())};
  auto trace = new Trace{thread_id.value(), TraceLogPathFor(thread_id.value())};
  SetTracePtr(trace);
}

void TraceManager::FreeTrace() {
  assert(TraceExists());
  delete GetTracePtr();
  SetTracePtr(nullptr);
}

Trace& TraceManager::GetTrace() const {
  return *GetTracePtr();
}

bool TraceManager::TraceExists() const {
  return GetTracePtr() != nullptr;
}

Trace* TraceManager::GetTracePtr() const {
  constexpr auto Error = [](auto msg) {
    BOOST_LOG_TRIVIAL(error) << msg;
    throw runtime_error{msg};
  };

  Trace* trace;
  jvmtiError err;
  err = jvmti_env_->GetThreadLocalStorage(CURRENT_THREAD,
                                          reinterpret_cast<void**>(&trace));

  switch (err) {
    case JVMTI_ERROR_NONE:
    case JVMTI_ERROR_NULL_POINTER:
      break;
    case JVMTI_ERROR_INVALID_THREAD:
      Error("JVMTI thinks that the current thread is invalid");
    case JVMTI_ERROR_THREAD_NOT_ALIVE:
      Error("The current thread is not alive (somehow).");
    default:
      // TODO: Give better descriptions for universal errors.
      Error("JVMTI returned an unexpected error code.");
  }

  return trace;
}

void TraceManager::SetTracePtr(Trace* trace) {
  constexpr auto Error = [](auto msg) { throw runtime_error{msg}; };

  jvmtiError err = jvmti_env_->SetThreadLocalStorage(CURRENT_THREAD, reinterpret_cast<void*>(trace));

  switch (err) {
    case JVMTI_ERROR_NONE:
      break;  // The handler was successfully retrieved.
    case JVMTI_ERROR_INVALID_THREAD:
      Error("Current thread is invalid.");
    case JVMTI_ERROR_THREAD_NOT_ALIVE:
      Error("Current thread is not alive (somehow).");
    default:
      // TODO: Give better descriptions for universal errors.
      Error("JVMTI returned an unexpected error code.");
  }
}

// https://docs.oracle.com/en/java/javase/11/docs/api/java.base/java/lang/Thread.html#getId()
path TraceManager::TraceLogPathFor(long thread_id) {
  assert(thread_id > 0);
  return {(trace_log_dir_ / "thread_").concat(to_string(thread_id))};
}

}  // namespace phasicj::tracelogger::core
