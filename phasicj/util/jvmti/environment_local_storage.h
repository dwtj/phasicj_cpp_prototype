// Copyright 2019 David Johnston

// The design of `EnvironmentLocalStorage` is similar to `ThreadLocalStorage`,
// except it provides access to a `jvmtiEnv`'s environment local storage.

#ifndef PHASICJ_UTIL_JVMTI_ENVIRONMENT_LOCAL_STORAGE_H_
#define PHASICJ_UTIL_JVMTI_ENVIRONMENT_LOCAL_STORAGE_H_

#include <memory>

#include "jvmti.h"

namespace phasicj::util::jvmti {

using ::std::unique_ptr;

template<typename T>
class EnvironmentLocalStorage {
 public:
  void Set(jvmtiEnv &jvmti_env, unique_ptr<T> to_store);
  T &Get(jvmtiEnv &jvmti_env);
  void DeleteStored(jvmtiEnv &jvmti_env);

 private:
  static constexpr auto CURRENT_THREAD = nullptr;

  T *GetPtr(jvmtiEnv &jvmti_env);
  void SetPtr(jvmtiEnv &jvmti_env, T *stored);
};

} // namespace phasicj::util::jvmti

#endif  // PHASICJ_UTIL_JVMTI_ENVIRONMENT_LOCAL_STORAGE_H_
