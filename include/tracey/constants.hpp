#pragma once

namespace Tracey {

namespace constants {
const double pi = 3.14159265358979323846;
}

inline float clamp(float x, float min, float max) {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}

} // namespace Tracey
