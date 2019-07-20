// Copyright 2019 David Johnston

#ifndef PHASICJ_JMMEVENTS_EVENT_ADAPTER_H_
#define PHASICJ_JMMEVENTS_EVENT_ADAPTER_H_

#include "jni.h"
#include "jvmti.h"

#include "phasicj/jmmevents/jmm_action_listener.h"

namespace phasicj::jmmevents {

/// Attaches to a Java Virtual Machine instance via the Java Virtual Machine
/// Tooling Interface (JVMTI) in order to send events to a appropriate
/// JmmActionListener instances.
class JmmActionAdapter {

 public:
  JmmActionAdapter(JavaVM &jvm, JmmActionListener* listener);
  ~JmmActionAdapter();

  static constexpr auto MINIMUM_REQUIRED_JVMTI_VERSION = JVMTI_VERSION_1_2;

 private:
  jvmtiEnv* jvmti_env_;
  JmmActionListener* listener_;

  static jvmtiEnv* NewJvmtiEnv(JavaVM &jvm);
};

}  // namespace phasicj::jmmevents

#endif //PHASICJ_JMMEVENTS_EVENT_ADAPTER_H_
