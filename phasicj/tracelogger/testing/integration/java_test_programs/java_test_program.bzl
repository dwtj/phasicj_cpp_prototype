def java_test_program(package_name):
    native.java_binary(
        name = package_name,
        srcs = native.glob([package_name + "/**/*.java"]),
        main_class = package_name + ".Main",
        javacopts = [
            "-source 8",
            "-target 8",
        ],
    )
