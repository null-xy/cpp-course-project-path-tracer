#ifndef PATH_TRACER_GEOMETRY
#define PATH_TRACER_GEOMETRY

#include <eigen3/Eigen/Dense>

#include "../ray/Ray.hpp"

using Eigen::Vector3f;

// wip
class Geometry {
 public:
  Geometry(Vector3f origin) : origin_(origin) {}
  Vector3f GetOrigin() const { return origin_; }
  virtual bool Intersect(Ray& ray) const = 0;

 private:
  Vector3f origin_;
};

#endif