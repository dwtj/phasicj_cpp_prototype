// Copyright 2019 David Johnston

#include <string>
#include <vector>

#include "phasicj/tracelogger/test/jvm_invoker.h"

using std::string;
using std::vector;

using phasicj::tracelogger::test::JvmInvoker;

int main() {
  JvmInvoker invoker{
      "phasicj/tracelogger/test/java_test_progs/hello.jar",
      "hello/Hello",
  };
  invoker.invoke();
  return 0;
}
