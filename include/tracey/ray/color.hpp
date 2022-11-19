#ifndef COLOR_CLASS
#define COLOR_CLASS
#include "../geometry/geometry.hpp"
#include "../geometry/geometry_list.hpp"
#include "../material/material.hpp"
#include "ray.hpp"

namespace Tracey {
void wirte_color(std::ostream &out, Vector3d pixel_color,
                 int samples_per_pixel) {
  auto r = pixel_color.x();
  auto g = pixel_color.y();
  auto b = pixel_color.z();
  // Divide the color by the number of samples.
  auto scale = 1.0 / samples_per_pixel;
  r = sqrt(scale * r);
  g = sqrt(scale * g);
  b = sqrt(scale * b);

  // Write the translated [0,255] value of each color component.
  out << static_cast<int>(256 * clamp(r, 0.0, 0.999)) << ' '
      << static_cast<int>(256 * clamp(g, 0.0, 0.999)) << ' '
      << static_cast<int>(256 * clamp(b, 0.0, 0.999)) << '\n';
}

Vector3d RayColor(const Ray &r, const Geometry &scene, int depth) {
  Hit_Record rec;
  if (depth <= 0) {
    return Vector3d(0, 0, 0);
  }
  if (scene.intersect(r, 0.001, constants::infinity, rec)) {
    // return 0.5 * (rec.normal + Vector3d(1.0, 1.0, 1.0));
    Ray ray_scatter;
    Vector3d attenuation;
    if (rec.material_prt->Scatter(r, rec, attenuation, ray_scatter)) {
      // attenuation.x()*RayColor(ray_scatter, scene, depth - 1).x()
      return attenuation.cwiseProduct(RayColor(ray_scatter, scene, depth - 1));
    } else {
      return Vector3d(0, 0, 0);
    }
    // Vector3d target =
    //    rec.p + rec.normal + Tracey::random_in_unit_sphere().normalized();
    // return 0.5 * RayColor(Tracey::Ray(rec.p, target - rec.p), scene, depth -
    // 1);
  }
  Vector3d unit = r.get_direction().normalized();
  double t = 0.5 * (unit.y() + 1.0);
  return (1.0 - t) * Vector3d(1.0, 1.0, 1.0) + t * Vector3d(0.5, 0.7, 1.0);
}
} // namespace Tracey
#endif