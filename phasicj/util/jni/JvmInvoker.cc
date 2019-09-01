// Copyright 2019 David Johnston

#include <cassert>
#include <cstring>
#include <string>
#include <vector>
#include <stdexcept>

#include "boost/numeric/conversion/cast.hpp"

#include "jni.h"  // NOLINT(build/include_subdir)

#include "phasicj/util/jni/JniDescriptors.h"
#include "phasicj/util/jni/JvmInvoker.h"

constexpr jint JNI_VERSION = JNI_VERSION_1_8;
static_assert(JNI_VERSION, "JNI version 1.8 or greater required.");

namespace phasicj::util::jni {

using std::string;
using std::strncpy;
using std::vector;

using boost::numeric_cast;

JvmInvoker::JvmInvoker(const class_descriptor &main_cls,
                       const vector<string> &opts)
    : main_cls_{main_cls} {
  jvm_args_.version = JNI_VERSION;
  jvm_args_.ignoreUnrecognized = JNI_FALSE;
  jvm_args_.nOptions = numeric_cast<jint>(opts.size());
  jvm_args_.options = new JavaVMOption[jvm_args_.nOptions];
  for (int i = 0; i < jvm_args_.nOptions; ++i) {
    auto src{opts[i].c_str()};
    auto dest_size{strlen(src) + 1};
    auto dest{new char[dest_size]};
    strncpy(dest, src, dest_size);
    jvm_args_.options[i] = {
        .optionString = dest,
        .extraInfo = nullptr,
    };
  }
}

JvmInvoker::~JvmInvoker() {
  for (int i = 0; i < jvm_args_.nOptions; ++i) {
    delete[] (jvm_args_.options[i].optionString);
  }
  delete[] jvm_args_.options;
}

// One reference for how to use the JNI Invocation API to start a JVM instance
// is OpenJDK's
// [`java`](http://hg.openjdk.java.net/jdk8/jdk8/jdk/file/tip/src/share/bin/java.c)
// command.
void JvmInvoker::invoke() {
  jint err = 0;
  JavaVM *jvm = nullptr;
  JNIEnv *env = nullptr;

  // TODO(dwtj): Rewrite this using (more informative) exceptions.
  err = JNI_CreateJavaVM(&jvm, reinterpret_cast<void **>(&env), &jvm_args_);
  assert(err == 0);
  assert(env != nullptr);
  assert(env->ExceptionCheck() == JNI_FALSE);

  jclass cls = env->FindClass(main_cls_.c_str());
  assert(env->ExceptionCheck() == JNI_FALSE);
  assert(cls != nullptr);

  jmethodID mid = env->GetStaticMethodID(cls, "main", "([Ljava/lang/String;)V");
  assert(env->ExceptionCheck() == JNI_FALSE);
  assert(mid != nullptr);

  jclass stringClass{env->FindClass("java/lang/String")};
  assert(env->ExceptionCheck() == JNI_FALSE);
  assert(stringClass != nullptr);

  jobjectArray args = env->NewObjectArray(0, stringClass, nullptr);
  assert(env->ExceptionCheck() == JNI_FALSE);
  assert(args != nullptr);

  env->CallStaticVoidMethod(cls, mid, args);
  assert(env->ExceptionCheck() == JNI_FALSE);
  assert(args != nullptr);

  err = jvm->DestroyJavaVM();
  assert(err == 0);
}

}  // namespace phasicj::util::jni
