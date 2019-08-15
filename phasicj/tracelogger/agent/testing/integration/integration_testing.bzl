DEFAULT_JVMS = ("hotspot",)  # TODO(dwtj): Add j9 as well.
DEFAULT_JDKS = ("jdk8", "jdk11")  # TODO(dwtj): add JDK12 as well.

def get_libjvm_dep(jdk, jvm):
    MACOS = "@bazel_tools//src/conditions:darwin"
    LINUX = "@bazel_tools//src/conditions:linux_x86_64"
    return select({
        MACOS: ["@net_adoptopenjdk_" + jdk + "_macos_" + jvm + "//:libjvm"],
        LINUX: ["@net_adoptopenjdk_" + jdk + "_linux_" + jvm + "//:libjvm"],
    })

# TODO(dwtj): Refactor this to remove the jar argument to eliminate repetition.
def integration_smoke_test_matrix(
        name_prefix,
        test_java_binary_target,
        test_java_binary_jar,
        test_java_main_class):
    integration_test_matrix(
        name_prefix = name_prefix,
        srcs = ["smoke_test.cc"],
        test_java_binary = test_java_binary_target,
        deps = [
            "@gtest",
            ":jvm_invoker",
        ],
        # TODO(dwtj): Use `local_defines` instead once it becomes available.
        defines = [
            "SMOKE_TEST_JAVA_BINARY_JAR_TO_INVOKE=" + test_java_binary_jar,
            "SMOKE_TEST_JAVA_MAIN_CLASS_TO_INVOKE=" + test_java_main_class,
        ],
    )

# A helper method to declare an `integration_test` target for each of the given
# jvm/jdk combinations. These `integration_test` targets are named with the
# form [name_prefix]_[jvm]_[jdk].
def integration_test_matrix(
        name_prefix,
        srcs,
        test_java_binary,
        agent = "//phasicj/tracelogger/agent:pjtracelogger",
        deps = [],
        defines = []):
    for jvm in DEFAULT_JVMS:
        for jdk in DEFAULT_JDKS:
            integration_test(
                name = name_prefix + "_" + jvm + "_" + jdk,
                agent = agent,
                jdk = jdk,
                jvm = jvm,
                test_java_binary = test_java_binary,
                srcs = srcs,
                deps = deps,
                defines = defines,
            )

# Declares a `cc_test` target linked against the given PhasicJ TraceLogger agent
# and JVM.
def integration_test(
        name,
        srcs,
        test_java_binary,
        agent = "//phasicj/tracelogger/agent:pjtracelogger",
        jvm = "hotspot",
        jdk = "jdk11",
        deps = [],
        defines = []):
    native.cc_test(
        name = name,
        srcs = srcs,
        copts = ["-std=c++17"],
        data = [
            agent,
            test_java_binary,
        ],
        deps = deps + get_libjvm_dep(jdk, jvm),
        linkopts = [
            "-ldl",  # Make `dlopen()` and friends work.
        ],
        defines = defines,
    )
