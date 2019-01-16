workspace(name = "PhasicJ")  # phasicj.org

# STANDARD LOAD STATEMENTS ###################################################

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")
load("@bazel_tools//tools/build_defs/repo:maven_rules.bzl", "maven_dependency_plugin", "maven_jar")

# CONFIGURE GOOGLETEST #######################################################

GOOGLETEST_COMMIT = "2fe3bd994b3189899d93f1d5a881e725e046fdc2"  # v1.8.1

git_repository(
    name = "gtest",
    commit = GOOGLETEST_COMMIT,
    remote = "https://github.com/google/googletest",
)

# CONFIGURE JUNIT 5 ###########################################################
# Adapted from https://github.com/junit-team/junit5-samples/blob/d0cc2270838dc5e45813f48d3bba11d6be61ce2d/junit5-jupiter-starter-bazel/WORKSPACE
# TODO: Remove this once JUnit 5 is natively supported by Bazel. See https://github.com/bazelbuild/bazel/issues/6681

load(":bazel/junit5.bzl", "junit_jupiter_java_repositories", "junit_platform_java_repositories")

maven_server(
    name = "default",
    url = "http://central.maven.org/maven2/",
)

JUNIT_JUPITER_VERSION = "5.3.2"
JUNIT_PLATFORM_VERSION = "1.3.2"

junit_jupiter_java_repositories(
    version = JUNIT_JUPITER_VERSION,
)

junit_platform_java_repositories(
    version = JUNIT_PLATFORM_VERSION,
)

# CONFIGURE PROTOBUF #########################################################

http_archive(
    name = "com_google_protobuf",
    sha256 = "d7a221b3d4fb4f05b7473795ccea9e05dab3b8721f6286a95fffbffc2d926f8b",
    strip_prefix = "protobuf-3.6.1",
    urls = ["https://github.com/google/protobuf/archive/v3.6.1.zip"],
)

# CONFIGURE Boost Libraries ##################################################

git_repository(
    name = "com_github_nelhage_rules_boost",
    commit = "c1d618315fa152958baef8ea0d77043eebf7f573",
    remote = "https://github.com/nelhage/rules_boost",
)

load("@com_github_nelhage_rules_boost//:boost/boost.bzl", "boost_deps")
boost_deps()

