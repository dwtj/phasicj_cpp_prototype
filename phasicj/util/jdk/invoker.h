//
// Created by David Johnston on 1/14/19.
//

#ifndef PHASICJ_UTIL_JDK_INVOKER_H
#define PHASICJ_UTIL_JDK_INVOKER_H

#include <string>
#include <vector>

#include "jni.h"  //NOLINT

namespace phasicj::util::jdk {

// Configures and performs an invocation of a JVM instance. Essentially, it
// wraps the use of the [JNI Invocation API](https://docs.oracle.com/en/java/javase/11/docs/specs/jni/invocation.html).
class Invoker {

 private:
  const std::string main_cls_;
  JavaVMInitArgs jvm_args_;  // TODO(dwtj): How can I make this `const`?

 public:
  Invoker(const std::vector<std::string>& opts, const std::string& main_cls);

  Invoker(const std::string& cp, const std::string& main_cls);

  Invoker(const std::string& cp, const std::string& main_cls,
          const std::vector<std::string>& other_opts);

  Invoker(const Invoker& i) = delete;  // TODO(dwtj)

  Invoker(Invoker&& i) = delete;       // TODO(dwtj)

  ~Invoker();

  void invoke();
};

}  // namespace phasicj::util::jdk

#endif //PHASICJ_UTIL_JDK_INVOKER_H
