#include <math.h>

#include <iostream>

#include "geometry.hpp"

namespace Tracey {

/**
 * @brief a class depicting an oriented bounding box
 *
 * @param ray a ray of light
 * @param normal_out the normal of the ray intersecting the geometry
 * @return void
 */
class Box : public Geometry {
 public:
  /**
   * @brief constructor for a box object
   *
   * @param origin is the center of the box
   * @param u basis vector
   * @param v basis vector
   * @param w basis vector
   * @param hw half-width
   * @param hh half-height
   * @param hd half-depth
   */
  Box(Vector3d origin, Vector3d u, Vector3d v, Vector3d w, double hw, double hh,
      double hd)
      : origin_(origin),
        base_(std::array<Vector3d, 3>{u, v, w}),
        dimensions_(std::array<double, 3>{hw, hh, hd}) {}

  Box(Vector3d origin, std::array<Vector3d, 3> base, std::array<double, 3> dim)
      : origin_(origin), base_(base), dimensions_(dim) {}

  const Vector3d get_origin() const { return origin_; }
  const std::array<Vector3d, 3> get_base() const { return base_; }
  const Vector3d get_base(unsigned int i) const { return base_[i]; }
  const std::array<double, 3> get_dim() const { return dimensions_; }
  const double get_dim(unsigned int i) const { return dimensions_[i]; }
  bool intersect(const Ray& ray, double t_min, double t_max,
                 Hit_Record& rec) const;

 private:
  Vector3d origin_;
  std::array<Vector3d, 3> base_;
  std::array<double, 3> dimensions_;
};

bool Box::intersect(const Ray& ray, double t_min, double t_max,
                    Hit_Record& rec) const {
  double t_near = t_min;
  double t_far = t_max;

  for (unsigned int i = 0; i < base_.size(); i++) {
    Vector3d vec = base_[i];
    double dim = dimensions_[i];

    double r = vec.dot(origin_ - ray.get_origin());

    double denominator = vec.dot(ray.get_direction());
    if (fabs(denominator) < 1e-50) {
      double r1 = -r - dim;
      double r2 = -r + dim;

      if ((-r - dim > 0) || (-r + dim > 0)) {
        // ray misses the box
        return false;
      }
    }

    double t0 = (r + dim) / denominator;
    double t1 = (r - dim) / denominator;

    if (t0 > t1) {
      double temp = t0;
      t0 = t1;
      t1 = temp;
    }

    if (t0 > t_near) {
      t_near = t0;
    }

    if (t1 < t_far) {
      t_far = t1;
    }

    if (t_near > t_far) {
      return false;
    }

    if (t_far < 0) {
      return false;
    }
  }
  // ray hit the box
  if (t_near > 0) {
    rec.t = t_near;
  } else {
    rec.t = t_far;
  }
  rec.p = ray.at(rec.t);
  Vector3d normal = (rec.p - get_origin()).normalized();
  rec.set_normal(ray, normal);
  return true;
}

}  // namespace Tracey