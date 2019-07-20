#include <string>
#include <optional>

#include "boost/log/trivial.hpp"
#include "boost/numeric/conversion/cast.hpp"

#include "jni.h"
#include "jvmti.h"

#include "phasicj/util/jvmti/threads.h"

namespace phasicj::util::jvmti {

using ::boost::numeric_cast;

std::optional<JvmThreadId> GetThreadId(JNIEnv& jni_env, const jthread thread) {
  if (thread == nullptr) {
    BOOST_LOG_TRIVIAL(warning) << "GetThreadId() was passed a null thread.";
    return {};
  }

  // Wraps checking whether `jni_env` has a pending exception. If so, it is
  // logged, cleared, and `true` is returned; otherwise, `false` is returned.
  auto JNIExceptionOccurred = [&jni_env](auto debug_context_message) -> bool {
    if (jni_env.ExceptionCheck() == JNI_TRUE) {
      BOOST_LOG_TRIVIAL(debug) << debug_context_message;
      // TODO(dwtj): Use JNI to extract this throwable's msg; log it with boost.
      jni_env.ExceptionDescribe();
      jni_env.ExceptionClear();
      return true;
    }
    return false;
  };

  jclass thread_klass = jni_env.GetObjectClass(thread);
  if (JNIExceptionOccurred("`GetThreadId()` called GetObjectClass().")) {
    return {};
  }

  jmethodID method_id = jni_env.GetMethodID(thread_klass, "getId", "()J");
  if (JNIExceptionOccurred("`GetThreadId()` called `GetMethodID()`.")) {
    return {};
  }

  jlong thread_id = jni_env.CallLongMethod(thread, method_id);
  if (JNIExceptionOccurred("`GetThreadId()` called `CallLongMethod()`")) {
    return {};
  }

  return {numeric_cast<int64_t>(thread_id)};
}

}  // namespace phasicj::util::jvmti
