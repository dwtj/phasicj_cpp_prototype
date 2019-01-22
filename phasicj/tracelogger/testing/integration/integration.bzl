MACOS = "@bazel_tools//src/conditions:darwin"
LINUX = "@bazel_tools//src/conditions:linux_x86_64"

def integration_test(name):
    for jdk in ("jdk8", "jdk11"):
        for jvm in ("hotspot", "j9"):
            native.cc_test(
                name = name + "_" + jdk + "_" + jvm,
                srcs = ["drivers/" + name + ".cc"],
                data = [
                    "//phasicj/tracelogger:pjtracelogger",
                    "//phasicj/tracelogger/testing/integration/java_test_programs:" + name,
                ],
                deps = [
                    "//phasicj/tracelogger/testing/integration:jvm_invoker",
                    "@gtest//:gtest_main",
                ] + select({
                    MACOS: ["@net_adoptopenjdk_" + jdk + "_macos_" + jvm + "//:libjvm"],
                    LINUX: ["@net_adoptopenjdk_" + jdk + "_linux_" + jvm + "//:libjvm"],
                }),
                linkopts = ["-ldl"],
                timeout = "short",
            )
