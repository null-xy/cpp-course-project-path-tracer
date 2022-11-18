#pragma once

#include <limits>

namespace Tracey {

namespace constants {
const double pi = 3.14159265358979323846;
const double near_zero = 1e-8;
const double infinity = std::numeric_limits<double>::infinity();
}

inline double clamp(double x, double min, double max) {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}

} // namespace Tracey
