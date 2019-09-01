// Copyright 2019 David Johnston

#include <stdexcept>

#include "jni.h"
#include "jvmti.h"

#include "phasicj/util/jvmti/ThreadLocalStorage.h"

namespace phasicj::util::jvmti {

using ::std::runtime_error;

static constexpr auto Error = [](auto msg) {
  throw runtime_error{msg};
};

template<typename T>
void ThreadLocalStorage<T>::Set(jvmtiEnv& jvmti_env, unique_ptr<T> to_store) {
  SetPtr(jvmti_env, to_store.release());
}

template<typename T>
T& ThreadLocalStorage<T>::Get(jvmtiEnv& jvmti_env) {
  return *GetPtr(jvmti_env);
}

template<typename T>
void ThreadLocalStorage<T>::DeleteStored(jvmtiEnv& jvmti_env) {
  delete GetPtr(jvmti_env);
  SetPtr(jvmti_env, nullptr);
}

template<typename T>
T* ThreadLocalStorage<T>::GetPtr(jvmtiEnv& jvmti_env) {
  T* stored{};
  jvmtiError err = jvmti_env.GetEnvironmentLocalStorage(
      reinterpret_cast<void**>(&stored));
  switch (err) {
    case JVMTI_ERROR_NONE:
    case JVMTI_ERROR_NULL_POINTER:
      break;
    // TODO: Give better descriptions for universal errors.
    default:
      Error("JVMTI returned an unexpected error code.");
  }
  return stored;
}

template<typename T>
void ThreadLocalStorage<T>::SetPtr(jvmtiEnv& jvmti_env, T* to_store) {
  jint err {jvmti_env.SetThreadLocalStorage(CURRENT_THREAD, to_store)};
  switch (err) {
    case JVMTI_ERROR_NONE:
      return;  // Old handler pointer successfully nulled.
    case JVMTI_ERROR_INVALID_THREAD:
      Error("Current thread is invalid.");
    case JVMTI_ERROR_THREAD_NOT_ALIVE:
      Error("Current thread is (somehow) not alive.");
    // TODO: Give better descriptions for universal errors.
    default:
      Error("JVMTI returned an unexpected error code.");
  }
}

}  // namespace phasicj::util::jvmti

