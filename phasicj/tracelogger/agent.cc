// Copyright 2019 David Johnston

#include <iostream>

#include "jni.h"  // NOLINT(build/include_subdir)

#include "phasicj/tracelogger/agent.h"
#include "phasicj/execution.pb.h"

namespace phasicj {
namespace tracelogger {

jint Agent::OnAttach(JavaVM *vm, char *options, void *reserved) {
  // TODO(dwtj)
  std::cout << "OnAttach(...)" << std::endl;
  return JNI_OK;
}

jint Agent::OnLoad(JavaVM *vm, char *options, void *reserved) {
  // TODO(dwtj)
  std::cout << "OnLoad(...)" << std::endl;
  return JNI_OK;
}

void Agent::OnUnload(JavaVM *vm) {
  // TODO(dwtj)
  std::cout << "OnUnload(...)" << std::endl;
}

}  // namespace tracelogger
}  // namespace phasicj

