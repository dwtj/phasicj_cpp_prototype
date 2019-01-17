// Copyright 2019 David Johnston

#include <cassert>
#include <cstdlib>
#include <string>
#include <vector>

#include "phasicj/tracelogger/test/invoker.h"

namespace phasicj {
namespace tracelogger {
namespace test {

using std::getenv;
using std::string;
using std::vector;

string GetPwd() {
  char* pwd = getenv("PWD");
  assert(pwd != nullptr);
  return string{pwd};
}

vector<string> BuildDefaultJvmOptions() {
  return vector<string>{
      "-agentpath:" + GetPwd() + "/phasicj/tracelogger/libpjtracelogger.so",
      "-verbose",
      "-enableassertions",
      "-enablesystemassertions",
      "-Xcheck:jni",
  };
}

invoker::invoker(string cp, string main_cls)
    : invoker_{cp, main_cls, BuildDefaultJvmOptions()} {};

void invoker::invoke() { invoker_.invoke(); }

}  // namespace test
}  // namespace tracelogger
}  // namespace phasicj
