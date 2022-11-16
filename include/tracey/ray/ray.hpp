#pragma once

#include <eigen3/Eigen/Dense>

using Eigen::Vector3f;

namespace Tracey {

class Ray {
 public:
  Ray() {}
  Ray(const Vector3f& origin, const Vector3f& direction)
      : origin_(origin), direction_(direction) {}
  Vector3f get_origin() const { return origin_; }

  Vector3f get_direction() const { return direction_; }
  Vector3f at(float f) const { return origin_ + direction_ * f; }

  friend inline Vector3f RandomInUnitSphere();
  friend inline Vector3f Reflect(const Vector3f& v, const Vector3f& n);

 private:
  Vector3f origin_;
  Vector3f direction_;
};

Vector3f RandomInUnitSphere() {
  Vector3f p;

  while (true) {
    float r = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    float g = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    float b = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    Vector3f p(r, g, b);
    if (p.norm() >= 1.0) continue;
    return p;
  }
}

inline Vector3f Reflect(const Vector3f& v, const Vector3f& n) {
  return v - 2 * v.dot(n) * n;
}

}  // namespace Tracey