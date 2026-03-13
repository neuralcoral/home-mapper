#include "hexapod_math.h"
#include <cmath>

namespace HexapodMath {
    float cosine(float radians) {
        return std::cos(radians);
    }
    float sine(float radians) {
        return std::sin(radians);
    }
    float power(float base, float exp) {
        return std::pow(base, exp);
    }
}