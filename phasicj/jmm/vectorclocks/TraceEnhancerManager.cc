// Copyright 2019 David Johnston

// TODO(dwtj): Java thread IDs may be re-used [1]. It doesn't appear that the
//  hotspot JVM does this, but some JVMTI-compliant JVM may do this. Thus, this
//  agent currently behaves incorrectly when thread IDs are reused. In
//  particular, the old thread's trace log file will be clobbered by the new
//  thread's trace log. Maybe I should at least check for thread ID reuse.
//
//  [1] https://docs.oracle.com/en/java/javase/11/docs/api/java.base/java/lang/Thread.html#getId()


#include <filesystem>
#include <stdexcept>

#include "gsl/gsl"

#include "jvmti.h"

#include "phasicj/util/jvm/Threads.h"

namespace phasicj::tracelogger {

using ::phasicj::util::jvm::JvmThreadId;
using ::std::runtime_error;

VcJmmTraceManager::VcJmmTraceTraceManager() { }

unique_ptr<JmmTraceEnhancer> JmmTraceEnhancerManager::New(JvmThreadId id) {
  // TODO(dwtj): It is an error if the given `jthread` does not represent the
  //  thread calling this function. Write this precondition as a GSL `Expects()`
  //  call.
  throw runtime_error{"TODO"};
}

}  // namespace phasicj::tracelogger
