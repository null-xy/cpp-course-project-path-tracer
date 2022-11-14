#include "Sphere.hpp"

#include <cmath>
#include <iostream>

#include "Geometry.hpp"

Sphere::Sphere(Vector3f origin, float radius)
    : origin_(origin), radius_(radius) {}

bool Sphere::Intersect(Ray& ray, float tMin, float tMax,
                       Hit_Record& rec) const {
  Vector3f oc = ray.GetOrigin() - GetOrigin();
  float a = ray.GetDirection().dot(ray.GetDirection());
  float bDivBy2 = oc.dot(ray.GetDirection());
  float c = oc.dot(oc) - GetRadius() * GetRadius();

  float discriminant = bDivBy2 * bDivBy2 - a * c;

  if (discriminant < 0) return false;  // ray does not hit sphere

  float sqrtD = sqrt(discriminant);

  // calculate the roots of the quadratic equation and check if the root is in the interval [tmin, tmax]
  float root = (-bDivBy2 - sqrtD) / a;
  if (root < tMin || root > tMax) {
    root = (-bDivBy2 + sqrtD) / a;
    if (root < tMin || root > tMax) {
      return false;
    }
  }

  rec.t = root;
  rec.p = ray.At(rec.t);
  Vector3f normal = (rec.p - GetOrigin()) / GetRadius();
  rec.SetNormal(ray, normal);

  return true;
}

Vector3f Sphere::GetOrigin() const { return origin_; }

float Sphere::GetRadius() const { return radius_; }