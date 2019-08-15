// Copyright 2019 David Johnston

#include <cassert>
#include <cstdlib>
#include <filesystem>
#include <string>
#include <vector>
#include <iostream>

#include "phasicj/tracelogger/agent/testing/integration/jvm_invoker.h"

namespace phasicj::tracelogger::agent::testing::integration {

using std::getenv;
using std::string;
using std::vector;
using std::filesystem::canonical;
using std::filesystem::exists;
using std::filesystem::is_regular_file;
using std::filesystem::path;

using phasicj::util::jni::class_descriptor;

path GetAbsoluteAgentPath() {
  // Tests should work on either macOS (which uses `.dylib` files) or Linux
  // (which uses `.so` files). Use whichever extension is found.

  path so{"phasicj/tracelogger/agent/libpjtracelogger.so"};
  path dylib{"phasicj/tracelogger/agent/libpjtracelogger.dylib"};
  assert(exists(so) != exists(dylib));  // Logical XOR trick.

  path agentpath{(exists(so) ? so : dylib)};
  assert(is_regular_file(agentpath));
  return canonical(agentpath);
}

vector<string> JvmOptions(const vector<string>& opt) {
  vector<string> new_opts{
      "-agentpath:" + GetAbsoluteAgentPath().native(),
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

void RecursivelyPrintContentsOfCurrentWorkingDirectory() {
  using ::std::filesystem::recursive_directory_iterator;
  std::cout << "recursively iterating over contents of cwd" << std::endl;
  for (auto& entry : recursive_directory_iterator(".")) {
    std::cout << entry.path() << std::endl;
  }
}

void JvmInvoker::invoke() {
  RecursivelyPrintContentsOfCurrentWorkingDirectory();
  invoker_.invoke();
}

}  // namespace phasicj::tracelogger::testing::integration
