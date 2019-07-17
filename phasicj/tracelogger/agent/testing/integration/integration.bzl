MACOS = "@bazel_tools//src/conditions:darwin"
LINUX = "@bazel_tools//src/conditions:linux_x86_64"

DEFAULT_JVM = "hotspot"
DEFAULT_JDK = "jdk11"

DEFAULT_JVMS = ("hotspot",)  # TODO(dwtj): Add j9 as well.
DEFAULT_JDKS = ("jdk8", "jdk11")  # TODO(dwtj): add JDK12 as well.

def simple_integration_test_matrix(
        name_prefix,
        cc_test_srcs,
        cc_test_deps,
        java_package):
    java_test_name = java_package + "_javatest"
    native.java_binary(
        name = java_test_name,
        srcs = native.glob([java_package + "/**/*.java"]),
        main_class = java_package + ".Main",
    )
    integration_test_matrix(
        name_prefix = name_prefix,
        srcs = cc_test_srcs,
        test_java_binary = ":" + java_test_name,
        deps = cc_test_deps,
    )

# A helper method to declare an `integration_test` target for each of the given
# jvm/jdk combinations. These targets are named with the form
# [name_prefix]_[jvm]_[jdk].
def integration_test_matrix(
        name_prefix,
        srcs,
        test_java_binary,
        agent = "//phasicj/tracelogger/agent:pjtracelogger",
        jvms = DEFAULT_JVMS,
        jdks = DEFAULT_JDKS,
        deps = []):
    for jvm in jvms:
        for jdk in jdks:
            integration_test(
                name = name_prefix + "_" + jvm + "_" + jdk,
                agent = agent,
                jdk = jdk,
                jvm = jvm,
                test_java_binary = test_java_binary,
                srcs = srcs,
                deps = deps,
            )

# Declares a `cc_test` target linked against the given PhasicJ TraceLogger and
# JVM.
def integration_test(
        name,
        srcs,
        test_java_binary,
        agent = "//phasicj/tracelogger/agent:pjtracelogger",
        jvm = "hotspot",
        jdk = "jdk11",
        deps = []):
    native.cc_test(
        name = name,
        srcs = srcs,
        data = [
            agent,
            test_java_binary,
        ],
        deps = deps + select({
            MACOS: ["@net_adoptopenjdk_" + jdk + "_macos_" + jvm + "//:libjvm"],
            LINUX: ["@net_adoptopenjdk_" + jdk + "_linux_" + jvm + "//:libjvm"],
        }),
        linkopts = [
            "-ldl",  # Make `dlopen()` and friends work.
        ],
    )
