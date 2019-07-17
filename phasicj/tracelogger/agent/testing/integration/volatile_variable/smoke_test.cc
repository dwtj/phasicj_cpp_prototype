#include "gtest/gtest.h"

#include "phasicj/tracelogger/agent/testing/integration/jvm_invoker.h"

using phasicj::tracelogger::agent::testing::integration::JvmInvoker;

TEST(volatile_variable_smoke_test, run) {
  JvmInvoker invoker{
      "phasicj/tracelogger/agent/testing/integration/volatile_variable/volatile_variable_java_test.jar",
      "volatile_variable/Main",
  };
  invoker.invoke();
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}