// Copyright 2019 David Johnston

#include <stdexcept>
#include <boost/filesystem/operations.hpp>

#include "phasicj/tracelogger/trace_logger.h"

namespace phasicj::tracelogger {

using ::std::runtime_error;
using ::std::filesystem::current_path;

TraceLogger::TraceLogger(path log_dir) :
    vector_clock_manager_{},
    trace_manager_{log_dir} { }

}  // namespace phasicj::tracelogger
