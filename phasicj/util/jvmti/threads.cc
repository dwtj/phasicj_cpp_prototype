#include <string>
#include <optional>

#include "boost/log/trivial.hpp"
#include "jni.h"
#include "jvmti.h"

#include "phasicj/util/jvmti/threads.h"

namespace phasicj::util::jvmti {

std::optional<jlong> GetThreadId(JNIEnv& jni_env, const jthread thread) {
  if (thread == nullptr) {
    BOOST_LOG_TRIVIAL(warning) << "GetThreadId() passed a null thread.";
    return {};
  }

  // Wraps checking whether `jni_env` has a pending exception. If so, it is
  // logged, cleared, and `true` is returned; otherwise, `false` is returned.
  auto ExceptionCheck = [&jni_env](auto debug_context_message) -> bool {
    if (jni_env.ExceptionCheck() == JNI_TRUE) {
      BOOST_LOG_TRIVIAL(debug) << debug_context_message;
      // TODO(dwtj): Extract this throwable's msg and log it with boost.
      jni_env.ExceptionDescribe();
      jni_env.ExceptionClear();
      return true;
    }

  };

  jclass thread_klass = jni_env.GetObjectClass(thread);
  if (ExceptionCheck("`GetThreadId()` called GetObjectClass().")) {
    return {};
  }

  jmethodID method_id = jni_env.GetMethodID(thread_klass, "getId", "()J");
  if (ExceptionCheck("`GetThreadId()` called `GetMethodID()`.")) {
    return true;
  }

  jlong thread_id = jni_env.CallLongMethod(thread, method_id);
  if (ExceptionCheck("`GetThreadId()` called `CallLongMethod()`")) {
    return {};
  }

  return {thread_id};
}

}  // namespace phasicj::util::jvmti
