def integration_test(name):
    native.cc_test(
        name = name,
        srcs = ["drivers/" + name + ".cc"],
        data = [
            "//phasicj/tracelogger:pjtracelogger",
            "//phasicj/tracelogger/testing/integration/java_test_programs:" + name,
        ],
        deps = [
            "//phasicj/tracelogger/testing/integration:jvm_invoker",
            "@gtest//:gtest_main",
        ],
    )
