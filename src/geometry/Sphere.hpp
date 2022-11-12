#ifndef PATH_TRACER_SPHERE
#define PATH_TRACER_SPHERE

#include <eigen3/Eigen/Dense>

#include "../ray/Ray.hpp"
#include "Geometry.hpp"

class Sphere : public Geometry {
 public:
  Sphere(Vector3f origin, float radius);
  bool Intersect(Ray& ray) const;
  float GetRadius() const;

 private:
  float radius_;
};

#endif