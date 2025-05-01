#include <cmath>
#pragma once

constexpr float Pi = 3.14159265358979323846f;
constexpr float DEG2RAD =Pi / 180.0f;
inline float toRadians(float degrees) {
    return degrees * DEG2RAD;
}
inline float toDegrees(float rad) {
    return rad/DEG2RAD;
}
bool apxequal(float x1, float x2) {
    return std::fabs( x1 - x2)<.00001f;
}