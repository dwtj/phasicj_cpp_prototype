def tracelogger_test(name, srcs, javadeps, size = "small"):
    native.cc_test(
        name = name,
        srcs = srcs,
        data = javadeps + ["//phasicj/tracelogger:pjtracelogger"],
        deps = [
            "//phasicj/tracelogger/test:jvm_invoker",
        ],
        size = size,
    )

def tracelogger_static_test(name, srcs, javadeps, size = "small"):
    native.cc_test(
        name = name,
        srcs = srcs,
        data = javadeps,
        deps = [
            "//phasicj/tracelogger:agent_static",
            "//phasicj/tracelogger/test:jvm_invoker",
        ],
        linkstatic = True,
        size = size,
    )
