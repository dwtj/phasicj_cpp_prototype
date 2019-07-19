// Copyright 2019 David Johnston

#include "jni.h"  // NOLINT
#include "jvmti.h"  // NOLINT

#include "phasicj/jmmevents/jvmti_capabilities.h"

namespace phasicj::jmmevents {

bool ProvidesRequiredCapabilities(jvmtiEnv& jvmti_env) {
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

}  // namespace phasicj::jmmevents
