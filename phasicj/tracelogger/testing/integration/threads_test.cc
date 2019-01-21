// Copyright 2019 David Johnston

#include "phasicj/tracelogger/testing/integration/jvm_invoker.h"

int main() {
  phasicj::tracelogger::testing::integration::JvmInvoker i{
      "phasicj/tracelogger/testing/integration/java_test_progs/threads.jar",
      "threads/Threads",
  };
  i.invoke();
  return 0;
}
