#pragma once

#include <Eigen/Dense>
#include <cmath>
#include <iostream>

#include "../ray/ray.hpp"
#include "geometry.hpp"

namespace Tracey {

class Sphere : public Geometry {
public:
  /**
   * @brief Construct a new Sphere object
   *
   * @param origin is the center of the sphere in xyz-coordinates
   * @param radius is the radius of the sphere
   */
  Sphere(Vector3d origin, double radius, shared_ptr<Material> material)
      : origin_(origin), radius_(radius), material_(material) {}

  bool intersect(const Ray &ray, double t_min, double t_max,
                 Hit_Record &rec) const;

  Vector3d get_origin() const { return origin_; }

  double get_radius() const { return radius_; }

private:
  Vector3d origin_;
  double radius_;
  shared_ptr<Material> material_;
};

bool Sphere::intersect(const Ray &ray, double tMin, double tMax,
                       Hit_Record &rec) const {
  Vector3d oc = ray.get_origin() - get_origin();
  double a = ray.get_direction().squaredNorm();
  double bDivBy2 = oc.dot(ray.get_direction());
  double c = oc.squaredNorm() - get_radius() * get_radius();

  double discriminant = bDivBy2 * bDivBy2 - a * c;

  if (discriminant < 0) return false; // ray does not hit sphere

  double sqrtD = sqrt(discriminant);

  // calculate the roots of the quadratic equation and check if the root is in
  // the interval [tmin, tmax]
  double root = (-bDivBy2 - sqrtD) / a;
  if (root < tMin || root > tMax) {
    root = (-bDivBy2 + sqrtD) / a;
    if (root < tMin || root > tMax) {
      return false;
    }
  }

  rec.t = root;
  rec.p = ray.at(rec.t);
  Vector3d normal = (rec.p - get_origin()) / get_radius();
  rec.set_normal(ray, normal);
  rec.material_prt = material_;
  return true;
}
} // namespace Tracey
