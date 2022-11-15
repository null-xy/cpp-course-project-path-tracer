#pragma once

#include <eigen3/Eigen/Dense>
#include <memory>
#include <vector>

#include "geometry.hpp"

using Eigen::Vector3f;
using std::make_shared;

namespace Tracey {

class GeometryList : public Geometry {
 public:
  GeometryList() {}

  GeometryList(std::shared_ptr<Geometry> object) { add(object); }

  void clear() { objects_.clear(); }

  void add(std::shared_ptr<Geometry> object) { objects_.push_back(object); }
/*
  std::vector<std::shared_ptr<Geometry>> get_objects() const {
    return objects_;
  }
*/
  virtual bool intersect(const Ray& ray, float tMin, float tMax, Hit_Record& rec) const override;

<<<<<<< HEAD
 //private:
  std::vector<std::shared_ptr<Geometry>> objects_;
};
  bool GeometryList::intersect(const Ray& ray, float tMin, float tMax, Hit_Record& rec) const {
  //bool intersect(Ray& ray, float tMin, float tMax, Hit_Record& rec) const {
=======
  bool intersect(const Ray& ray, float tMin, float tMax,
                      Hit_Record& rec) const {
>>>>>>> minor bugfix and set up the test correctly
    Hit_Record temp;
    bool objectHit = false;
    float closest = tMax;

    for (const auto& object : objects_) {
      if (object->intersect(ray, tMin, tMax, temp)) {
        objectHit = true;
        closest = temp.t;
        rec = temp;
      }
    }

    return objectHit;
  }
}  // namespace Tracey