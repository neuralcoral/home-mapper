load("@rules_cc//cc:action_names.bzl", "ACTION_NAMES")
load(
    "@rules_cc//cc:cc_toolchain_config_lib.bzl",
    "feature",
    "flag_group",
    "flag_set",
    "tool_path",
)
load("@rules_cc//cc/common:cc_common.bzl", "cc_common")

def _impl(ctx):
    tool_paths = [
        tool_path(name = "gcc", path = "bin/avr-gcc"),
        tool_path(name = "ld", path = "bin/avr-ld"),
        tool_path(name = "ar", path = "bin/avr-ar"),
        tool_path(name = "cpp", path = "bin/avr-cpp"),
        tool_path(name = "gcov", path = "bin/avr-gcov"),
        tool_path(name = "nm", path = "bin/avr-nm"),
        tool_path(name = "objdump", path = "bin/avr-objdump"),
        tool_path(name = "strip", path = "bin/avr-strip"),
    ]

    features = [
        feature(
            name = "default_compiler_flags",
            enabled = True,
            flag_sets = [
                flag_set(
                    actions = [
                        ACTION_NAMES.c_compile,
                        ACTION_NAMES.cpp_compile,
                        ACTION_NAMES.assemble,
                        ACTION_NAMES.preprocess_assemble,
                    ],
                    flag_groups = [
                        flag_group(
                            flags = [
                                "-Os",
                                "-mmcu=atmega328p",  # Update to your target MCU
                                "-ffunction-sections",
                                "-fdata-sections",
                                "-no-canonical-prefixes",
                            ],
                        ),
                    ],
                ),
            ],
        ),
        feature(
            name = "default_linker_flags",
            enabled = True,
            flag_sets = [
                flag_set(
                    actions = [ACTION_NAMES.cpp_link_executable],
                    flag_groups = [
                        flag_group(
                            flags = [
                                "-mmcu=atmega328p",  # Update to your target MCU
                                "-Wl,--gc-sections",
                                "-no-canonical-prefixes",
                            ],
                        ),
                    ],
                ),
            ],
        ),
    ]

    return cc_common.create_cc_toolchain_config_info(
        ctx = ctx,
        features = features,
        cxx_builtin_include_directories = [
            "avr/include",
            "lib/gcc/avr/15.2.0/include",
        ],
        toolchain_identifier = "avr-toolchain",
        host_system_name = "local",
        target_system_name = "avr",
        target_cpu = "avr",
        target_libc = "avr-libc",
        compiler = "avr-gcc",
        abi_version = "unknown",
        abi_libc_version = "unknown",
        tool_paths = tool_paths,
    )

avr_toolchain_config = rule(
    implementation = _impl,
    attrs = {},
)
