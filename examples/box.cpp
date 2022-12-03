#include <Eigen/Dense>
#include <iostream>
#include <memory>

#include "../include/tracey/tracey.hpp"

using Eigen::Vector3d;

int main() {
  std::vector<std::vector<Vector3d>> image;

  // image
  double aspectRatio = 16.0 / 9.0;
  int w = 100;
  int h = static_cast<int>(w / aspectRatio);
  int samples_per_pixel = 100;
  int max_depth = 50;

  // scene
  Tracey::GeometryList scene;

  // orthogonal basis
  Vector3d u_(1.0, 2.0, 3.0);
  Vector3d v_(3.0, 3.0, -3.0);
  Vector3d w_(-15.0, 12, -3.0);

  std::array<Vector3d, 3> vec{u_.normalized(), v_.normalized(),
                              w_.normalized()};
  std::array<double, 3> dim{0.5, 0.5, 0.5};
  std::shared_ptr<Tracey::Material> material =
      std::make_shared<Tracey::Lambertian>(Vector3d(0.7, 0.3, 0.3));

  scene.add(std::make_shared<Tracey::Box>(Vector3d(0.0, 0.0, -2.0), vec, dim,
                                          material));

  Vector3d origin(0.0, 0.0, 1.0);
  Tracey::Camera cam(w, h, origin, 45.0);

  for (int j = h - 1; j >= 0; j--) {
    std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
    std::vector<Vector3d> pixelRow;
    for (int i = 0; i < w; i++) {
      Vector3d pixel_color(0, 0, 0);
      Tracey::Ray r = cam.get_direction(i, j);
      for (int s = 0; s < samples_per_pixel; ++s) {
        pixel_color += Tracey::RayColor(r, Vector3d(0.2, 0.2, 0.6), scene, max_depth);
      }
      pixelRow.push_back(pixel_color);
    }
    image.push_back(pixelRow);
  }
  std::cerr << "Done" << std::endl;

  Tracey::FileWriter fw("out.ppm", image, "../../output/");
  fw.write_file(samples_per_pixel);

  return 0;
}