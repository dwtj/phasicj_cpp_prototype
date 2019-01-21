#include "gtest/gtest.h"

#include "phasicj/tracelogger/testing/integration/jvm_invoker.h"

using phasicj::tracelogger::testing::integration::JvmInvoker;

TEST(volatile_variable, run) {
  JvmInvoker invoker{
      "phasicj/tracelogger/testing/integration/java_test_programs/"
      "volatile_variable.jar",
      "volatile_variable/Main",
  };
  invoker.invoke();
}
