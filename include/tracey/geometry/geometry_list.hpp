#pragma once

#include <eigen3/Eigen/Dense>
#include <memory>
#include <vector>

#include "geometry.hpp"

using Eigen::Vector3d;

namespace Tracey {

class GeometryList : public Geometry {
 public:
  /**
   * @brief Construct a new Camera object
   */
  GeometryList() {}

  /**
   * @brief Construct a new Camera object
   * @param object an object to be added into the list
   */
  GeometryList(std::shared_ptr<Geometry> object) { add(object); }

  /**
   * @brief clears the list
   */
  void clear() { objects_.clear(); }

  /**
   * @brief adds a geometry object to the list
   * @param a shared pointer pointing to a geometry object
   */
  void add(std::shared_ptr<Geometry> object) { objects_.push_back(object); }

  virtual bool intersect(const Ray& ray, double t_min, double t_max,
                         Hit_Record& rec) const override;

 private:
  std::vector<std::shared_ptr<Geometry>> objects_;
};

bool GeometryList::intersect(const Ray& ray, double t_min, double t_max,
                             Hit_Record& rec) const {
  Hit_Record temp;
  bool objectHit = false;
  double closest = t_max;

  for (const auto& object : objects_) {
    if (object->intersect(ray, t_min, closest, temp)) {
      objectHit = true;
      closest = temp.t;
      rec = temp;
    }
  }

  return objectHit;
}
}  // namespace Tracey