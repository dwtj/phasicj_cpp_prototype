licenses(["restricted"])  # GPLv2, portions of GPLv2 with "Classpath" exception

package(
    default_visibility = ["//visibility:public"],
)

cc_import(
    name = "libjvm",
    hdrs = ["include/jni.h"],
    shared_library = "jre/lib/server/libjvm.dylib",
)

cc_library(
    name = "jni_headers",
    hdrs = ["include/jni.h"],
    deps = [":jni_md_headers"],
    strip_include_prefix = "include",
)

cc_library(
    name = "jni_md_headers",
    hdrs = ["include/darwin/jni_md.h"],
    strip_include_prefix = "include/darwin",
    visibility = ["//visibility:private"],
)

cc_library(
    name = "jvmti_headers",
    hdrs = [
        "include/jvmti.h",
        "include/jvmticmlr.h",
    ],
    strip_include_prefix = "include",
)
