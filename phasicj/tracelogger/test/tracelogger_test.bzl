def tracelogger_test(name, srcs, javadeps, size="small"):
    native.cc_test(
        name = name,
        srcs = srcs,
        data = javadeps + ["//phasicj/tracelogger:libpjtracelogger.so"],
        deps = [
            "//phasicj/tracelogger/test:invoker",
        ],
        size = size,
    )

def tracelogger_static_test(name, srcs, javadeps, size="small"):
    native.cc_test(
        name = name,
        srcs = srcs,
        data = javadeps,
        deps = [
            "//phasicj/tracelogger:agent_static",
            "//phasicj/tracelogger/test:invoker",
        ],
        linkstatic = True,
        size = size,
    )
