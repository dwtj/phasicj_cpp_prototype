// Copyright 2019 David Johnston

// This file defines a simple wrapper for each of the agent's callbacks.
//
// Each wrapper function in this file is designed to be usable as C-style
// function pointer.
//
// Each wrapper function should do the same thing: when called, it uses the
// given JVMTI environment to obtain the Agent instance stored in environment
// local storage [1]. The wrapper then delegates to this Agent instance's
// corresponding member function.
//
// [1](https://docs.oracle.com/en/java/javase/11/docs/specs/jvmti.html#SetEnvironmentLocalStorage)

#include <list>

#include "jni.h"
#include "jvmti.h"

#include "phasicj/tracelogger/agent.h"
#include "phasicj/tracelogger/agent_callbacks.h"

namespace phasicj::tracelogger {

using std::list;

inline Agent& GetAgent(jvmtiEnv& jvmti_env) {
  Agent* agent;
  jvmti_env.GetEnvironmentLocalStorage(reinterpret_cast<void**>(&agent));
  return *agent;
}

void JNICALL FieldAccess(jvmtiEnv* jvmti_env,
                         JNIEnv* jni_env,
                         jthread thread,
                         jmethodID method,
                         jlocation location,
                         jclass field_klass,
                         jobject object,
                         jfieldID field) {
  GetAgent(*jvmti_env)
      .FieldAccess(jvmti_env,
                   jni_env,
                   thread,
                   method,
                   location,
                   field_klass,
                   object,
                   field);
}

void JNICALL FieldModification(jvmtiEnv* jvmti_env,
                               JNIEnv* jni_env,
                               jthread thread,
                               jmethodID method,
                               jlocation location,
                               jclass field_klass,
                               jobject object,
                               jfieldID field,
                               char signature_type,
                               jvalue new_value) {
  GetAgent(*jvmti_env)
      .FieldModification(jvmti_env,
                         jni_env,
                         thread,
                         method,
                         location,
                         field_klass,
                         object,
                         field,
                         signature_type,
                         new_value);
}

}  // namespace phasicj::tracelogger
