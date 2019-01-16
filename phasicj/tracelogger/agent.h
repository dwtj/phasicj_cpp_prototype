// Copyright 2019 David Johnston

#ifndef PHASICJ_TRACELOGGER_AGENT_H_
#define PHASICJ_TRACELOGGER_AGENT_H_

#include "jni.h"  // NOLINT(build/include_subdir)

namespace phasicj {
namespace tracelogger {

class Agent {
 public:
  jint OnLoad(JavaVM *vm, char *options, void *reserved);
  jint OnAttach(JavaVM *vm, char *options, void *reserved);
  void OnUnload(JavaVM *vm);
};

}  // namespace tracelogger
}  // namespace phasicj

#endif  // PHASICJ_TRACELOGGER_AGENT_H_
