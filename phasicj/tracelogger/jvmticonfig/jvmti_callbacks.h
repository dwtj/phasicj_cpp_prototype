// Copyright 2019 David Johnston

// This file declares the functions which are meant to be registered with JVMTI
// as event callbacks.
//
// Each callback function in this file is designed to be usable as a C-style
// function pointer, so that it can be passed to JVMTI's `SetEventCallbacks()`.
// Each callback is a simple wrapper around the proper event handler. The event
// is forwarded to either a `GlobalHandler` (accessed via the JVMTI's
// environment's `GetEnvironmentLocalStorage()` [1] or a `LocalHandler`,
// accessed via the JVMTI environment's `GetThreadLocalStorage()` [2].
//
// [1](https://docs.oracle.com/en/java/javase/11/docs/specs/jvmti.html#GetEnvironmentLocalStorage)
// [2](https://docs.oracle.com/en/java/javase/11/docs/specs/jvmti.html#GetThreadLocalStorage)

#ifndef PHASICJ_TRACELOGGER_JVMTICONF_CALLBACKS_H_
#define PHASICJ_TRACELOGGER_JVMTICONF_CALLBACKS_H_

#include "jni.h"
#include "jvmti.h"

namespace phasicj::tracelogger::jvmtievents {

struct EventNotificationConfig {
  jvmtiEventMode mode;
  jvmtiEvent event_type;
  jthread thread;
};

inline constexpr EventNotificationConfig INITIAL_EVENT_NOTIFICATION_CONFIGS[]{
    {
        .mode = JVMTI_ENABLE,
        .event_type = JVMTI_EVENT_THREAD_START,
        .thread = nullptr,
    },
    {
        .mode = JVMTI_ENABLE,
        .event_type = JVMTI_EVENT_THREAD_END,
        .thread = nullptr,
    },
    {
        .mode = JVMTI_ENABLE,
        .event_type = JVMTI_EVENT_CLASS_PREPARE,
        .thread = nullptr,
    },
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
    {
        .mode = JVMTI_ENABLE,
        .event_type = JVMTI_EVENT_OBJECT_FREE,
        .thread = nullptr,
    },
    {
        .mode = JVMTI_ENABLE,
        .event_type = JVMTI_EVENT_VM_OBJECT_ALLOC,
        .thread = nullptr,
    },
    {
        .mode = JVMTI_ENABLE,
        .event_type = JVMTI_EVENT_VM_DEATH,
        .thread = nullptr,
    },
};

void JNICALL ThreadStart(jvmtiEnv* jvmti_env, JNIEnv* jni_env, jthread thread);

void JNICALL ThreadEnd(jvmtiEnv* jvmti_env, JNIEnv* jni_env, jthread thread);

void JNICALL ClassPrepare(jvmtiEnv* jvmti_env,
                          JNIEnv* jni_env,
                          jthread thread,
                          jclass klass);

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

void JNICALL ObjectFree(jvmtiEnv* jvmti_env, jlong tag);

void JNICALL VMObjectAlloc(jvmtiEnv* jvmti_env,
                           JNIEnv* jni_env,
                           jthread thread,
                           jobject object,
                           jclass object_klass,
                           jlong size);

void JNICALL VMDeath(jvmtiEnv* jvmti_env, JNIEnv* jni_env);

inline constexpr jvmtiEventCallbacks INITIAL_AGENT_CALLBACKS{
    .VMInit = nullptr,
    .VMDeath = VMDeath,
    .ThreadStart = ThreadStart,
    .ThreadEnd = ThreadEnd,
    .ClassFileLoadHook = nullptr,
    .ClassLoad = nullptr,
    .ClassPrepare = ClassPrepare,
    .VMStart = nullptr,
    .Exception = nullptr,
    .ExceptionCatch = nullptr,
    .SingleStep = nullptr,
    .FramePop = nullptr,
    .Breakpoint = nullptr,
    .FieldAccess = FieldAccess,
    .FieldModification = FieldModification,
    .MethodEntry = nullptr,
    .MethodExit = nullptr,
    .NativeMethodBind = nullptr,
    .CompiledMethodLoad = nullptr,
    .CompiledMethodUnload = nullptr,
    .DynamicCodeGenerated = nullptr,
    .DataDumpRequest = nullptr,
    .reserved72 = nullptr,
    .MonitorWait = nullptr,
    .MonitorWaited = nullptr,
    .MonitorContendedEnter = nullptr,
    .MonitorContendedEntered = nullptr,
    .reserved77 = nullptr,
    .reserved78 = nullptr,
    .reserved79 = nullptr,
    .ResourceExhausted = nullptr,
    .GarbageCollectionStart = nullptr,
    .GarbageCollectionFinish = nullptr,
    .ObjectFree = ObjectFree,
    .VMObjectAlloc = VMObjectAlloc,
    .reserved85 = nullptr,
    .SampledObjectAlloc = nullptr,
};

}  // namespace phasicj::tracelogger::jvmticonfig

#endif  // PHASICJ_TRACELOGGER_JVMTICONF_CALLBACKS_H_
