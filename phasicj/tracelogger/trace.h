// Copyright 2019 David Johnston

#ifndef PHASICJ_TRACELOGGER_TRACE_H_
#define PHASICJ_TRACELOGGER_TRACE_H_

#include "jni.h"
#include "jvmti.h"

#include "phasicj/tracelogger/trace_log.h"
#include "phasicj/tracelogger/vector_clock.h"
#include "phasicj/jmmevents/jmm_action_listener.h"

namespace phasicj::tracelogger {

using ::std::filesystem::path;
using ::phasicj::tracelogger::TraceLog;
using ::phasicj::jmmevents::JmmActionListener;

class Trace : JmmActionListener {
 public:
  Trace(JvmThreadId thread_id, path&& log_path);

  void Read(JvmThreadId thread_id) override;
  void VolatileRead(JvmThreadId thread_id) override;

  void Write(JvmThreadId thread_id) override;
  void VolatileWrite(JvmThreadId thread_id) override;

  void Lock(JvmThreadId thread_id) override;
  void Unlock(JvmThreadId thread_id) override;

  void ThreadStart(JvmThreadId thread_id) override;
  void ThreadStop(JvmThreadId thread_id) override;

  void External(JvmThreadId thread_id) override;

  void VectorClockTick();

  void SynchronizeVectorClocks(VectorClock &other);

 private:
  TraceLog trace_log_;
  int64_t thread_id_;
  int64_t counter_;
  std::map<int64_t, int64_t> counters_;
  VectorClock vector_clock_;
};

}  // namespace phasicj::tracelogger

#endif  // PHASICJ_TRACELOGGER_TRACE_H_
