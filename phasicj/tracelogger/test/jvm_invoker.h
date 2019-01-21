// Copyright 2019 David Johnston

#ifndef PHASICJ_TRACELOGGER_TEST_INVOKER_H_
#define PHASICJ_TRACELOGGER_TEST_INVOKER_H_

#include <string>

#include "phasicj/util/jni/jvm_invoker.h"

namespace phasicj::tracelogger::test {

using std::string;

class JvmInvoker {
 private:
  phasicj::util::jni::JvmInvoker invoker_;

 public:
  JvmInvoker(const string& cp, const string& main_cls);
  void invoke();
};

}  // namespace phasicj::tracelogger::test

#endif  // PHASICJ_TRACELOGGER_TEST_INVOKER_H_
