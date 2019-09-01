// Copyright 2019 David Johnston

#include <stdexcept>
#include <boost/filesystem/operations.hpp>

#include "phasicj/tracelogger/TraceLogger.h"

namespace phasicj::tracelogger {

using ::std::runtime_error;
using ::std::filesystem::current_path;

TraceLogger::TraceLogger(JavaVM& jvm, path log_dir) :
    vector_clock_manager_{},
    trace_manager_{log_dir},
    jmm_action_adapter_{jvm, &trace_manager_} { }

}  // namespace phasicj::tracelogger
