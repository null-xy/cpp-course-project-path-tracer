#pragma once

#include <eigen3/Eigen/Dense>

using Eigen::Vector3d;

namespace Tracey {

class Ray {
 public:
  Ray() {}
  // Ray(Vector3d origin, Vector3d direction)
  //     : origin_(origin), direction_(direction) {}
  // Ray should be const
  Ray(const Vector3d& origin, const Vector3d& direction)
      : origin_(origin), direction_(direction) {}
  Vector3d get_origin() const { return origin_; }

  Vector3d get_direction() const { return direction_; }
  Vector3d at(float f) const { return origin_ + direction_ * f; }

  friend inline Vector3d RandomInUnitSphere();
  friend inline Vector3d Reflect(const Vector3d& v, const Vector3d& n);

 private:
  Vector3d origin_;
  Vector3d direction_;
};

Vector3d RandomInUnitSphere() {
  Vector3d point;
    while (true) {
      float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
      float g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
      float b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
      Vector3d p(r, g, b);
      if (p.norm() >= 1.0) continue;
      return p;
  }
}

inline Vector3d Reflect(const Vector3d& v, const Vector3d& n) {
  return v - 2 * v.dot(n) * n;
}

}  // namespace Tracey