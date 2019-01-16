// Copyright 2019 David Johnston

#include <string>
#include <vector>

#include "phasicj/tracelogger/test/invoker.h"

namespace phasicj::tracelogger::test {

using std::vector;
using std::string;

static const vector<string> DEFAULT_JVM_OPTIONS {
    "-verbose",
    "-agentlib:pjtracelogger",
    "-enableassertions",
    "-enablesystemassertions",
    "-Xcheck:jni",
};

invoker::invoker(string cp, string main_cls) :
      invoker_ {cp, main_cls, DEFAULT_JVM_OPTIONS} { };

void invoker::invoke() {
    invoker_.invoke();
}

}  // namespace phasicj::tracelogger::test
