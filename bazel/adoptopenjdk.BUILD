licenses(["restricted"])  # GPLv2, portions of GPLv2 with "Classpath" exception

package(
    default_visibility = ["//visibility:public"],
)

MACOS = "@bazel_tools//src/conditions:darwin_x86_64"
LINUX = "@bazel_tools//src/conditions:linux_x86_64"

cc_import(
    name = "libjvm",
    hdrs = ["include/jni.h"],
    shared_library = select({
        MACOS: "lib/server/libjvm.dylib",
        LINUX: "lib/server/libjvm.so",
    }),
)

cc_library(
    name = "jni_headers",
    hdrs = ["include/jni.h"],
    deps = [":jni_md_headers"],
    strip_include_prefix = "include",
)

cc_library(
    name = "jni_md_headers",
    hdrs = select({
        MACOS: ["include/darwin/jni_md.h"],
        LINUX: ["include/linux/jni_md.h"],
    }),
    strip_include_prefix = select({
        MACOS: "include/darwin",
        LINUX: "include/linux",
    }),
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