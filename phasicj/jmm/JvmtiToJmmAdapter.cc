// Copyright 2019 David Johnston

#include <stdexcept>

#include "phasicj/jmmevents/jmm_action_adapter.h"
#include "phasicj/jmmevents/jvmti_capabilities.h"

namespace phasicj::jmmevents {

using std::runtime_error;

JmmActionAdapter::JmmActionAdapter(JavaVM &jvm, JmmTraceManager* trace_manager) :
  jvmti_env_ {NewJvmtiEnv(jvm)} {
  EnsureRequiredCapabilitiesAreProvided(*jvmti_env_);
  AddRequiredCapabilities(*jvmti_env_);
}

JmmActionAdapter::~JmmActionAdapter() {
  // TODO(dwtj): Everything!
}

jvmtiEnv* JmmActionAdapter::NewJvmtiEnv(JavaVM& jvm) {
  jvmtiEnv *jvmti_env = nullptr;
  jint err = jvm.GetEnv(reinterpret_cast<void **>(&jvmti_env),
                        JmmActionAdapter::MINIMUM_REQUIRED_JVMTI_VERSION);
  switch (err) {
    case JNI_OK:
      if (jvmti_env == nullptr) {
        throw runtime_error{"The JVM didn't return a valid JVMTI environment."};
      }
      return jvmti_env;
    case JNI_EDETACHED:
      throw runtime_error{"The current thread isn't attached to this JVM."};
    case JNI_EVERSION:
      throw runtime_error{"This JVM can't provide the required JVMTI version."};
    default:
      throw runtime_error{"An unfamiliar error code was returned from GetEnv"};
  }
}

void JmmActionAdapter::EnsureRequiredCapabilitiesAreProvided(jvmtiEnv &jvmti_env) {
  if (!ProvidesRequiredCapabilities(jvmti_env)) {
    // TODO(dwtj): Say which required capabilities aren't supported by this JVM.
    throw runtime_error{
        "JVMTI environment does not provide one or more required capabilities."
    };
  }
}

bool JmmActionAdapter::ProvidesRequiredCapabilities(jvmtiEnv& jvmti_env) {
  jvmtiCapabilities c;
  jvmti_env.GetPotentialCapabilities(&c);
  return c.can_tag_objects && c.can_generate_field_modification_events &&
      c.can_generate_field_access_events && c.can_get_bytecodes &&
      c.can_get_owned_monitor_info && c.can_access_local_variables &&
      c.can_generate_single_step_events &&
      c.can_generate_breakpoint_events &&
      c.can_generate_vm_object_alloc_events &&
      c.can_generate_object_free_events;
}

void JmmActionAdapter::AddRequiredCapabilities(jvmtiEnv& jvmti_env) {
  jint err = jvmti_env.AddCapabilities(&INITIAL_REQUIRED_CAPABILITIES);
  if (err != JVMTI_ERROR_NONE) {
    // TODO(dwtj): Check error codes to improve explanation of the failure.
    throw runtime_error{
      "Failed to add required capabilities to this JVMTI environment."
    };
  }
}

// TODO(dwtj): Use something like this to set thread-local storage to point to
//  the JmmTrace instance. Each thread has a pointer to decrease
//  contention.
// TODO(dwtj): But will it actually decrease contention? Where would contention
//  happen anyway? In the lookup to JVMTI Environment Global Storage?

//Trace* TraceManager::GetTracePtr() const {
//  constexpr auto Error = [](auto msg) {
//    BOOST_LOG_TRIVIAL(error) << msg;
//    throw runtime_error{msg};
//  };
//
//  Trace* trace;
//  jvmtiError err;
//  err = jvmti_env_->GetThreadLocalStorage(CURRENT_THREAD,
//                                          reinterpret_cast<void**>(&trace));
//
//  switch (err) {
//    case JVMTI_ERROR_NONE:
//    case JVMTI_ERROR_NULL_POINTER:
//      break;
//    case JVMTI_ERROR_INVALID_THREAD:
//      Error("JVMTI thinks that the current thread is invalid");
//    case JVMTI_ERROR_THREAD_NOT_ALIVE:
//      Error("The current thread is not alive (somehow).");
//    default:
//      // TODO: Give better descriptions for universal errors.
//      Error("JVMTI returned an unexpected error code.");
//  }
//
//  return trace;
//}
//
//void TraceManager::SetTracePtr(Trace* trace) {
//  constexpr auto Error = [](auto msg) { throw runtime_error{msg}; };
//
//  jvmtiError err = jvmti_env_->SetThreadLocalStorage(CURRENT_THREAD, reinterpret_cast<void*>(trace));
//
//  switch (err) {
//    case JVMTI_ERROR_NONE:
//      break;  // The handler was successfully retrieved.
//    case JVMTI_ERROR_INVALID_THREAD:
//      Error("Current thread is invalid.");
//    case JVMTI_ERROR_THREAD_NOT_ALIVE:
//      Error("Current thread is not alive (somehow).");
//    default:
//      // TODO: Give better descriptions for universal errors.
//      Error("JVMTI returned an unexpected error code.");
//  }
//}


}  // namespace phasicj::jmm

