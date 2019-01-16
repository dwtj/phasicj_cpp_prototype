def tracelogger_test(name, srcs, javadeps):
    native.cc_test(
        name = name,
        srcs = srcs,
        data = javadeps,
        # data = javadeps + [
        #     "//phasicj/tracelogger:pjtracelogger",
        # ],
        deps = [
            "//phasicj/tracelogger:pjtracelogger",
            "//phasicj/tracelogger/test:invoker"
        ],
    )

def tracelogger_static_test(name, srcs, javadeps):
    native.cc_test(
        name = name,
        srcs = srcs,
        data = javadeps,
        deps = [
            "//phasicj/tracelogger:pjtracelogger_static",
            "//phasicj/tracelogger/test:invoker",
        ],
        linkstatic = True,
    )
