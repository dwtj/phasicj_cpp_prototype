#include <optional>

#include "jni.h"
#include "jvmti.h"

#include "phasicj/util/jvmti/misc.h"

namespace phasicj::util::jvmti {

using std::optional;

optional<bool> IsFieldVolatile(jvmtiEnv& jvmti_env,
                               const jclass field_klass,
                               const jfieldID field) {
  // NOTE(dwtj): The JVMTI documentation does not seem to say how a field's
  // modifiers are encoded in this `jint` [1]. So, I am going to guess that
  // modifiers are encoded like in the Java class file format's `field_info`
  // structure, specifically, its `access_flags` field [2]. This guess is
  // consistent with some discussion that I've seen on StackOverflow [3].
  //
  // [1](https://docs.oracle.com/en/java/javase/11/docs/specs/jvmti.html#GetFieldModifiers)
  // [2](https://docs.oracle.com/javase/specs/jvms/se11/html/jvms-4.html#jvms-4.5)
  // [3](https://stackoverflow.com/q/30001583)

  // TODO(dwtj): Test the above assumption.

  constexpr jint AAC_VOLATILE = 0x0040;
  jint modifiers;
  jint err;
  err = jvmti_env.GetFieldModifiers(field_klass, field, &modifiers);
  if (err == JVMTI_ERROR_NONE) {
    return {(modifiers & AAC_VOLATILE) != 0};
  } else {
    return {};
  }
}

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
