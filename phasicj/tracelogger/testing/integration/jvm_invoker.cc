// Copyright 2019 David Johnston

#include <cassert>
#include <cstdlib>
#include <string>
#include <vector>

#include "boost/filesystem.hpp"

#include "phasicj/tracelogger/testing/integration/jvm_invoker.h"

namespace phasicj::tracelogger::testing::integration {

using std::getenv;
using std::string;
using std::vector;

using boost::filesystem::canonical;
using boost::filesystem::exists;
using boost::filesystem::is_regular_file;
using boost::filesystem::path;

using phasicj::util::jni::class_descriptor;

path GetAbsoluteAgentPath() {
  // Tests should work on either macOS (which uses `.dylib` files) or Linux
  // (which uses `.so` files). Use whichever extension is found.
  path so{"phasicj/tracelogger/libpjtracelogger.so"};
  path dylib{"phasicj/tracelogger/libpjtracelogger.dylib"};
  assert(exists(so) != exists(dylib));  // Logical XOR trick.

  path agentpath{(exists(so) ? so : dylib)};
  assert(is_regular_file(agentpath));
  return canonical(agentpath);
}

vector<string> JvmOptions(const vector<string>& opt) {
  vector<string> new_opts{
      "-agentpath:" + GetAbsoluteAgentPath().native(),
      "-verbose",
      "-enableassertions",
      "-enablesystemassertions",
      "-Xcheck:jni",
  };
  for (auto& o : opt) {
    new_opts.push_back(o);
  }
  return new_opts;
}

JvmInvoker::JvmInvoker(const string& cp, const class_descriptor& main_cls)
    : invoker_{main_cls,
               JvmOptions(vector<string>{"-Djava.class.path=" + cp})} {}

void JvmInvoker::invoke() { invoker_.invoke(); }

}  // namespace phasicj::tracelogger::testing::integration
