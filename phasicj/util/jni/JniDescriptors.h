// Copyright 2019 David Johnston

#ifndef PHASICJ_UTIL_JNI_DESCRIPTORS_H_
#define PHASICJ_UTIL_JNI_DESCRIPTORS_H_

#include <string>

namespace phasicj::util::jni {

using std::string;

// TODO(dwtj): Turn these type aliases into something supporting type safety.

// See Liang (1999) 12.3.2
using class_descriptor = string;

// See Liang (1999) 12.3.3
using field_descriptor = string;

// See Liang (1999) 12.3.4
using method_descriptor = string;

}  // namespace phasicj::util::jni

#endif  // PHASICJ_UTIL_JNI_DESCRIPTORS_H_
