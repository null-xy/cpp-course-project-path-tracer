#ifndef MATERIAL_CLASS
#define MATERIAL_CLASS
#include "../constants.hpp"
#include "../geometry/Geometry.hpp"
#include "../ray/ray.hpp"

namespace Tracey {
class Material {
public:
  virtual bool Scatter(const Ray &ray, const Hit_Record &hit,
                       Vector3d &attenuation, Ray &ray_scatter) const = 0;
};

class Lambertian : public Material {
public:
  Lambertian(const Vector3d &albedo) : albedo_(albedo) {}
  bool Scatter(const Ray &ray_input, const Hit_Record &rec,
                       Vector3d &attenuation, Ray &ray_scatter) const override {
    Vector3d ray_direction = rec.normal + random_in_unit_sphere().normalized();
    // fabs(ray_direction.x()) || ray_direction.x().abs()
    if (fabs(ray_direction.x()) < constants::near_zero &&
        fabs(ray_direction.y()) < constants::near_zero &&
        fabs(ray_direction.z()) < constants::near_zero) {
      ray_direction = rec.normal;
    }

    ray_scatter = Ray(rec.p, ray_direction);
    attenuation = albedo_;
    return true;
  }

private:
  Vector3d albedo_;
};

class Metal : public Material {
public:
  Metal(const Vector3d &albedo, double fuzz) : albedo_(albedo), fuzz_(fuzz <1 ? fuzz :1) {}

  bool Scatter(const Ray &ray_input, const Hit_Record &rec,
               Vector3d &attenuation, Ray &ray_scatter) const override {
    Vector3d ray_reflect =
        reflect(ray_input.get_direction().normalized(), rec.normal);
    ray_scatter = Ray(rec.p, ray_reflect + random_in_unit_sphere()*fuzz_);
    attenuation = albedo_;
    return (ray_scatter.get_direction().dot(rec.normal) > 0);
  }

private:
  Vector3d albedo_;
  //frosted material
  double fuzz_;
};

} // namespace Tracey

#endif