#include "gtest/gtest.h"

#include "phasicj/tracelogger/agent/testing/integration/jvm_invoker.h"

using phasicj::tracelogger::agent::testing::integration::JvmInvoker;

TEST(hello_smoke_test, run) {
  JvmInvoker invoker{
      "phasicj/tracelogger/agent/testing/integration/hello/hello_java_test.jar",
      "hello/Main",
  };
  invoker.invoke();
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
