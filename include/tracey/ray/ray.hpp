#pragma once

#include <eigen3/Eigen/Dense>

using Eigen::Vector3f;

namespace Tracey {

class Ray {
 public:
  Ray() {}
  Ray(Vector3f origin, Vector3f direction)
      : origin_(origin), direction_(direction) {}

  Vector3f get_origin() const { return origin_; }

  Vector3f get_direction() const { return direction_; }
  Vector3f at(float f) const { return origin_ + direction_ * f; }

 private:
  Vector3f origin_;
  Vector3f direction_;
};

}