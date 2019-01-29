//
// Created by dwtj on 1/28/19.
//

#ifndef PHASICJ_UTIL_JVMTI_FIELDS_H_
#define PHASICJ_UTIL_JVMTI_FIELDS_H_

namespace phasicj::util::jvmti {

std::optional<bool> IsFieldVolatile(jvmtiEnv& jvmti_env,
                                    const jclass field_klass,
                                    const jfieldID field);

}  // namespace phasicj::util::jvmti {

#endif  // PHASICJ_UTIL_JVMTI_FIELDS_H_
