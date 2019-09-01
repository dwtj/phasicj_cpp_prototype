// Copyright 2019 David Johnston

#ifndef PHASICJ_TRACELOGGER_LOGGING_PROTOS_PROTO_FILE_TRACE_LOG_H_
#define PHASICJ_TRACELOGGER_LOGGING_PROTOS_PROTO_FILE_TRACE_LOG_H_

#include "phasicj/tracelogger/jmmevents/vectorclocks/vc_jmm_trace.h"

namespace phasicj::tracelogger::logging::protos {

class ProtoFileTraceLog : public VcJmmTrace {
 public:
  explicit ProtoFileTraceLog(::std::filesystem::path out);
  TraceLog& operator<<(const phasicj::jvmexec::MemoryEvent& ev);

 private:
  std::ofstream out_;
};

}  // namespace phasicj::tracelogger::logging::protos

#endif // PHASICJ_TRACELOGGER_LOGGING_PROTOS_PROTO_FILE_TRACE_LOG_H_
