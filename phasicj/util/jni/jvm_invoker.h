// Copyright 2019 David Johnston

#ifndef PHASICJ_UTIL_JDK_INVOKER_H_
#define PHASICJ_UTIL_JDK_INVOKER_H_

#include <string>
#include <vector>

#include "jni.h"  // NOLINT(build/include_subdir)

#include "phasicj/util/jni/descriptors.h"

namespace phasicj {
namespace util {
namespace jni {

using phasicj::util::jni::class_descriptor;

// Configures and performs an invocation of a JVM instance. Essentially, it
// wraps the use of the [JNI Invocation
// API](https://docs.oracle.com/en/java/javase/11/docs/specs/jni/invocation.html).
class JvmInvoker {
 private:
  const class_descriptor main_cls_;
  JavaVMInitArgs jvm_args_;  // TODO(dwtj): How can I make this `const`?

 public:
  JvmInvoker(const class_descriptor& main_cls,
             const std::vector<std::string>& opts);

  JvmInvoker(const JvmInvoker& i) = delete;

  JvmInvoker(JvmInvoker&& i) = delete;

  ~JvmInvoker();

  void invoke();
};

}  // namespace jni
}  // namespace util
}  // namespace phasicj

#endif  // PHASICJ_UTIL_JDK_INVOKER_H_
