#include <optional>

#include "jni.h"
#include "jvmti.h"

#include "phasicj/util/jvmti/threads.h"

namespace phasicj::util::jvmti {

std::optional<jlong> GetThreadId(JNIEnv& jni_env, const jthread thread) {
  if (thread == nullptr) {
    // TODO: Error log this.
    return {};
  }
  jclass thread_klass = jni_env.GetObjectClass(thread);
  if (jni_env.ExceptionCheck() == JNI_FALSE) {
    // TODO: Error log this.
    jni_env.ExceptionClear();
    return {};
  }

  jmethodID method_id = jni_env.GetMethodID(thread_klass, "getId", "()J");
  if (jni_env.ExceptionCheck() == JNI_FALSE) {
    // TODO: Error log this.
    jni_env.ExceptionClear();
    return {};
  }

  jlong thread_id = jni_env.CallLongMethod(thread, method_id);
  if (jni_env.ExceptionCheck() == JNI_FALSE) {
    // TODO: Error log this.
    jni_env.ExceptionClear();
    return {};
  }

  return {thread_id};
}

}  // namespace phasicj::util::jvmti
