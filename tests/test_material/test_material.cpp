#include <fstream>
#include <iostream>

#include "../../include/tracey/ray/hittable_list.hpp"
#include "../../include/tracey/ray/sphere.hpp"
#include "../../include/tracey/tracey.hpp"

//, int depth
const double infinity = std::numeric_limits<double>::infinity();

Vector3d RayColor(const Tracey::Ray& r, const Tracey::Geometry& scene,
                  int depth) {
  Tracey::Hit_Record rec;
  if (depth <= 0) {
    return Vector3d(0, 0, 0);
  }
  if (scene.intersect(r, 0.001, infinity, rec)) {
    // return 0.5 * (rec.normal + Vector3d(1.0, 1.0, 1.0));
    Vector3d target =
        rec.p + rec.normal + Tracey::RandomInUnitSphere().normalized();
    return 0.5 * RayColor(Tracey::Ray(rec.p, target - rec.p), scene, depth - 1);
  }
  Vector3d unit = r.get_direction().normalized();
  double t = 0.5 * (unit.y() + 1.0);
  return (1.0 - t) * Vector3d(1.0, 1.0, 1.0) + t * Vector3d(0.5, 0.7, 1.0);
}

int main() {
  std::ofstream out("out.ppm");
  const int samples_per_pixel = 100;
  const int max_depth = 5;

  // image
  double aspectRatio = 16.0 / 9.0;
  int w = 400;
  int h = static_cast<int>(w / aspectRatio);

  // scene
  Tracey::GeometryList scene;
  scene.add(std::make_shared<Tracey::Sphere>(Vector3d(0.0, 0.0, -1.0), 0.5));
  scene.add(std::make_shared<Tracey::Sphere>(Vector3d(0.0, -100.5, -1.0), 100));

  Vector3d origin(0.0, 0.0, 0.0);
  Tracey::Camera cam(w, h, origin, 90.0);

  out << "P3\n" << w << ' ' << h << "\n255\n";

  for (int j = 0; j < h; j++) {
    std::cerr << "\rScanlines remaining: " << h - j << ' ' << std::flush;
    for (int i = 0; i < w; ++i) {
      Vector3d pixel_color(0, 0, 0);
      for (int s = 0; s < samples_per_pixel; ++s) {
        Tracey::Ray r = cam.get_direction(i, j);
        pixel_color += RayColor(r, scene, max_depth);
      }
      wirte_color(out, pixel_color, samples_per_pixel);
    }
  }
  std::cerr << "\nDone.\n";
}