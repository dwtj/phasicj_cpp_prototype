#include "gtest/gtest.h"

#include "phasicj/tracelogger/agent/testing/integration/jvm_invoker.h"

using phasicj::tracelogger::agent::testing::integration::JvmInvoker;

TEST(hello, smoke_test) {
  JvmInvoker invoker{
      "phasicj/tracelogger/agent/testing/integration/hello/hello_java_test.jar",
      "helloworld/Main",
  };
  invoker.invoke();
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}