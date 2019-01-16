def tracelogger_test(name, srcs, javadeps):
    native.cc_test(
        name = name,
        srcs = srcs,
        data = javadeps + ["//phasicj/tracelogger:libpjtracelogger.so"],
        deps = [
            "//phasicj/tracelogger/test:invoker",
        ],
    )

def tracelogger_static_test(name, srcs, javadeps):
    native.cc_test(
        name = name,
        srcs = srcs,
        data = javadeps,
        deps = [
            "//phasicj/tracelogger:agent_static",
            "//phasicj/tracelogger/test:invoker",
        ],
        linkstatic = True,
    )
