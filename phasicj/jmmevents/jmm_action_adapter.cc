// Copyright 2019 David Johnston

#include <stdexcept>

#include "phasicj/jmmevents/jmm_action_adapter.h"
#include "phasicj/jmmevents/jvmti_capabilities.h"

namespace phasicj::jmmevents {

using std::runtime_error;

JmmActionAdapter::JmmActionAdapter(JavaVM &jvm, JmmActionListener* listener) :
  jvmti_env_ {NewJvmtiEnv(jvm)}, listener_{listener} { }

JmmActionAdapter::~JmmActionAdapter() {
  // TODO(dwtj): Everything!
}

jvmtiEnv* JmmActionAdapter::NewJvmtiEnv(JavaVM& jvm) {
  jint err;
  jvmtiEnv *jvmti_env = nullptr;

  err = jvm.GetEnv(reinterpret_cast<void **>(&jvmti_env),
                   MINIMUM_REQUIRED_JVMTI_VERSION);
  if (err != JNI_OK) {
    throw runtime_error {
        // TODO(dwtj): Improve explanation with more specific description.
        "Could not obtain a compatible JVMTI environment from this JVM."
    };
  }

  if (!ProvidesRequiredCapabilities(*jvmti_env)) {
    throw runtime_error{
        // TODO(dwtj): Improve explanation with more specific description.
        "JVMTI environment does not provide one or more required capabilities."
    };
  }

  err = jvmti_env->AddCapabilities(&INITIAL_REQUIRED_CAPABILITIES);
  if (err != JVMTI_ERROR_NONE) {
    // TODO(dwtj): Improve explanation.
    throw runtime_error{"Failed to add one or more required capabilities."};
  }

  return jvmti_env;
}

// TODO(dwtj): Use something like this to set thread-local storage to point to
//  the JmmActionListener instance. Each thread has a pointer to decrease
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


}  // namespace phasicj::jmmevents
