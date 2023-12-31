#ifndef COLOR_CLASS
#define COLOR_CLASS
#include <Eigen/Dense>

#include "../geometry/geometry.hpp"
#include "../geometry/geometry_list.hpp"
#include "../material/material.hpp"
#include "ray.hpp"

using Eigen::Vector3d;

namespace Tracey {
void WirteColor(std::ostream &out, Vector3d pixel_color,
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
  out << static_cast<int>(256 * Clamp(r, 0.0, 0.999)) << ' '
      << static_cast<int>(256 * Clamp(g, 0.0, 0.999)) << ' '
      << static_cast<int>(256 * Clamp(b, 0.0, 0.999)) << '\n';
}
  /**
   * @brief Rendering the color of the Ray
   * 
   * @param r direction for incoming ray
   * @param background default background color vector, normally 0,0,0
   * @param scene geometry list
   * @param dept ray iteration limitation
   * @return a ray vector
   */

Vector3d RayColor(const Ray &r, const Vector3d& background, const Geometry &scene, int depth) {
  Hit_Record rec;
  if (depth <= 0) {
    return Vector3d(0, 0, 0);
  }
  if (scene.intersect(r, 0.001, constants::infinity, rec)) {
    Ray ray_scatter;
    Vector3d attenuation;
    Vector3d emitted_ray=rec.material_prt->Emitted(rec.u, rec.v, rec.p);

    if (rec.material_prt->Scatter(r, rec, attenuation, ray_scatter)) {
      return emitted_ray + attenuation.cwiseProduct(RayColor(ray_scatter,background, scene, depth - 1));
    } else {
      return emitted_ray;
    }
  }else{
    return background;
  }
  Vector3d unit = r.get_direction().normalized();
  double t = 0.5 * (unit.y() + 1.0);
  return (1.0 - t) * Vector3d(1.0, 1.0, 1.0) + t * Vector3d(0.5, 0.7, 1.0);
}
} // namespace Tracey
#endif
