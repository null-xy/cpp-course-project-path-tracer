#pragma once

#include <eigen3/Eigen/Dense>

#include "../ray/ray.hpp"

using Eigen::Vector3d;

namespace Tracey {

struct Hit_Record {
  Vector3d p;
  Vector3d normal;
  double t;
  bool pointsOut;

  inline void set_normal(const Ray& ray, const Vector3d& normalOut) {
    // check whether the normal points towards the ray
    pointsOut = ray.get_direction().dot(normalOut) < 0;
    // set the normal pointing towards the ray
    normal = pointsOut ? normalOut : -normalOut;
  }
};

// wip
class Geometry {
 public:

   virtual bool intersect(const Ray& ray, double tMin, double tMax,
                          Hit_Record& rec) const = 0;

};

}  // namespace Tracey