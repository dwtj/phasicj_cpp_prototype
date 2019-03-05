// Copyright 2019 David Johnston

#ifndef PHASICJ_TRACELOGGER_TRACELOG_H_
#define PHASICJ_TRACELOGGER_TRACELOG_H_

#include <filesystem>
#include <fstream>
#include <ostream>

#include "phasicj/jvmexec/memory_event.pb.h"

namespace phasicj::tracelogger {

class TraceLog {
 public:
  TraceLog(std::filesystem::path logpath);

  //TraceLog& operator<<(const phasicj::jvmexec::MemoryEvent& ev);

 private:
  std::ofstream out_;
};

}  // namespace phasicj::tracelogger

#endif  // PHASICJ_TRACELOGGER_TRACELOG_H_
