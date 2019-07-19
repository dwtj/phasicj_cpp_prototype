#include <thread>

#include "gtest/gtest.h"

#include "phasicj/tracelogger/agent/testing/integration/jvm_invoker.h"

using std::thread;

using phasicj::tracelogger::agent::testing::integration::JvmInvoker;

void invoke() {
  JvmInvoker invoker{
    "phasicj/tracelogger/agent/testing/integration/hello/hello_java_test.jar",
    "sleep/Main",
  };
  invoker.invoke();
}

TEST(sleep, multiple_jvms_smoke_test) {
  thread t1{invoke};
  thread t2{invoke};
  t1.join();
  t2.join();
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}