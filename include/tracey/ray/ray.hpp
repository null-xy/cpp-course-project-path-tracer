#pragma once

#include <eigen3/Eigen/Dense>

using Eigen::Vector3d;

namespace Tracey {

class Ray {
 public:
  Ray() {}
  Ray(const Vector3d& origin, const Vector3d& direction)
      : origin_(origin), direction_(direction) {}
  Vector3d get_origin() const { return origin_; }

  Vector3d get_direction() const { return direction_; }
  Vector3d at(double f) const { return origin_ + direction_ * f; }

  friend inline Vector3d RandomInUnitSphere();
  friend inline Vector3d Reflect(const Vector3d& v, const Vector3d& n);

 private:
  Vector3d origin_;
  Vector3d direction_;
};

Vector3d RandomInUnitSphere() {
  Vector3d p;

  while (true) {
    double r = static_cast<double>(rand()) / static_cast<double>(RAND_MAX);
    double g = static_cast<double>(rand()) / static_cast<double>(RAND_MAX);
    double b = static_cast<double>(rand()) / static_cast<double>(RAND_MAX);
    Vector3d p(r, g, b);
    if (p.norm() >= 1.0) continue;
    return p;
  }
}

inline Vector3d Reflect(const Vector3d& v, const Vector3d& n) {
  return v - 2 * v.dot(n) * n;
}

}  // namespace Tracey