// Copyright 2019 David Johnston

#ifndef PHASICJ_TRACELOGGER_AGENT_H_
#define PHASICJ_TRACELOGGER_AGENT_H_

#include "jni.h"

namespace phasicj::tracelogger {

class Agent {
 public:
  jint OnLoad(JavaVM *vm, char *options, void *reserved);
  jint OnAttach(JavaVM *vm, char *options, void *reserved);
  void OnUnload(JavaVM *vm);
};

}  // namespace phasicj::tracelogger

#endif //PHASICJ_TRACELOGGER_AGENT_H_
