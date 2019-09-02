workspace(name = "PhasicJ")  # phasicj.org

# Standard Load Statements ###################################################

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")
load("@bazel_tools//tools/build_defs/repo:maven_rules.bzl", "maven_dependency_plugin", "maven_jar")

# CHECK BAZEL VERSION ########################################################

http_archive(
    name = "bazel_skylib",
    url = "https://github.com/bazelbuild/bazel-skylib/releases/download/0.9.0/bazel_skylib-0.9.0.tar.gz",
    sha256 = "1dde365491125a3db70731e25658dfdd3bc5dbdfd11b840b3e987ecf043c7ca0",
)

load("@bazel_skylib//:workspace.bzl", "bazel_skylib_workspace")
bazel_skylib_workspace()

load("@bazel_skylib//lib:versions.bzl", "versions")
versions.check(
    minimum_bazel_version = "0.28.1",
    maximum_bazel_version = "0.28.1",
)

# Configure googletest #######################################################

GOOGLETEST_COMMIT = "2fe3bd994b3189899d93f1d5a881e725e046fdc2"  # v1.8.1

git_repository(
    name = "gtest",
    commit = GOOGLETEST_COMMIT,
    remote = "https://github.com/google/googletest",
)

# Configure JUnit 5 ###########################################################
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

# Configure Protobuf ##########################################################

http_archive(
    name = "com_google_protobuf",
    sha256 = "8eb5ca331ab8ca0da2baea7fc0607d86c46c80845deca57109a5d637ccb93bb4",
    strip_prefix = "protobuf-3.9.0",
    urls = ["https://github.com/protocolbuffers/protobuf/archive/v3.9.0.zip"],
)
load("@com_google_protobuf//:protobuf_deps.bzl", "protobuf_deps")
protobuf_deps()

# Configure Boost Libraries ###################################################

git_repository(
    name = "com_github_nelhage_rules_boost",
    commit = "c1d618315fa152958baef8ea0d77043eebf7f573",
    remote = "https://github.com/nelhage/rules_boost",
)

load("@com_github_nelhage_rules_boost//:boost/boost.bzl", "boost_deps")
boost_deps()


# Configure C++ Guidelines Support Library ####################################

http_archive(
    name = "gsl",
    sha256 = "837f35a9f00b2543bada8ae680e5c56af84709d36d48cdc3ed8db69df043f5b2",
    strip_prefix = "GSL-2.0.0",
    urls = ["https://github.com/microsoft/GSL/archive/v2.0.0.zip"],
    build_file = "//:bazel/gsl.BUILD",
)

# Download Remote Testing JDKs ################################################

# JDK 8 Builds

http_archive(
    # jdk8u222-b10, 2019-07-17
    name = "net_adoptopenjdk_jdk8_macos_hotspot",
    sha256 = "9605fd00d2960934422437f601c7a9a1c5537309b9199d5bc75f84f20cd29a76",
    strip_prefix = "jdk8u222-b10/Contents/Home",
    urls = ["https://github.com/AdoptOpenJDK/openjdk8-binaries/releases/download/jdk8u222-b10/OpenJDK8U-jdk_x64_mac_hotspot_8u222b10.tar.gz"],
    build_file = "//:bazel/net_adoptopenjdk_jdk8_macos_hotspot.BUILD",
)

http_archive(
    # jdk8u222-b10, openj9-0.15.1, 2019-07-18
    name = "net_adoptopenjdk_jdk8_macos_j9",
    sha256 = "df185e167756332163633a826b329db067f8a721f7d5d27f0b353a35fc415de0",
    strip_prefix = "jdk8u222-b10/Contents/Home",
    urls = ["https://github.com/AdoptOpenJDK/openjdk8-binaries/releases/download/jdk8u222-b10_openj9-0.15.1/OpenJDK8U-jdk_x64_mac_openj9_8u222b10_openj9-0.15.1.tar.gz"],
    build_file = "//:bazel/net_adoptopenjdk_jdk8_macos_j9.BUILD",
)

