// Copyright 2019 David Johnston

#ifndef PHASICJ_JMMEVENTS_EVENT_ADAPTER_H_
#define PHASICJ_JMMEVENTS_EVENT_ADAPTER_H_

#include <memory>
#include "jni.h"
#include "jvmti.h"

#include "phasicj/jmmevents/jmm_action_listener.h"

namespace phasicj::jmmevents {

using std::unique_ptr;
using std::runtime_error;

/// Attaches to a Java Virtual Machine instance via the Java Virtual Machine
/// Tooling Interface (JVMTI) in order to send events to a JmmActionListener
/// instance.
class JvmtiEventAdapter {

 public:
  JvmtiEventAdapter(JavaVM &jvm, JmmActionListener* listener);
  ~JvmtiEventAdapter();

  static constexpr auto MINIMUM_REQUIRED_JVMTI_VERSION = JVMTI_VERSION_1_2;

 private:
  jvmtiEnv* jvmti_env_;
  JmmActionListener* listener_;

  static jvmtiEnv* NewJvmtiEnv(JavaVM &jvm);
};

}  // namespace phasicj::jmmevents

#endif //PHASICJ_JMMEVENTS_EVENT_ADAPTER_H_