namespace {
void JNICALL phasicj_jmmevents_ThreadStart(jvmtiEnv* jvmti_env,
JNIEnv* jni_env,
    jthread thread) {
// TODO(dwtj): Replace with refactored receiver
// Agent::EmbeddedReciever(*jvmti_env).ThreadStart(*jvmti_env, *jni_env,
// thread);
}

void JNICALL phasicj_jmmevents_ThreadEnd(jvmtiEnv* jvmti_env,
JNIEnv* jni_env,
    jthread thread) {
// TODO(dwtj): Replace with refactored receiver
// Agent::EmbeddedReciever(*jvmti_env).ThreadEnd(*jvmti_env, *jni_env,
// thread);
}

void JNICALL phasicj_jmmevents_ClassPrepare(jvmtiEnv* jvmti_env,
JNIEnv* jni_env,
    jthread thread,
jclass klass) {
// TODO(dwtj): Replace with refactored receiver
/*
Agent::EmbeddedReciever(*jvmti_env).ClassPrepare(*jvmti_env,
                                            *jni_env,
                                            thread,
                                            klass);
                                            */
}

void JNICALL phasicj_jmmevents_FieldAccess(jvmtiEnv* jvmti_env,
JNIEnv* jni_env,
    jthread thread,
jmethodID method,
    jlocation location,
jclass field_klass,
    jobject object,
jfieldID field) {
// TODO(dwtj): Replace with refactored receiver
/*
Agent::EmbeddedReciever(*jvmti_env).FieldAccess(*jvmti_env,
                                           *jni_env,
                                           thread,
                                           method,
                                           location,
                                           field_klass,
                                           object,
                                           field);
                                           */
}

void JNICALL phasicj_jmmevents_FieldModification(jvmtiEnv* jvmti_env,
JNIEnv* jni_env,
    jthread thread,
jmethodID method,
    jlocation location,
jclass field_klass,
    jobject object,
jfieldID field,
char signature_type,
    jvalue new_value) {
// TODO(dwtj): Replace with refactored receiver
/*
Agent::EmbeddedReciever(*jvmti_env).FieldModification(*jvmti_env,
                                                 *jni_env,
                                                 thread,
                                                 method,
                                                 location,
                                                 field_klass,
                                                 object,
                                                 field,
                                                 signature_type,
                                                 new_value);
                                                 */
}

void JNICALL phasicj_jmmevents_ObjectFree(jvmtiEnv* jvmti_env, jlong tag) {
// TODO(dwtj): Replace with refactored receiver
// Agent::EmbeddedReciever(*jvmti_env).ObjectFree(*jvmti_env, tag);
}

void JNICALL phasicj_jmmevents_VMObjectAlloc(jvmtiEnv* jvmti_env,
JNIEnv* jni_env,
    jthread thread,
jobject object,
    jclass object_klass,
jlong size) {
// TODO(dwtj): Replace with refactored receiver
/*
Agent::EmbeddedReciever(*jvmti_env).VMObjectAlloc(*jvmti_env,
                                             *jni_env,
                                             thread,
                                             object,
                                             object_klass,
                                             size);
                                             */
}

// TODO(dwtj): The documentation of the `VMDeath` JVMTI event says that no
//  events will be triggered on a JVMTI environment after a `VMDeath` event.
//  However, might there be events which are still running? Presumably,
//  background threads are still allowed to run, but I don't think that I'll
//  be using any of those.
void JNICALL phasicj_jmmevents_VMDeath(jvmtiEnv* jvmti_env, JNIEnv* jni_env) {
// TODO(dwtj): Everything!
// DeleteEmbeddedTraceLogger(jvmti_env);
// jvmti_env.DisposeEnvironment();
}

} // namespace (anonymous)
