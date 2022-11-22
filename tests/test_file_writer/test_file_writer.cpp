#include <Eigen/Dense>
#include <iostream>
#include <memory>

#include "../../include/tracey/tracey.hpp"

using Eigen::Vector3d;

const double infinity = std::numeric_limits<double>::infinity();

// compile instructions:
// g++ FileWriterTest.cpp -o fw.o
// to save as file, run the compiled file with '> o.ppm'
int main() {
  std::fstream out("out.ppm");
  std::vector<std::vector<Vector3d>> image;

  // image
  double aspectRatio = 16.0 / 9.0;
  int w = 800;
  int h = static_cast<int>(w / aspectRatio);

  // scene
  Tracey::GeometryList scene;

  // orthogonal basis
  Vector3d u_(1.0, 2.0, 3.0);
  Vector3d v_(3.0, 3.0, -3.0);
  Vector3d w_(-15.0, 12, -3.0);

  auto material_1 =
      std::make_shared<Tracey::Lambertian>(Vector3d(0.7, 0.3, 0.3));

  std::array<Vector3d, 3> vec{u_.normalized(), v_.normalized(),
                              w_.normalized()};
  std::array<double, 3> dim{0.5, 0.5, 0.5};

  scene.add(std::make_shared<Tracey::Box>(Vector3d(0.0, 0.0, -2.0), vec, dim,
                                          material_1));

  Vector3d origin(0.0, 0.0, 1.0);
  Tracey::Camera cam(w, h, origin, 45.0);

  const int samples_per_pixel = 100;
  const int max_depth = 50;

  for (int j = h - 1; j >= 0; j--) {
    std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
    std::vector<Vector3d> pixelRow;
    for (int i = 0; i < w; i++) {
      Vector3d pixel_color(0, 0, 0);
      for (int s = 0; s < samples_per_pixel; ++s) {
        Tracey::Ray r = cam.get_direction(i, j);
        pixel_color += Tracey::RayColor(r, scene, max_depth);
      }
      pixelRow.push_back(pixel_color);
    }
    image.push_back(pixelRow);
  }

  std::cerr << "Done"<< std::endl;

  Tracey::FileWriter fw(image);
  fw.WriteFile(out, samples_per_pixel);

  return 0;
}
