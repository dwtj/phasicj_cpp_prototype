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
  static bool ProvidesRequiredCapabilities(jvmtiEnv& jvmti_env);

  Agent() = delete;

  // Throws a `runtime_error` if construction fails.
  Agent(JavaVM& jvm, const std::string& options);

  Agent(const Agent& other) = delete;

  Agent(Agent&& other) noexcept;

  ~Agent() noexcept;

  void FieldAccess(jvmtiEnv* jvmti_env,
                   JNIEnv* jni_env,
                   jthread thread,
                   jmethodID method,
                   jlocation location,
                   jclass field_klass,
                   jobject object,
                   jfieldID field);

  void FieldModification(jvmtiEnv* jvmti_env,
                         JNIEnv* jni_env,
                         jthread thread,
                         jmethodID method,
                         jlocation location,
                         jclass field_klass,
                         jobject object,
                         jfieldID field,
                         char signature_type,
                         jvalue new_value);
};

}  // namespace phasicj::tracelogger

#endif  // PHASICJ_TRACELOGGER_AGENT_H_
