#include "hexapod_math.h"
#include <Arduino.h>

namespace HexapodMath {
    float cosine(float radians) {
        return cos(radians);
    }
    float sine(float radians) {
        return sin(radians);
    }
    float power(float base, float exp) {
        return pow(base, exp);
    }
}
