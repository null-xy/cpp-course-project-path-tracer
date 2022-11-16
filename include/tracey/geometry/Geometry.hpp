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

  /**
   * @brief calculates the normal of the ray intersecting a geometry and sets it
   * pointing outward of the geometry
   *
   * @param ray a ray of light
   * @param normal_out the normal of the ray intersecting the geometry
   * @return void
   */
  inline void set_normal(const Ray& ray, const Vector3d& normal_out) {
    // check whether the normal points towards the ray
    pointsOut = ray.get_direction().dot(normal_out) < 0;
    // set the normal pointing towards the ray
    normal = pointsOut ? normal_out : -normal_out;
  }
};

// wip
class Geometry {
 public:
  /**
   * @brief returns a truth value indicating if a ray of light hits the sphere
   *
   * @param ray a ray of light
   * @param t_min is
   * @param t_max
   * @param rec is a struct that holds information about the ray intersecting a
   * geometry
   * @return true if ray hits the geometry, else false
   */
  virtual bool intersect(const Ray& ray, double t_min, double t_max,
                         Hit_Record& rec) const = 0;
};

}  // namespace Tracey