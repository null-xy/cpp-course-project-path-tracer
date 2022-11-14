#include "GeometryList.hpp"

GeometryList::GeometryList() {}

GeometryList::GeometryList(std::shared_ptr<Geometry> object) { Add(object); }

void GeometryList::Clear() { objects_.clear(); }

void GeometryList::Add(std::shared_ptr<Geometry> object) {
  objects_.push_back(object);
}

std::vector<std::shared_ptr<Geometry>> GeometryList::GetObjects() const {
  return objects_;
}

bool GeometryList::Intersect(Ray& ray, float tMin, float tMax,
                             Hit_Record& rec) const {
  Hit_Record temp;
  bool objectHit = false;
  float closest = tMax;

  for (auto object : objects_) {
    if (object->Intersect(ray, tMin, tMax, temp)) {
      objectHit = true;
      closest = temp.t;
      rec = temp;
    }
  }

  return objectHit;
}