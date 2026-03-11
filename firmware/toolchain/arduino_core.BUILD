load("@rules_cc//cc:defs.bzl", "cc_library")

package(default_visibility = ["//visibility:public"])

# PlatformIO hides these compiler flags from you, but we need to declare them manually
# so the Arduino Core knows what hardware it is compiling for.
# (Assuming an Arduino Uno/Nano running at 16MHz here)
ARDUINO_DEFINES = [
    "F_CPU=16000000L",
    "ARDUINO=10806",
    "ARDUINO_AVR_UNO",
    "ARDUINO_ARCH_AVR",
]
ARDUINO_COPTS = [
    "-Os",
]

cc_library(
    name = "arduino_core",
    srcs = glob([
        "cores/arduino/*.c",
        "cores/arduino/*.cpp",
        "cores/arduino/*.S",
    ]),
    hdrs = glob([
        "cores/arduino/*.h",
        "variants/standard/*.h",
    ]) + [
    "cores/arduino/new",
    ],
    includes = [
        "cores/arduino",
        "variants/standard",
    ],
    copts = ARDUINO_COPTS,
    defines = ARDUINO_DEFINES,
    linkopts = ["-lm"], # Link the math library (required by some Arduino core functions)
)