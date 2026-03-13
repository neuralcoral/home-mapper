#ifndef HOME_MAPPER_HEXAPOD_MATH_H
#define HOME_MAPPER_HEXAPOD_MATH_H

namespace HexapodMath {
    constexpr float PI = 3.14159265358979323846f;
    constexpr float HALF_PI = 1.57079632679489661923f;
    float cosine(float radians);
    float sine(float radians);
    float power(float base, float exp);
}

#endif //HOME_MAPPER_HEXAPOD_MATH_H
