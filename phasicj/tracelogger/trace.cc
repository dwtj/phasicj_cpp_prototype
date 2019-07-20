// Copyright 2019 David Johnston

#include "jni.h"
#include "jvmti.h"

#include "phasicj/tracelogger/trace.h"

namespace phasicj::tracelogger {

Trace::Trace(JvmThreadId thread_id, path&& log_path)
    : trace_log_{log_path},
      thread_id_{thread_id},
      counter_{0},
      counters_{},
      vector_clock_{} {}

void Trace::Read(JvmThreadId thread_id) {
  // TODO(dwtj): Everything!
}

void Trace::VolatileRead(JvmThreadId thread_id) {
  // TODO(dwtj): Everything!
}

void Trace::Write(JvmThreadId thread_id) {
  // TODO(dwtj): Everything!
}

void Trace::VolatileWrite(JvmThreadId thread_id) {
  // TODO(dwtj): Everything!
}

void Trace::Lock(JvmThreadId thread_id) {
  // TODO(dwtj): Everything!
}

void Trace::Unlock(JvmThreadId thread_id) {
  // TODO(dwtj): Everything!
}

void Trace::ThreadStart(JvmThreadId thread_id) {
  // TODO(dwtj): Everything!
}

void Trace::ThreadStop(JvmThreadId thread_id) {
  // TODO(dwtj): Everything!
}

void Trace::External(JvmThreadId thread_id) {
  // TODO(dwtj): Everything!
}

void Trace::VectorClockTick() {
  vector_clock_.Tick(thread_id_);
}

}  // namespace phasicj::tracelogger
