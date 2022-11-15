#pragma once

#include <eigen3/Eigen/Dense>

using Eigen::Vector3f;

namespace Tracey {

class Ray {
 public:
  Ray() {}
  //Ray(Vector3f origin, Vector3f direction)
  //    : origin_(origin), direction_(direction) {}
  //Ray should be const
  Ray(const Vector3f& origin, const Vector3f& direction)
      : origin_(origin),direction_(direction){}
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
<<<<<<< HEAD
    Vector3f point;
=======
    Vector3f p;
    /*
>>>>>>> 5da39af0524b969c646ee7c5731281e92d2d9a8f
    do{
        point=Vector3f::Random(-1,1);
    }while (point.norm() >= 1);
	return point;
<<<<<<< HEAD
=======
  while (true) {
        p = Vector3f::Random(-1,1);
        if (p.squaredNorm() >= 1.0) continue;
        return p;
    }*/

    while (true) {
      float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
      float g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
      float b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
      Vector3f p(r, g, b);
      if (p.norm() >= 1.0) continue;
      return p;
  }
>>>>>>> 5da39af0524b969c646ee7c5731281e92d2d9a8f
}

inline Vector3f Reflect(const Vector3f& v, const Vector3f& n){
	return v - 2 * v.dot(n) * n;
}

}