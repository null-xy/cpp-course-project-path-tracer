#ifndef PATH_TRACER_LIST
#define PATH_TRACER_LIST

#include <eigen3/Eigen/Dense>
#include <memory>
#include <vector>

#include "Geometry.hpp"

using Eigen::Vector3f;

class GeometryList : public Geometry {
 public:
  GeometryList();
  GeometryList(std::shared_ptr<Geometry> object);
  void Clear();
  void Add(std::shared_ptr<Geometry> object);
  std::vector<std::shared_ptr<Geometry>> GetObjects() const;
  bool Intersect(Ray& ray, float tMin, float tMax, Hit_Record& rec) const;

 private:
  std::vector<std::shared_ptr<Geometry>> objects_;
};

#endif