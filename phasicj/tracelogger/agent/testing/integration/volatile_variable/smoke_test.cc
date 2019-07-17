#include "gtest/gtest.h"

#include "phasicj/tracelogger/agent/testing/integration/jvm_invoker.h"

using phasicj::tracelogger::agent::testing::integration::JvmInvoker;

TEST(volatile_variable_smoke_test, run) {
  JvmInvoker invoker{
      "phasicj/tracelogger/testing/integration/java_test_programs/"
      "volatile_variable.jar",
      "volatile_variable/Main",
  };
  invoker.invoke();
}
