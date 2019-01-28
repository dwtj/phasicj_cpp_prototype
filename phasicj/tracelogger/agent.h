// Copyright 2019 David Johnston

#ifndef PHASICJ_TRACELOGGER_AGENT_H_
#define PHASICJ_TRACELOGGER_AGENT_H_

#include <optional>
#include <string>

#include "jni.h"  // NOLINT(build/include_subdir)
#include "jvmti.h"

namespace phasicj::tracelogger {

class Agent {
 private:
  // The JVMTI environment to which this agent is bound.
  jvmtiEnv* jvmti_env_;

 public:
  static std::optional<Agent*> NewFromOnLoad(JavaVM* jvm,
                                             char* options,
                                             void* reserved);

  Agent() = delete;

  // Throws a `runtime_error` if construction fails.
  Agent(JavaVM& jvm, const std::string& options);

  Agent(const Agent& other) = delete;

  Agent(Agent&& other) noexcept = delete;

  ~Agent() noexcept;
};

}  // namespace phasicj::tracelogger

#endif  // PHASICJ_TRACELOGGER_AGENT_H_
