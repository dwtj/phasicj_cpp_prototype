// Copyright 2019 David Johnston

#ifndef PHASICJ_TRACELOGGER_JVMTIAGENT_LIFETIME_EVENT_CALLBACKS_H_
#define PHASICJ_TRACELOGGER_JVMTIAGENT_LIFETIME_EVENT_CALLBACKS_H_

#include "jni.h"

namespace phasicj::tracelogger::jvmtiagent {

  jint OnLoad(JavaVM* jvm, char* options, void* reserved);
  jint OnAttach(JavaVM *vm, char *options, void *reserved);
  void OnUnload(JavaVM* vm);

}  // namespace phasicj::tracelogger::jvmtiagent {

#endif  // PHASICJ_TRACELOGGER_JVMTIAGENT_LIFETIME_EVENT_CALLBACKS_H_
