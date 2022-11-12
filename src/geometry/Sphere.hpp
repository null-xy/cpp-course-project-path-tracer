#ifndef PATH_TRACER_SPHERE
#define PATH_TRACER_SPHERE

#include <eigen3/Eigen/Dense>

#include "Geometry.hpp"
#include "../ray/Ray.hpp"

class Sphere {
 public:
  Sphere();
  Sphere(Vector3f origin, float radius);
  bool Intersect(Ray& ray) const;
  Vector3f GetOrigin() const;
  float GetRadius() const;

 private:
  Vector3f origin_;
  float radius_;
};

#endif