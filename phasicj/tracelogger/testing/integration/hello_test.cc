// Copyright 2019 David Johnston

#include <string>
#include <vector>

#include "phasicj/tracelogger/testing/integration/jvm_invoker.h"

using phasicj::tracelogger::testing::integration::JvmInvoker;

int main() {
  JvmInvoker invoker{
      "phasicj/tracelogger/testing/integration/java_test_progs/hello.jar",
      "hello/Hello",
  };
  invoker.invoke();
  return 0;
}
