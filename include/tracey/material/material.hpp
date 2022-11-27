#ifndef MATERIAL_CLASS
#define MATERIAL_CLASS
#include "../constants.hpp"
#include "../geometry/geometry.hpp"
#include "../ray/ray.hpp"
#include "texture.hpp"

namespace Tracey {
class Material {
public:
  virtual bool Scatter(const Ray &ray, const Hit_Record &hit,
                       Vector3d &attenuation, Ray &scattered_ray) const = 0;
  virtual Vector3d Emitted(double u, double v, const Vector3d &point) const {
    return Vector3d(0, 0, 0);
  }
};
/**
 * @brief Construct a new Lambertian Material object
 *
 * @param albedo is RGB color of the Material
 */
class Lambertian : public Material {
public:
  Lambertian(const Vector3d &albedo)
      : albedo_(std::make_shared<SolidTexture>(albedo)) {}
  Lambertian(std::shared_ptr<Texture> albedo) : albedo_(albedo) {}
  bool Scatter(const Ray &ray_input, const Hit_Record &rec,
               Vector3d &attenuation, Ray &scattered_ray) const override {
    Vector3d ray_direction = rec.normal + random_in_unit_sphere().normalized();
    if (fabs(ray_direction.x()) < constants::near_zero &&
        fabs(ray_direction.y()) < constants::near_zero &&
        fabs(ray_direction.z()) < constants::near_zero) {
      ray_direction = rec.normal;
    }

    scattered_ray = Ray(rec.p, ray_direction);
    attenuation = albedo_->Color(rec.u, rec.v, rec.p);
    // attenuation = albedo_;
    return true;
  }

private:
  std::shared_ptr<Texture> albedo_;
  // Vector3d albedo_;
};

/**
 * @brief Construct a new Metal Material object
 *
 * @param albedo is RGB color of the Material
 * @param fuzz to make frosted metal, fuzz=0: smooth
 */
class Metal : public Material {
public:
  Metal(const Vector3d &albedo, double fuzz)
      : albedo_(albedo), fuzz_(fuzz < 1 ? fuzz : 1) {}

  bool Scatter(const Ray &ray_input, const Hit_Record &rec,
               Vector3d &attenuation, Ray &scattered_ray) const override {
    Vector3d reflected_ray =
        Reflect(ray_input.get_direction().normalized(), rec.normal);
    scattered_ray = Ray(rec.p, reflected_ray + random_in_unit_sphere() * fuzz_);
    attenuation = albedo_;
    return (scattered_ray.get_direction().dot(rec.normal) > 0);
  }

private:
  Vector3d albedo_;
  // frosted material
  double fuzz_;
};

/**
 * @brief Construct a new Glass Material object
 *
 * @param albedo is RGB color of the Material
 * @param fuzz to make frosted metal, fuzz=0: smooth
 * @param refractive_index refractive index (typically air = 1.0, glass
 * = 1.3–1.7, diamond = 2.4)
 */
class Glass : public Material {
public:
  Glass(const Vector3d &albedo, double fuzz, double refractive_index)
      : albedo_(albedo), fuzz_(fuzz < 1 ? fuzz : 1),
        refractive_index_(refractive_index) {}
  bool Scatter(const Ray &ray_in, const Hit_Record &rec, Vector3d &attenuation,
               Ray &scattered_ray) const override {
    attenuation = albedo_;
    // attenuation = Vector3d(1.0, 1.0, 1.0);
    // 1.0 here is refractive index for air
    double n1_over_n2 =
        rec.pointsOut ? (1.0 / refractive_index_) : refractive_index_;

    Vector3d unit_ray_in = ray_in.get_direction().normalized();
    double cos_theta = fmin((-unit_ray_in).dot(rec.normal), 1.0);
    double sin_theta = sqrt(1.0 - cos_theta * cos_theta);

    bool cannot_refract = n1_over_n2 * sin_theta > 1.0;
    Vector3d ray_out;
    if (cannot_refract || Schlick(cos_theta, n1_over_n2) > RandomDouble()) {
      ray_out = Reflect(unit_ray_in, rec.normal);
    } else {
      ray_out = Refract(unit_ray_in, rec.normal, n1_over_n2);
    }
    scattered_ray = Ray(rec.p, ray_out + random_in_unit_sphere() * fuzz_);

    return true;
  }

private:
  /**
   * @brief Schlick's approximation for Fresnel Formula
   *
   * @param cos cos(theta)
   * @param n1_over_n2 refractive index from n1 / refractive index from n2
   * @return a radio of reflect and refract
   */
  static double Schlick(double cos, double n1_over_n2) {
    double r0 = (1 - n1_over_n2) / (1 + n1_over_n2);
    r0 = r0 * r0;
    return r0 + (1 - r0) * pow((1 - cos), 5);
  }

  Vector3d albedo_;
  double fuzz_;
  double refractive_index_;
};

} // namespace Tracey

#endif