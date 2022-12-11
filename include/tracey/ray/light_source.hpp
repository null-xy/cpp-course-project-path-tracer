#ifndef LIGHT_SOURCE_CLASS
#define LIGHT_SOURCE_CLASS
#include "../material/material.hpp"
#include "../material/texture.hpp"

namespace Tracey {

class LightSource : public Material {
 public:
  LightSource(shared_ptr<Texture> a) : emitted_ray_(a) {}
  LightSource(Vector3d c) : emitted_ray_(std::make_shared<SolidTexture>(c)) {}

  bool Scatter(const Ray &ray, const Hit_Record &hit, Vector3d &attenuation,
               Ray &scattered_ray) const {
    (void)ray;
    (void)hit;
    (void)attenuation;
    (void)scattered_ray;
    return false;
  }

  Vector3d Emitted(double u, double v, const Vector3d &point) const {
    return emitted_ray_->Color(u, v, point);
  }

 private:
  shared_ptr<Texture> emitted_ray_;
};

}  // namespace Tracey
#endif