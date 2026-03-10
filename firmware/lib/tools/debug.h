#ifndef DEBUG_H
#define DEBUG_H

#include <Arduino.h>

// Set to 0 to completely compile out all print statements
#define DEBUG_MODE 1

#if DEBUG_MODE
// The F() macro forces the string literal to stay in Flash memory,
// preventing it from eating your 2KB of SRAM.
#define LOG_INFO(msg) Serial.println(F(msg))

// Macro to print a variable name and its value
#define LOG_VAL(name, val) \
        Serial.print(F(name)); \
        Serial.print(F(": ")); \
        Serial.println(val)
#else
// If DEBUG_MODE is 0, these replace your logs with absolutely nothing
    #define LOG_INFO(msg)
    #define LOG_VAL(name, val)
#endif

#endif // DEBUG_H