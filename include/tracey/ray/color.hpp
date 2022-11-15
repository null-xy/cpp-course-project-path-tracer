#ifndef COLOR_CLASS
#define COLOR_CLASS
#include "ray.hpp"

void wirte_color(std::ostream &out, Vector3f pixel_color,
                 int samples_per_pixel) {
  auto r = pixel_color.x();
  auto g = pixel_color.y();
  auto b = pixel_color.z();
  // Divide the color by the number of samples.
  auto scale = 1.0 / samples_per_pixel;
  r *= scale;
  g *= scale;
  b *= scale;

  // Write the translated [0,255] value of each color component.
  out << static_cast<int>(256 * Tracey::clamp(r, 0.0, 0.999)) << ' '
      << static_cast<int>(256 * Tracey::clamp(g, 0.0, 0.999)) << ' '
      << static_cast<int>(256 * Tracey::clamp(b, 0.0, 0.999)) << '\n';
}

#endif