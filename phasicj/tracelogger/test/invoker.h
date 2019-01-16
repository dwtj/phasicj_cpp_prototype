// Copyright 2019 David Johnston

#ifndef PHASICJ_TRACELOGGER_TEST_INVOKER_H_
#define PHASICJ_TRACELOGGER_TEST_INVOKER_H_

#include <string>

#include "phasicj/util/jdk/invoker.h"

namespace phasicj::tracelogger::test {

using std::string;

class invoker {
 private:
  phasicj::util::jdk::Invoker invoker_;

 public:
  invoker(string cp, string main_cls);
  void invoke();
};

}  // namespace phasicj::tracelogger::test

#endif  // PHASICJ_TRACELOGGER_TEST_INVOKER_H_
