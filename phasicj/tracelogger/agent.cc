// Copyright 2019 David Johnston

// This class implements the actual agent logic. The class does not follow
// conventional RAII discipline. Instances of it are expected to have static
// storage duration. Resources which it manages are primarily provided by the
// JVM and managed during callbacks from the JVM to an agent instance.
//
// More information about these various callbacks and the details of the
// JVM/agent contract are available in [the JVMTI
// documentation](https://docs.oracle.com/en/java/javase/11/docs/specs/jvmti.html).

#include <iostream>

#include "jni.h"  // NOLINT(build/include_subdir)

#include "phasicj/execution.pb.h"
#include "phasicj/tracelogger/agent.h"

namespace phasicj::tracelogger {

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

}  // namespace phasicj::tracelogger
