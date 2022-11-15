#pragma once

#include <cmath>
#include <eigen3/Eigen/Dense>
#include <iostream>

#include "../ray/ray.hpp"
#include "geometry.hpp"

namespace Tracey {

class Sphere : public Geometry {
 public:
  Sphere(){}
  Sphere(Vector3f origin, float radius) : origin_(origin), radius_(radius) {}

  virtual bool intersect(const Ray& ray, float tMin, float tMax, Hit_Record& rec) const override;


  Vector3f get_origin() const { return origin_; }

  float get_radius() const { return radius_; }

 private:
  Vector3f origin_;
  float radius_;
};

  bool Sphere::intersect(const Ray& ray, float tMin, float tMax, Hit_Record& rec) const {
    Vector3f oc = ray.get_origin() - get_origin();
    float a = ray.get_direction().squaredNorm();
    float bDivBy2 = oc.dot(ray.get_direction());
    float c = oc.squaredNorm() - get_radius() * get_radius();

    float discriminant = bDivBy2 * bDivBy2 - a * c;

    if (discriminant < 0) return false;  // ray does not hit sphere

    float sqrtD = sqrt(discriminant);

    // calculate the roots of the quadratic equation and check if the root is in
    // the interval [tmin, tmax]
    float root = (-bDivBy2 - sqrtD) / a;
    if (root < tMin || root > tMax) {
      root = (-bDivBy2 + sqrtD) / a;
      if (root < tMin || root > tMax) {
        return false;
      }
    }

    rec.t = root;
    rec.p = ray.at(rec.t);
    Vector3f normal = (rec.p - get_origin()) / get_radius();
    rec.set_normal(ray, normal);
    return true;
    //    Vector3f outward_normal = (rec.point - center) / radius;
    //rec.set_face_normal(r, outward_normal);
  }
}  // namespace Tracey