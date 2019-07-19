// Copyright 2019 David Johnston

#include "phasicj/tracelogger/trace_logger_manager.h"

namespace phasicj::tracelogger {

using ::std::scoped_lock;

void TraceLoggerManager::Install(const JavaVM &jvm) {
  scoped_lock monitor {monitor_};
  // TODO(dwtj): Everything!
}

void TraceLoggerManager::Uninstall(const JavaVM &jvm) {
  scoped_lock monitor {monitor_};
  // TODO(dwtj): Everything!
}

}  // namespace phasicj::tracelogger
