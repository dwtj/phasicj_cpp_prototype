// Copyright 2019 David Johnston

#ifndef PHASICJ_TRACELOGGER_AGENT_H_
#define PHASICJ_TRACELOGGER_AGENT_H_

#include "jni.h"  // NOLINT(build/include_subdir)
#include "jvmti.h"

namespace phasicj::tracelogger {

class Agent {
 public:
  static bool ProvidesRequiredCapabilities(jvmtiEnv& env);
  static Agent* MaybeNewFromOnLoadEvent(JavaVM* vm, char* options,
                                        void* reserved);
  explicit Agent(jvmtiEnv* env);

 private:
  jvmtiEnv* jvmti_env_;
};

}  // namespace phasicj::tracelogger

#endif  // PHASICJ_TRACELOGGER_AGENT_H_
