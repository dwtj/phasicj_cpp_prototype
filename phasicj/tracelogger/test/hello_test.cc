// Copyright 2019 David Johnston

#include <cstdlib>
#include <iostream>
#include <string>

#include "phasicj/tracelogger/test/invoker.h"

int main() {
  phasicj::tracelogger::test::invoker i {
    "phasicj/tracelogger/test/java_test_progs/hello.jar",
    "hello/Hello",
  };
  i.invoke();
  return 0;
}
