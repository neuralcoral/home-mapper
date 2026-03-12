load("@rules_cc//cc:defs.bzl", "cc_toolchain")
load("@home_mapper//firmware/toolchain:avr_toolchain_config.bzl", "avr_toolchain_config")

package(default_visibility = ["//visibility:public"])

# This grabs every file in the downloaded avr-gcc folder (compiler, linker, headers, libc, etc.)
# Bazel needs this so it knows exactly what files to send to the sandbox for remote/hermetic execution.
filegroup(
    name = "all_files",
    srcs = glob(["**/*"]),
)

# This instantiates the Starlark logic we wrote to set the -mmcu and -Os flags
avr_toolchain_config(
    name = "avr_config",
)

# This is the final target Bazel looks for when it resolves the toolchain
cc_toolchain(
    name = "avr_cc_toolchain",
    toolchain_identifier = "avr-toolchain",
    toolchain_config = ":avr_config",
    all_files = ":all_files",
    ar_files = ":all_files",
    as_files = ":all_files",
    compiler_files = ":all_files",
    dwp_files = ":all_files",
    linker_files = ":all_files",
    objcopy_files = ":all_files",
    strip_files = ":all_files",
)
