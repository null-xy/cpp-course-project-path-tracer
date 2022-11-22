#include <Eigen/Dense>
#include <iostream>
#include <memory>

#include "../../include/tracey/tracey.hpp"

using Eigen::Vector3d;

const double infinity = std::numeric_limits<double>::infinity();

Vector3d RayColor(Tracey::Ray &r, const Tracey::Geometry &scene) {
  Tracey::Hit_Record rec;
  if (scene.intersect(r, 0, infinity, rec)) {
    return 0.5 * (rec.normal + Vector3d(1.0, 1.0, 1.0));
    //return 0.5 * Vector3d(1.0, 1.0, 1.0);
  }
  Vector3d unit = r.get_direction().normalized();
  double t = 0.5 * (unit(1) + 1.0);
  //background color
  return (1.0 - t) * Vector3d(1.0, 1.0, 1.0) + t * Vector3d(0.5, 0.7, 1.0);
}

// compile instructions:
// g++ FileWriterTest.cpp -o fw.o
// to save as file, run the compiled file with '> o.ppm'
int main() {
  std::vector<std::vector<Vector3d>> image;

  // image
  double aspectRatio = 16.0 / 9.0;
  int w = 800;
  int h = static_cast<int>(w / aspectRatio);

  // scene
  Tracey::GeometryList scene;
  //scene.add(std::make_shared<Tracey::Sphere>(Vector3d(-1.0, 0.0, -1.0), 0.5));
  //scene.add(std::make_shared<Tracey::Sphere>(Vector3d(0.0, -100.5, -1.0), 100));
  //scene.add(std::make_shared<Tracey::Plane>(Vector3d(0.0, 0.0, -1.0), Vector3d(2.0, 1.0, -1.0), 0.5));
  
  //orthogonal basis
  Vector3d u_(1.0, 2.0, 3.0);
  Vector3d v_(3.0, 3.0, -3.0);
  Vector3d w_(-15.0, 12, -3.0);

  //non orthogonal basis
  //Vector3d u_(1.0, 62.0, -3.0);
  //Vector3d v_(1.23, 3.7, -2.0);
  //Vector3d w_(12.0, 17.5, -6.0);

  //std::cerr << u_.normalized() << v_.normalized() << w_.normalized() << std::endl;

  std::array<Vector3d, 3> vec{u_.normalized(), v_.normalized(), w_.normalized()};
  std::array<Vector3d, 3> aa{Vector3d(1.0, 0.0, 0.0), Vector3d(0.0, 1.0, 0.0), Vector3d(0.0, 0.0, 1.0)};
  std::array<double, 3> dim{0.5, 0.5, 0.5};

  //scene.add(std::make_shared<Tracey::Box>(Vector3d(0.0, 0.0, -2.0), aa, dim));
  scene.add(std::make_shared<Tracey::Box>(Vector3d(0.0, 0.0, -2.0), vec, dim));

  Vector3d origin(0.0, 0.0, 1.0);
  Tracey::Camera cam(w, h, origin, 45.0);

  for (int j = h - 1; j >= 0; j--) {
    std::vector<Vector3d> pixelRow;
    for (int i = 0; i < w; i++) {
      auto dir = cam.get_direction(i, j);
      Vector3d color = RayColor(dir, scene);
      pixelRow.push_back(color);
    }
    image.push_back(pixelRow);
  }

  Tracey::FileWriter fw(image);
  fw.WriteFile();
  return 0;
}
