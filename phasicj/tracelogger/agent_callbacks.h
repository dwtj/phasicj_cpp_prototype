// Copyright 2019 David Johnston

#ifndef PHASICJ_TRACELOGGER_AGENT_CALLBACKS_H_
#define PHASICJ_TRACELOGGER_AGENT_CALLBACKS_H_

#include <list>

#include "jvmti.h"

namespace phasicj::tracelogger {

void JNICALL FieldAccess(jvmtiEnv* jvmti_env,
                         JNIEnv* jni_env,
                         jthread thread,
                         jmethodID method,
                         jlocation location,
                         jclass field_klass,
                         jobject object,
                         jfieldID field);

void JNICALL FieldModification(jvmtiEnv* jvmti_env,
                               JNIEnv* jni_env,
                               jthread thread,
                               jmethodID method,
                               jlocation location,
                               jclass field_klass,
                               jobject object,
                               jfieldID field,
                               char signature_type,
                               jvalue new_value);

struct EventNotificationConfig {
  jvmtiEventMode mode;
  jvmtiEvent event_type;
  jthread thread;
};

constexpr EventNotificationConfig INITIAL_AGENT_EVENT_NOTIFICATION_CONFIGS[]{
    {
        .mode = JVMTI_ENABLE,
        .event_type = JVMTI_EVENT_FIELD_ACCESS,
        .thread = nullptr,
    },
    {
        .mode = JVMTI_ENABLE,
        .event_type = JVMTI_EVENT_FIELD_MODIFICATION,
        .thread = nullptr,
    },
};

constexpr jvmtiEventCallbacks INITIAL_AGENT_CALLBACKS{
    .VMInit = nullptr,
    .VMDeath = nullptr,
    .ThreadStart = nullptr,
    .ThreadEnd = nullptr,
    .ClassFileLoadHook = nullptr,
    .ClassLoad = nullptr,
    .ClassPrepare = nullptr,
    .VMStart = nullptr,
    .Exception = nullptr,
    .ExceptionCatch = nullptr,
    .SingleStep = nullptr,
    .FramePop = nullptr,
    .Breakpoint = nullptr,
    .FieldAccess = FieldAccess,
    .FieldModification = FieldModification,
};

}  // namespace phasicj::tracelogger

#endif  // PHASICJ_TRACELOGGER_AGENT_CALLBACKS_H_
