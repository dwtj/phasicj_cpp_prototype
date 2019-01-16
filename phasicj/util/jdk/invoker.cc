// Copyright 2019 David Johnston

#include <cstring>
#include <string>
#include <vector>
#include <cassert>

#include "boost/numeric/conversion/cast.hpp"

#include "jni.h"  // NOLINT

#include "phasicj/util/jdk/invoker.h"

constexpr jint JNI_VERSION = JNI_VERSION_9;
static_assert(JNI_VERSION, "JNI version 9 or greater required.");

namespace phasicj::util::jdk {

using std::string;
using std::strncpy;
using std::string_literals::operator""s;
using std::vector;

void InitializeVmArgsFrom(JavaVMInitArgs &jvm_args,
                          const vector<string> &opts) {
  jvm_args.version = JNI_VERSION;
  jvm_args.ignoreUnrecognized = JNI_FALSE;
  jvm_args.nOptions = boost::numeric_cast<jint>(opts.size());
  jvm_args.options = new JavaVMOption[jvm_args.nOptions];
  for (int i = 0; i < jvm_args.nOptions; ++i) {
    auto src {opts[i].c_str()};
    auto dest_size {strlen(src) + 1};
    auto dest {new char[dest_size]};
    strncpy(dest, src, dest_size);
    jvm_args.options[i] = {
        .optionString = dest,
        .extraInfo = nullptr,
    };
  }
}

Invoker::Invoker(const string &cp, const string &main_cls) :
    Invoker(vector<string>{"-Djava.class.path"s + cp}, main_cls) { }

Invoker::Invoker(const vector<string> &opts, const string &main_cls) :
    main_cls_{main_cls} {
  InitializeVmArgsFrom(jvm_args_, opts);
}

Invoker::Invoker(const string &cp, const string &main_cls,
                 const vector<string> &other_opts) : main_cls_ {main_cls} {
  vector<string> opts{other_opts};
  opts.push_back("-Djava.class.path=" + cp);
  InitializeVmArgsFrom(jvm_args_, opts);
}

Invoker::~Invoker() {
  for (int i = 0; i < jvm_args_.nOptions; ++i) {
    delete (jvm_args_.options[i].optionString);
  }
  delete jvm_args_.options;
}

// One reference for how to use the JNI Invocation API to start a JVM instance
// is OpenJDK's [`java`](http://hg.openjdk.java.net/jdk8/jdk8/jdk/file/tip/src/share/bin/java.c)
// command.
void Invoker::invoke() {
  jint err = 0;
  JavaVM *jvm = nullptr;
  JNIEnv *env = nullptr;

  err = JNI_CreateJavaVM(&jvm, reinterpret_cast<void **>(&env), &jvm_args_);
  assert(env->ExceptionCheck() == JNI_FALSE);
  assert(err == 0);

  jclass cls = env->FindClass(main_cls_.c_str());
  assert(env->ExceptionCheck() == JNI_FALSE);
  assert(cls != nullptr);

  jmethodID mid = env->GetStaticMethodID(cls, "main", "([Ljava/lang/String;)V");
  if (env->ExceptionCheck() == JNI_FALSE) {
    env->ExceptionDescribe();
  }
  assert(env->ExceptionCheck() == JNI_FALSE);
  assert(mid != nullptr);

  jclass stringClass {env->FindClass("java/lang/String")};
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

}  // namespace phasicj::util::jdk
