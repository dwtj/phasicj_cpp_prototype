// Copyright 2019 David Johnston

// The `TraceManager` controls the creation and deletion of `Trace` instances,
// one per live JVM thread.

#ifndef PHASICJ_TRACELOGGER_TRACE_MANAGER_H_
#define PHASICJ_TRACELOGGER_TRACE_MANAGER_H_

#include <filesystem>

#include "phasicj/jmmevents/jmm_trace.h"
#include "phasicj/jmmevents/jmm_trace_manager.h"

#include "phasicj/tracelogger/vc_trace.h"

namespace phasicj::tracelogger {

class TraceEnhancerManager : public ::phasicj::jmmevents::JmmTraceManager {
 public:
  explicit TraceManager(::std::filesystem::path log_dir);

  ::phasicj::jmmevents::JmmTrace* New(JvmThreadId id) override;
  void Free(JvmThreadId thread_id) override;

 private:
  std::filesystem::path log_dir_;
  path TraceLogPathFor(long thread_id);
};

}  // namespace phasicj::tracelogger

#endif  // PHASICJ_TRACELOGGER_TRACE_MANAGER_H_
