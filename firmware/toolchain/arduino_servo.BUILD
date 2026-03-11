load("@rules_cc//cc:defs.bzl", "cc_library")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "arduino_servo",
    srcs = [
        "src/avr/Servo.cpp",
    ],
    hdrs = glob([
        "src/*.h",
        "src/avr/*.h"
    ]),
    includes = ["src"],
    # CRITICAL: Link the core so Servo.cpp can find <Arduino.h>
    deps = [
        "@arduino_core//:arduino_core",
    ],
)