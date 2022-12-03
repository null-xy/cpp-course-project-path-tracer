#pragma once

#include <Eigen/Dense>
#include <iostream>
#include <memory>

#include "geometry.hpp"

using Eigen::Vector3d;

namespace Tracey {

// for now, it is just a square
class Plane : public Geometry {
 public:
  Plane(const Vector3d& origin, const Vector3d& normal, double radius, std::shared_ptr<Material> material) {
    origin_ = origin;
    normal_ = normal.normalized();
    radius_ = radius;
    material_ = material;
  }

  Vector3d get_origin() const { return origin_; }

  Vector3d get_normal() const { return normal_; }

  double get_radius() const { return radius_; }

  bool intersect(const Ray& ray, double t_min, double t_max,
                 Hit_Record& rec) const {
    if (intersect_plane(ray, t_min, t_max, rec)) {
      Vector3d p = rec.p;
      Vector3d v = p - origin_;
      float d2 = v.dot(v);
      return sqrt(d2) <= radius_;
    }
    return false;
  }

 private:
  Vector3d origin_;
  Vector3d normal_;
  double radius_;
  std::shared_ptr<Material> material_;

  bool intersect_plane(const Ray& ray, double t_min, double t_max,
                       Hit_Record& rec) const;
};

bool Plane::intersect_plane(const Ray& ray, double t_min, double t_max,
                            Hit_Record& rec) const {
  double denominator = ray.get_direction().dot(normal_);
  // check if denominator is too close to zero
  if (denominator > 1e-6) {
    double numerator = normal_.dot(origin_ - ray.get_origin());
    double t = numerator / denominator;

    if (t > t_min && t < t_max) {
      rec.t = t;
      rec.p = ray.at(rec.t);
      Vector3d normal = (rec.p - get_origin()) / get_radius();
      rec.set_normal(ray, normal);
      rec.material_prt = material_;
      return true;
    }
  }
  return false;
}

}  // namespace Tracey