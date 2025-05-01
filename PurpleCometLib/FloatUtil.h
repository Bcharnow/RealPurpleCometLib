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
inline bool apxequal(float x1, float x2) {
    return std::fabs( x1 - x2)<.00001f;
}template <typename T>
inline const T& clamp(const T& value, const T& low, const T& high) {
    return (value < low) ? low : (value > high) ? high : value;
}   template<typename T>
inline T lerp(T a, T b, double t) {
    return a + (b - a) * t;
}
inline float abs(float x) {
    return x < 0 ? -x : x;
}
inline float log(float base,float x){
    return log(x)/log(base);
}