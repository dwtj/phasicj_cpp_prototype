// Copyright 2019 David Johnston

// Provides a type-safe interface for accessing a value stored in a JVMTI
// environment's thread-local storage. Essentially this just gets, sets, and
// casts values stored in thread-local storage along with some added safety
// checks. This class deletes the stored object when this object is deleted.

#ifndef PHASICJ_UTIL_JVMTI_THREAD_LOCAL_STORAGE_H_
#define PHASICJ_UTIL_JVMTI_THREAD_LOCAL_STORAGE_H_

#include <memory>

#include "jvmti.h"

namespace phasicj::util::jvmti {

using std::unique_ptr;

template<typename T>
class ThreadLocalStorage {
 public:
  void Set(jvmtiEnv& jvmti_env, unique_ptr<T> to_store);
  T& Get(jvmtiEnv& jvmti_env);
  void DeleteStored(jvmtiEnv& jvmti_env);

 private:
  static constexpr auto CURRENT_THREAD = nullptr;

  T* GetPtr(jvmtiEnv& jvmti_env);
  void SetPtr(jvmtiEnv& jvmti_env, T* stored);
};

}  // namespace phasicj::util::jvmti

#endif  // PHASICJ_UTIL_JVMTI_THREAD_LOCAL_STORAGE_H_
