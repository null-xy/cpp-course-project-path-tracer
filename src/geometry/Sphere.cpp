#include "Sphere.hpp"

#include <iostream>

Sphere::Sphere(Vector3f origin, float radius)
    : Geometry(origin), radius_(radius) {}

bool Sphere::Intersect(Ray& ray) const {
  Vector3f oc = ray.GetOrigin() - GetOrigin();
  float a = ray.GetDirection().dot(ray.GetDirection());
  float b = 2.0 * oc.dot(ray.GetDirection());
  float c = oc.dot(oc) - GetRadius() * GetRadius();

  float discriminant = b * b - 4 * a * c;

  return (discriminant > 0);
}

float Sphere::GetRadius() const { return radius_; }