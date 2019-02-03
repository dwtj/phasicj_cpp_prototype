// Copyright 2019 David Johnston

#ifndef PHASICJ_UTIL_JVMTI_JVMTIUTIL_H_
#define PHASICJ_UTIL_JVMTI_JVMTIUTIL_H_

#include <optional>

#include "jni.h"
#include "jvmti.h"

namespace phasicj::util::jvmti {

std::optional<jlong> GetThreadId(JNIEnv& jni_env, jthread thread);

}  // namespace phasicj::util::jvmti

#endif  // PHASICJ_UTIL_JVMTI_JVMTIUTIL_H_