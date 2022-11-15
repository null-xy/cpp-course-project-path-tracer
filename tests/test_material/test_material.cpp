#include <fstream>
#include <iostream>

#include "../../include/tracey/tracey.hpp"

const double infinity = std::numeric_limits<double>::infinity();

//, int depth
Vector3f RayColor(const Tracey::Ray& r, const Tracey::Geometry& scene,
                  int depth) {
  Tracey::Hit_Record rec;

  if (depth <= 0) {
    return Vector3f(0, 0, 0);
  }

  if (scene.intersect(r, 0, infinity, rec)) {
    // std::cout << depth << std::endl;
    // return 0.5 * (rec.normal + Vector3f(1.0, 1.0, 1.0));
    Vector3f target = rec.p + rec.normal + Tracey::RandomInUnitSphere();
    return 0.5 * RayColor(Tracey::Ray(rec.p, target - rec.p), scene, depth - 1);
  }
  Vector3f unit = r.get_direction().normalized();
  float t = 0.5 * (unit.y() + 1.0);
  return (1.0 - t) * Vector3f(1.0, 1.0, 1.0) + t * Vector3f(0.5, 0.7, 1.0);
}

int main() {
  std::ofstream out("out.ppm");
  // Image
  const auto aspect_ratio = 16.0 / 9.0;
  const int image_width = 400;
  const int image_height = static_cast<int>(image_width / aspect_ratio);
  const int samples_per_pixel = 100;
  const int max_depth = 50;

  Tracey::GeometryList scene;
  scene.add(std::make_shared<Tracey::Sphere>(Vector3f(0.0, 0.0, -1), 0.5));
  scene.add(std::make_shared<Tracey::Sphere>(Vector3f(0.0, -100.5, -1), 100));

  out << "P3\n" << image_width << ' ' << image_height << "\n255\n";

  for (int j = image_height - 1; j >= 0; --j) {
    std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
    for (int i = 0; i < image_width; ++i) {
      Vector3f pixel_color(0, 0, 0);
      for (int s = 0; s < samples_per_pixel; ++s) {
        float u = (i + (rand() / (RAND_MAX + 1.0))) / (image_width - 1);
        float v = (j + (rand() / (RAND_MAX + 1.0))) / (image_height - 1);
        Vector3f origin(0, 0, 0);
        float viewport_width = 2.0;
        float viewport_height = 1.0;
        Vector3f horizontal(viewport_width, 0.0, 0.0);
        Vector3f vertical(0.0, viewport_height, 0.0);
        Vector3f lower_left_corner =
            origin - (horizontal / 2) - (vertical / 2) - Vector3f(0, 0, 1.0);
        Tracey::Ray r(
            Vector3f(0.0, 0.0, 0.0),
            lower_left_corner + u * horizontal + v * vertical - origin);
        pixel_color = RayColor(r, scene, max_depth);
      }
      wirte_color(out, pixel_color, samples_per_pixel);
    }
  }
  std::cerr << "\nDone.\n";
}