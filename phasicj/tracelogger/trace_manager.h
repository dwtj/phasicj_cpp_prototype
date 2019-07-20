// Copyright 2019 David Johnston

// The `TraceManager` controls the creation and deletion of `Trace` instances,
// one per live JVM thread.

#ifndef PHASICJ_TRACELOGGER_TRACE_MANAGER_H_
#define PHASICJ_TRACELOGGER_TRACE_MANAGER_H_

#include <filesystem>

#include "phasicj/jmmevents/jmm_action_listener.h"
#include "phasicj/jmmevents/jmm_action_listener_manager.h"

#include "phasicj/tracelogger/trace.h"

namespace phasicj::tracelogger {

class TraceManager : ::phasicj::jmmevents::JmmActionListenerManager {
 public:
  explicit TraceManager(::std::filesystem::path log_dir);

  virtual ::phasicj::jmmevents::JmmActionListener* New(JvmThreadId id) override;
  virtual void Free(JvmThreadId thread_id) override;

 private:
  std::filesystem::path log_dir_;
  path TraceLogPathFor(long thread_id);
};

}  // namespace phasicj::tracelogger

#endif  // PHASICJ_TRACELOGGER_TRACE_MANAGER_H_
