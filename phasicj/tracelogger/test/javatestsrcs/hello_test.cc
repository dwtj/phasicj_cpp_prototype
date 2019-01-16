// Copyright 2019 David Johnston

#include <cstdlib>
#include <iostream>
#include <string>

#include "phasicj/tracelogger/test/invoker.h"

int main() {
  phasicj::tracelogger::test::invoker i {
    "phasicj/tracelogger/test/javatestsrcs/hello/libhello.jar",  // TODO(dwtj): I don't think that the lib prefix is portable.
    "hello/Hello",
  };
  i.invoke();
  return 0;
}
