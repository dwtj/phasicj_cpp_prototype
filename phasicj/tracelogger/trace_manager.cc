// Copyright 2019 David Johnston

// TODO(dwtj): Java thread IDs may be re-used [1]. It doesn't appear that the
//  hotspot JVM does this, but some JVMTI-compliant JVM may do this. Thus, this
//  agent currently behaves incorrectly when thread IDs are reused. In
//  particular, the old thread's trace log file will be clobbered by the new
//  thread's trace log. Maybe I should at least check for thread ID reuse.
//
//  [1] https://docs.oracle.com/en/java/javase/11/docs/api/java.base/java/lang/Thread.html#getId()


#include <cassert>
#include <filesystem>
#include <stdexcept>

#include "gsl/gsl"

#include "boost/log/trivial.hpp"

#include "jvmti.h"

#include "phasicj/util/jvmti/threads.h"
#include "phasicj/tracelogger/trace.h"
#include "phasicj/tracelogger/trace_log.h"
#include "phasicj/tracelogger/trace_manager.h"
#include "phasicj/jmmevents/jmm_action_listener.h"

namespace phasicj::tracelogger {

using ::std::filesystem::path;
using ::std::move;
using ::std::runtime_error;
using ::std::to_string;

using ::phasicj::util::jvmti::GetThreadId;

using ::phasicj::jmmevents::JmmActionListener;
using ::phasicj::jmmevents::JmmActionListenerManager;

TraceManager::TraceManager(path log_dir) : log_dir_(move(log_dir)) { }

JmmActionListener* TraceManager::New(JvmThreadId id) {
  // TODO(dwtj): It is an error if the given `jthread` does not represent the
  //  thread calling this function. Write this precondition as a GSL `Expects()`
  //  call.
  throw runtime_error{"TODO"};
}

void TraceManager::Free(JvmThreadId id) {
  // TODO(dwtj): Everything!
  throw runtime_error{"TODO"};
}

// https://docs.oracle.com/en/java/javase/11/docs/api/java.base/java/lang/Thread.html#getId()
path TraceManager::TraceLogPathFor(JvmThreadId thread_id) {
  Expects(thread_id > 0);
  // TODO(dwtj): Think again about how thread trace log files should be organized?
  return {(log_dir_ / "thread_").concat(to_string(thread_id))};
}

}  // namespace phasicj::tracelogger
