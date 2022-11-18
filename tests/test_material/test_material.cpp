#include <fstream>
#include <iostream>

#include "../../include/tracey/tracey.hpp"



int main() {
  std::ofstream out("out.ppm");
  const int samples_per_pixel = 100;
  const int max_depth = 50;

  // image
  double aspectRatio = 16.0 / 9.0;
  int w = 400;
  int h = static_cast<int>(w / aspectRatio);

  //material
  auto material_ground=std::make_shared<Tracey::Lambertian>(Vector3d(0.8,0.8,0.0));
  auto material_sphere_0=std::make_shared<Tracey::Metal>(Vector3d(0.8,0.8,0.8),0.3);
  auto material_sphere_1=std::make_shared<Tracey::Lambertian>(Vector3d(0.7,0.3,0.3));
  // scene
  Tracey::GeometryList scene;
  scene.add(std::make_shared<Tracey::Sphere>(Vector3d(0.0, 0.0, -1.0), 0.5, material_sphere_0));
  scene.add(std::make_shared<Tracey::Sphere>(Vector3d(-1.0, 0.0, -1.0), 0.5, material_sphere_1));
  scene.add(std::make_shared<Tracey::Sphere>(Vector3d(0.0, -100.5, -1.0), 100, material_ground));

  Vector3d origin(0.0, 0.0, 0.0);
  Tracey::Camera cam(w, h, origin, 90.0);

  out << "P3\n" << w << ' ' << h << "\n255\n";

  for (int j = 0; j < h; j++) {
    std::cerr << "\rScanlines remaining: " << h - j << ' ' << std::flush;
    for (int i = 0; i < w; ++i) {
      Vector3d pixel_color(0, 0, 0);
      for (int s = 0; s < samples_per_pixel; ++s) {
        Tracey::Ray r = cam.get_direction(i, j);
        pixel_color += Tracey::RayColor(r, scene, max_depth);
      }
      Tracey::wirte_color(out, pixel_color, samples_per_pixel);
    }
  }
  std::cerr << "\nDone.\n";
}