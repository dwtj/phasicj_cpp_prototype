def jvm_tracelogger_integration_test(name, srcs, javadeps, size = "small"):
    native.cc_test(
        name = name,
        srcs = srcs,
        data = javadeps + ["//phasicj/tracelogger:pjtracelogger"],
        deps = [
            "//phasicj/tracelogger/testing/integration:jvm_invoker",
        ],
        size = size,
    )

# TODO(dwtj): Try to make this work.
#def jvm_tracelogger_static_integration_test(name, srcs, javadeps, size = "small"):
#    native.cc_test(
#        name = name,
#        srcs = srcs,
#        data = javadeps,
#        deps = [
#            "//phasicj/tracelogger:agent_static",
#            "//phasicj/tracelogger/testing:jvm_invoker",
#        ],
#        linkstatic = True,
#        size = size,
#    )
