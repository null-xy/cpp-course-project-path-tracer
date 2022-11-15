#pragma once

#include <eigen3/Eigen/Dense>

#include "../ray/ray.hpp"

using Eigen::Vector3f;

namespace Tracey {

struct Hit_Record {
  Vector3f p;
  Vector3f normal;
  float t;
  bool pointsOut;

  inline void set_normal(const Ray& ray, const Vector3f& normalOut) {
    // check whether the normal points towards the ray
    pointsOut = ray.get_direction().dot(normalOut) < 0;
    // set the normal pointing towards the ray
    normal = pointsOut ? normalOut : -normalOut;
  }
};

// wip
class Geometry {
 public:

   virtual bool intersect(const Ray& ray, float tMin, float tMax,
                          Hit_Record& rec) const = 0;
  //virtual bool intersect(Ray& ray, float tMin, float tMax,
  //                       Hit_Record& rec) const = 0;

};

}  // namespace Tracey