http_archive(
    # jdk8u222-b10, 2019-07-17
    name = "net_adoptopenjdk_jdk8_linux_hotspot",
    sha256 = "37356281345b93feb4212e6267109b4409b55b06f107619dde4960e402bafa77",
    strip_prefix = "jdk8u222-b10",
    urls = ["https://github.com/AdoptOpenJDK/openjdk8-binaries/releases/download/jdk8u222-b10/OpenJDK8U-jdk_x64_linux_hotspot_8u222b10.tar.gz"],
    build_file = "//:bazel/net_adoptopenjdk_jdk8_linux_hotspot.BUILD",
)

http_archive(
    # jdk8u222-b10, openj9-0.15.1, 2019-07-18
    name = "net_adoptopenjdk_jdk8_linux_j9",
    sha256 = "20cff719c6de43f8bb58c7f59e251da7c1fa2207897c9a4768c8c669716dc819",
    strip_prefix = "jdk8u222-b10",
    urls = ["https://github.com/AdoptOpenJDK/openjdk8-binaries/releases/download/jdk8u222-b10_openj9-0.15.1/OpenJDK8U-jdk_x64_linux_openj9_8u222b10_openj9-0.15.1.tar.gz"],
    build_file = "//:bazel/net_adoptopenjdk_jdk8_linux_j9.BUILD",
)

# JDK 11 Builds

http_archive(
    # jdk-11.0.4+11, 2019-07-18
    name = "net_adoptopenjdk_jdk11_macos_hotspot",
    sha256 = "a50b211f475b9497311c9b65594764d7b852b1653f249582bb20fc3c302846a5",
    strip_prefix = "jdk-11.0.4+11/Contents/Home",
    urls = ["https://github.com/AdoptOpenJDK/openjdk11-binaries/releases/download/jdk-11.0.4%2B11/OpenJDK11U-jdk_x64_mac_hotspot_11.0.4_11.tar.gz"],
    build_file = "//:bazel/net_adoptopenjdk_jdk11.BUILD",
)

http_archive(
    # jdk-11.0.4+11, openj9-0.15.1, 2019-07-18
    name = "net_adoptopenjdk_jdk11_macos_j9",
    sha256 = "7c09678d9c2d9dd0366693c6ab27bed39c76a23e7ac69b8a25c794e99dcf3ba7",
    strip_prefix = "jdk-11.0.4+11/Contents/Home",
    urls = ["https://github.com/AdoptOpenJDK/openjdk11-binaries/releases/download/jdk-11.0.4%2B11_openj9-0.15.1/OpenJDK11U-jdk_x64_mac_openj9_11.0.4_11_openj9-0.15.1.tar.gz"],
    build_file = "//:bazel/net_adoptopenjdk_jdk11.BUILD",
)

http_archive(
    # jdk-11.0.4+11, 2019-07-18
    name = "net_adoptopenjdk_jdk11_linux_hotspot",
    sha256 = "90c33cf3f2ed0bd773f648815de7347e69cfbb3416ef3bf41616ab1c4aa0f5a8",
    strip_prefix = "jdk-11.0.4+11",
    urls = ["https://github.com/AdoptOpenJDK/openjdk11-binaries/releases/download/jdk-11.0.4%2B11/OpenJDK11U-jdk_x64_linux_hotspot_11.0.4_11.tar.gz"],
    build_file = "//:bazel/net_adoptopenjdk_jdk11.BUILD",
)

http_archive(
    # jdk-11.0.4+11, openj9-0.15.1, 2019-07-18
    name = "net_adoptopenjdk_jdk11_linux_j9",
    sha256 = "b1099cccc80a3f434728c9bc3b8a90395793b625f4680ca05267cf635143d64d",
    strip_prefix = "jdk-11.0.4+11",
    urls = ["https://github.com/AdoptOpenJDK/openjdk11-binaries/releases/download/jdk-11.0.4%2B11_openj9-0.15.1/OpenJDK11U-jdk_x64_linux_openj9_11.0.4_11_openj9-0.15.1.tar.gz"],
    build_file = "//:bazel/net_adoptopenjdk_jdk11.BUILD",
)
