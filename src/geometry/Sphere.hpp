#ifndef PATH_TRACER_SPHERE
#define PATH_TRACER_SPHERE

#include <eigen3/Eigen/Dense>

#include "../ray/Ray.hpp"
#include "Geometry.hpp"

class Sphere : public Geometry {
 public:
  Sphere(Vector3f origin, float radius);
  bool Intersect(Ray& ray, float tMin, float tMax, Hit_Record& rec) const;
  Vector3f GetOrigin() const;
  float GetRadius() const;

 private:
  Vector3f origin_;
  float radius_;
};

#endif