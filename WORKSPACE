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

load("@bazel_skylib//:lib.bzl", "versions")
versions.check(minimum_bazel_version = "0.22.0")

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
    # jdk8u202-b08
    name = "net_adoptopenjdk_jdk8_macos_hotspot",
    sha256 = "35e8f9b18f6c7b627dba13a4c6f45e6266552ccd7156043d92391443db0d60d6",
    strip_prefix = "jdk8u202-b08/Contents/Home",
    urls = ["https://github.com/AdoptOpenJDK/openjdk8-binaries/releases/download/jdk8u202-b08/OpenJDK8U-jdk_x64_mac_hotspot_8u202b08.tar.gz"],
    build_file = "//:bazel/net_adoptopenjdk_jdk8_macos_hotspot.BUILD",
)

http_archive(
    # TODO(dwtj): Change this to a release build once AdoptOpenJDK a build of JDK8 with j9.
    # Nightly: 2019-01-21
    name = "net_adoptopenjdk_jdk8_macos_j9",
    sha256 = "399e7635be2176cd52b0992806b91a41b71d6429fb43cde1ba27835f0ce63e97",
    strip_prefix = "jdk8u202-b01/Contents/Home",
    urls = ["https://github.com/AdoptOpenJDK/openjdk8-binaries/releases/download/jdk8u-2019-01-21-09-29/OpenJDK8U-jdk_x64_mac_openj9_2019-01-21-09-29.tar.gz"],
    build_file = "//:bazel/net_adoptopenjdk_jdk8_macos_j9.BUILD",
)

http_archive(
    # jdk8u202-b08
    name = "net_adoptopenjdk_jdk8_linux_hotspot",
    sha256 = "f5a1c9836beb3ca933ec3b1d39568ecbb68bd7e7ca6a9989a21ff16a74d910ab",
    strip_prefix = "jdk8u202-b08",
    urls = ["https://github.com/AdoptOpenJDK/openjdk8-binaries/releases/download/jdk8u202-b08/OpenJDK8U-jdk_x64_linux_hotspot_8u202b08.tar.gz"],
    build_file = "//:bazel/net_adoptopenjdk_jdk8_linux_hotspot.BUILD",
)

http_archive(
    # jdk8u202-b08
    name = "net_adoptopenjdk_jdk8_linux_j9",
    sha256 = "86adb6f5cb85950687ca2e568e2e284eedd25a633f68c8780a19017c16712ac9",
    strip_prefix = "jdk8u202-b08",
    urls = ["https://github.com/AdoptOpenJDK/openjdk8-binaries/releases/download/jdk8u202-b08/OpenJDK8U-jdk_x64_linux_openj9_8u202b08.tar.gz"],
    build_file = "//:bazel/net_adoptopenjdk_jdk8_linux_j9.BUILD",
)

# JDK 11 Builds

http_archive(
    # jdk-11.0.1+13
    name = "net_adoptopenjdk_jdk11_macos_hotspot",
    sha256 = "e219e7e2d586ed09ae65f4ec390fca5d5f0c37a61b47677648610194daf1aaa7",
    strip_prefix = "jdk-11.0.1+13/Contents/Home",
    urls = ["https://github.com/AdoptOpenJDK/openjdk11-binaries/releases/download/jdk-11.0.1%2B13/OpenJDK11U-jdk_x64_mac_hotspot_11.0.1_13.tar.gz"],
    build_file = "//:bazel/adoptopenjdk.BUILD",
)

http_archive(
    # jdk-11.0.1+13
    name = "net_adoptopenjdk_jdk11_macos_j9",
    sha256 = "b8960753a66190fa81982682357a2449b4183f3e23c20a5e3b4cf01e2989846b",
    strip_prefix = "jdk-11.0.1+13/Contents/Home",
    urls = ["https://github.com/AdoptOpenJDK/openjdk11-binaries/releases/download/jdk-11.0.1%2B13/OpenJDK11U-jdk_x64_mac_openj9_jdk-11.0.1_13_openj9-0.11.0_11.0.1_13.tar.gz"],
    build_file = "//:bazel/adoptopenjdk.BUILD",
)

http_archive(
    # jdk-11.0.1+13
    name = "net_adoptopenjdk_jdk11_linux_hotspot",
    sha256 = "22bd2f1a2e0cb6e4075967bfeda4a960b0325879305aa739a0ba2d6e5cd4c3e2",
    strip_prefix = "jdk-11.0.1+13",
    urls = ["https://github.com/AdoptOpenJDK/openjdk11-binaries/releases/download/jdk-11.0.1%2B13/OpenJDK11U-jdk_x64_linux_hotspot_11.0.1_13.tar.gz"],
    build_file = "//:bazel/adoptopenjdk.BUILD",
)

http_archive(
    # jdk-11.0.1+13
    name = "net_adoptopenjdk_jdk11_linux_j9",
    sha256 = "ef9bf07cba79082285a9d426ea4eb3e8df57561ce2afe07cc5f299a8fa203279",
    strip_prefix = "jdk-11.0.1+13",
    urls = ["https://github.com/AdoptOpenJDK/openjdk11-binaries/releases/download/jdk-11.0.1%2B13/OpenJDK11U-jdk_x64_linux_openj9_jdk-11.0.1_13_openj9-0.11.0_11.0.1_13.tar.gz"],
    build_file = "//:bazel/adoptopenjdk.BUILD",
)

