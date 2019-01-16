// Copyright 2019 David Johnston

#include "phasicj/tracelogger/test/invoker.h"

int main() {
  phasicj::tracelogger::test::invoker i {
    "phasicj/tracelogger/test/javatestsrcs/threads/libthreads.jar",  // TODO(dwtj): I don't think that the lib prefix is portable.
    "threads/Threads",
  };
  i.invoke();
  return 0;
}