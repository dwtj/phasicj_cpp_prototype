#include "gtest/gtest.h"

#include "phasicj/tracelogger/agent/testing/integration/jvm_invoker.h"

using phasicj::tracelogger::agent::testing::integration::JvmInvoker;

TEST(threads_smoke_test, run) {
  JvmInvoker invoker{
      "phasicj/tracelogger/testing/integration/java_test_programs/threads.jar",
      "threads/Main",
  };
  invoker.invoke();
}