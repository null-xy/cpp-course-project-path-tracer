#ifndef PATH_TRACER_GEOMETRY
#define PATH_TRACER_GEOMETRY

#include <eigen3/Eigen/Dense>

#include "../ray/Ray.hpp"

using Eigen::Vector3f;

struct Hit_Record {
  Vector3f p;
  Vector3f normal;
  float t;
  bool pointsOut;

  inline void SetNormal(const Ray& ray, const Vector3f normalOut) {
    //check whether the normal points towards the ray
    pointsOut = ray.GetDirection().dot(normalOut) > 0;
    //set the normal pointing towards the ray
    normal = pointsOut ? normalOut : - normalOut;
  }
};

// wip
class Geometry {
 public:
  virtual bool Intersect(Ray& ray, float tMin, float tMax,
                          Hit_Record& rec) const = 0;
};

#endif