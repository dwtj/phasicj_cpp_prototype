// Copyright 2019 David Johnston

#include <filesystem>
#include <stdexcept>

#include "google/protobuf/util/delimited_message_util.h"

#include "phasicj/jvmexec/event.pb.h"
#include "phasicj/tracelogger/trace_log.h"

namespace phasicj::tracelogger {

using ::google::protobuf::util::SerializeDelimitedToOstream;
using ::std::runtime_error;
using ::std::filesystem::path;

TraceLog::TraceLog(path out) : out_{out, std::ios::binary | std::ios::trunc} {
  if (!out_) {
    throw runtime_error("Failed to make a trace log at path: " + out.string());
  }
  out_.exceptions(std::ios_base::badbit | std::ios_base::failbit);
}

TraceLog& TraceLog::operator<<(const phasicj::jvmexec::Event& ev) {
  SerializeDelimitedToOstream(ev, &out_);
}

}  // namespace phasicj::tracelogger