// Copyright 2019 David Johnston

#include "gtest/gtest.h"

#include "phasicj/tracelogger/agent/testing/integration/jvm_invoker.h"

#ifndef SMOKE_TEST_JAVA_BINARY_JAR_TO_INVOKE
#error SMOKE_TEST_JAVA_BINARY_JAR_TO_INVOKE is not defined.
#endif

#ifndef SMOKE_TEST_JAVA_MAIN_CLASS_TO_INVOKE
#error SMOKE_TEST_JAVA_MAIN_CLASS_TO_INVOKE is not defined.
#endif

// Use double-expansion trick to convert C preprocessor macros to string
// literals. See: https://stackoverflow.com/q/240353
#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

using ::phasicj::tracelogger::agent::testing::integration::JvmInvoker;
using ::std::cout;
using ::std::endl;
using ::std::string;

TEST(smoke_test, smoke_test) {
  const string jar {TOSTRING(SMOKE_TEST_JAVA_BINARY_JAR_TO_INVOKE)};
  const string main_class {TOSTRING(SMOKE_TEST_JAVA_MAIN_CLASS_TO_INVOKE)};

  cout << "Running PhasicJ TraceLogger integration smoke test..." << endl;
  cout << "JAR to invoke: " << jar << endl;
  cout << "Main class to invoke: " << main_class << endl;

  JvmInvoker invoker{jar, main_class};
  invoker.invoke();
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
