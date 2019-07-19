// Copyright 2019 David Johnston

#ifndef PHASICJ_JMMEVENTS_JVMTI_CAPABILITIES_H_
#define PHASICJ_JMMEVENTS_JVMTI_CAPABILITIES_H_

#include "jni.h"
#include "jvmti.h"

namespace phasicj::jmmevents {

bool ProvidesRequiredCapabilities(jvmtiEnv& jvmti_env);

/// @warning If `INITIAL_REQUIRED_CAPABILITIES` is changed, so should the
/// checks in `ProvidesRequiredCapabilities()`.
// TODO(dwtj): How can we avoid this field name repetition?
inline constexpr jvmtiCapabilities INITIAL_REQUIRED_CAPABILITIES = {
    .can_tag_objects = 1,
    .can_generate_field_modification_events = 1,
    .can_generate_field_access_events = 1,
    .can_get_bytecodes = 1,
    .can_get_synthetic_attribute = 0,
    .can_get_owned_monitor_info = 1,
    .can_get_current_contended_monitor = 0,
    .can_get_monitor_info = 0,
    .can_pop_frame = 0,
    .can_redefine_classes = 0,
    .can_signal_thread = 0,
    .can_get_source_file_name = 0,
    .can_get_line_numbers = 0,
    .can_get_source_debug_extension = 0,
    .can_access_local_variables = 1,
    .can_maintain_original_method_order = 0,
    .can_generate_single_step_events = 1,
    .can_generate_exception_events = 0,
    .can_generate_frame_pop_events = 0,
    .can_generate_breakpoint_events = 1,
    .can_suspend = 0,
    .can_redefine_any_class = 0,
    .can_get_current_thread_cpu_time = 0,
    .can_get_thread_cpu_time = 0,
    .can_generate_method_entry_events = 0,
    .can_generate_method_exit_events = 0,
    .can_generate_all_class_hook_events = 0,
    .can_generate_compiled_method_load_events = 0,
    .can_generate_monitor_events = 0,
    .can_generate_vm_object_alloc_events = 1,
    .can_generate_native_method_bind_events = 0,
    .can_generate_garbage_collection_events = 0,
    .can_generate_object_free_events = 1,
    .can_force_early_return = 0,
    .can_get_owned_monitor_stack_depth_info = 0,
    .can_get_constant_pool = 0,
    .can_set_native_method_prefix = 0,
    .can_retransform_classes = 0,
    .can_retransform_any_class = 0,
    .can_generate_resource_exhaustion_heap_events = 0,
    .can_generate_resource_exhaustion_threads_events = 0,
    .can_generate_early_vmstart = 0,
    .can_generate_early_class_hook_events = 0,
    .can_generate_sampled_object_alloc_events = 0,
};

}  // namespace phasicj::jmmevents

#endif  // PHASICJ_JMMEVENTS_JVMTI_CAPABILITIES_H_
