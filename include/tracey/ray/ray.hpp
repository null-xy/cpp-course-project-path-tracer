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

  friend inline Vector3f RandomInUnitSphere();
  friend inline Vector3f Reflect(const Vector3f& v, const Vector3f& n);

 private:
  Vector3f origin_;
  Vector3f direction_;
};

Vector3f RandomInUnitSphere(){
    Vector3f point;
    do{
        point=Vector3f::Random(-1,1);
    }while (point.norm() >= 1);
	return point;
}

inline Vector3f Reflect(const Vector3f& v, const Vector3f& n){
	return v - 2 * v.dot(n) * n;
}

}