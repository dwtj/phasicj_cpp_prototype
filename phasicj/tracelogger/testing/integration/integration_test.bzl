MACOS = "@bazel_tools//src/conditions:darwin"
LINUX = "@bazel_tools//src/conditions:linux_x86_64"

def integration_test(name):
    jdks = ("jdk8", "jdk11")

    #jvms = ("hotspot", "j9")  # TODO(dwtj): Disable j9 until I can figure it out.
    jvms = ("hotspot",)
    for jdk in jdks:
        for jvm in jvms:
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
                linkopts = ["-ldl"],  # Support programmatic dynamic linkage
                # (i.e. make `dlopen()` and friends work).
                timeout = "short",
            )
