#include "gtest/gtest.h"

#include "phasicj/tracelogger/agent/testing/integration/jvm_invoker.h"

using phasicj::tracelogger::agent::testing::integration::JvmInvoker;

TEST(threads_smoke_test, run) {
  JvmInvoker invoker{
      "phasicj/tracelogger/agent/testing/integration/threads/threads_java_test.jar",
      "threads/Main",
  };
  invoker.invoke();
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}