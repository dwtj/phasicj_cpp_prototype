// Copyright 2019 David Johnston

// The `TraceManager` controls creation, storage, retrieval, and deletion of
// `Trace` instances, one per live JVM thread.

#ifndef PHASICJ_TRACELOGGER_TRACE_MANAGER_H
#define PHASICJ_TRACELOGGER_TRACE_MANAGER_H

#include <filesystem>

#include "phasicj/tracelogger/trace.h"

namespace phasicj::tracelogger {

using ::std::filesystem::path;

class TraceManager {
 public:
  TraceManager(jvmtiEnv* jvmti_env, std::filesystem::path trace_log_dir);
  void AllocateTrace(jvmtiEnv& jvmti_env, JNIEnv& jni_env, jthread thread);
  void FreeTrace();
  Trace& GetTrace() const;
  bool TraceExists() const;

 private:
  static constexpr jthread CURRENT_THREAD = static_cast<jthread>(NULL);

  jvmtiEnv* jvmti_env_;
  std::filesystem::path trace_log_dir_;

  Trace* GetTracePtr() const;
  void SetTracePtr(Trace* trace);

  path TraceLogPathFor(long thread_id);
};

}  // namespace phasicj::tracelogger

#endif  // PHASICJ_TRACELOGGER_TRACE_MANAGER_H_
