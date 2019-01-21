#include "gtest/gtest.h"

#include "phasicj/tracelogger/testing/integration/jvm_invoker.h"

using phasicj::tracelogger::testing::integration::JvmInvoker;

TEST(hello, run) {
  JvmInvoker invoker{
      "phasicj/tracelogger/testing/integration/java_test_programs/hello.jar",
      "hello/Main",
  };
  invoker.invoke();
}
