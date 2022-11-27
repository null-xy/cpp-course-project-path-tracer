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

  // material
  Vector3d background(0,0,0);
  auto pointlight = std::make_shared<Tracey::LightSource>(Vector3d(4,4,4));

auto material_ground = std::make_shared<Tracey::ChessBoardTexture>(Vector3d(0.2, 0.3, 0.1),Vector3d(0.9, 0.9, 0.9));
  //auto material_ground =
  //    std::make_shared<Tracey::Lambertian>(Vector3d(0.8, 0.8, 0.0));
  auto material_sphere_0 =
      std::make_shared<Tracey::Metal>(Vector3d(0.8, 0.6, 0.2), 0.3);
  auto material_sphere_1 =
      std::make_shared<Tracey::Lambertian>(Vector3d(0.7, 0.3, 0.3));
  //
  auto material_sphere_2 = std::make_shared<Tracey::Glass>(Vector3d(0.8, 0.8, 0.8),0.0,1.3);
  // scene
  Tracey::GeometryList scene;
    scene.add(std::make_shared<Tracey::Sphere>(Vector3d(0.5, 1.5, -0.5), 0.5,
                                             pointlight));
  scene.add(std::make_shared<Tracey::Sphere>(Vector3d(0.0, 0.0, -1.0), 0.5,
                                             material_sphere_0));
  scene.add(std::make_shared<Tracey::Sphere>(Vector3d(-1.0, 0.0, -1.0), 0.5,
                                             material_sphere_1));
  scene.add(std::make_shared<Tracey::Sphere>(Vector3d(1.0, 0.0, -1.0), 0.5,
                                             material_sphere_2));
  // radius<0 to make a empty sphere inside the glass sphere
  // scene.add(std::make_shared<Tracey::Sphere>(Vector3d(1.0, 0.0, -1.0), -0.4,
  //                                           material_sphere_2));
  scene.add(std::make_shared<Tracey::Sphere>(Vector3d(0.0, -100.5, -1.0), 100, std::make_shared<Tracey::Lambertian>(material_ground)
                                             ));

  Vector3d origin(0.0, 0.0, 2.0);
  Tracey::Camera cam(w, h, origin, 50.0);

  out << "P3\n" << w << ' ' << h << "\n255\n";

  for (int j = 0; j < h; j++) {
    std::cerr << "\rScanlines remaining: " << h - j << ' ' << std::flush;
    for (int i = 0; i < w; ++i) {
      Vector3d pixel_color(0, 0, 0);
      for (int s = 0; s < samples_per_pixel; ++s) {
        Tracey::Ray r = cam.get_direction(i, j);
        pixel_color += Tracey::RayColor(r,background, scene, max_depth);
      }
      Tracey::WirteColor(out, pixel_color, samples_per_pixel);
    }
  }
  std::cerr << "\nDone.\n";
}