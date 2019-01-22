// Copyright 2019 David Johnston

#ifndef PHASICJ_TRACELOGGER_AGENT_H_
#define PHASICJ_TRACELOGGER_AGENT_H_

#include <optional>

#include "jni.h"  // NOLINT(build/include_subdir)
#include "jvmti.h"

namespace phasicj::tracelogger {

class Agent {
 public:
  static bool ProvidesRequiredCapabilities(jvmtiEnv& env);
  static std::optional<Agent> NewFromOnLoadEvent(JavaVM* vm, char* options,
                                                 void* reserved);

  Agent() = delete;
  explicit Agent(jvmtiEnv* env);
  Agent(const Agent& other) = delete;
  Agent(Agent&& other) noexcept;
  ~Agent() noexcept;

 private:
  jvmtiEnv* jvmti_env_;
};

}  // namespace phasicj::tracelogger

#endif  // PHASICJ_TRACELOGGER_AGENT_H_
