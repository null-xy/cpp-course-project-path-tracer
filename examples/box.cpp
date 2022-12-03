#include <Eigen/Dense>
#include <iostream>
#include <memory>

#include "../include/tracey/tracey.hpp"

using Eigen::Vector3d;

int main() {
  std::vector<std::vector<Vector3d>> image;

  // image
  double aspectRatio = 16.0 / 9.0;
  int w = 400;
  int h = static_cast<int>(w / aspectRatio);

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

  auto pointlight = std::make_shared<Tracey::LightSource>(Vector3d(4.0, 4.0, 4.0));
  scene.add(std::make_shared<Tracey::Sphere>(Vector3d(0.5, 1.5, -0.5), 0.5,
                                             pointlight));

  scene.add(std::make_shared<Tracey::Box>(Vector3d(0.0, 0.0, -2.0), vec, dim,
                                          material));

  Vector3d origin(0.0, 0.0, 1.0);
  Tracey::Camera cam(w, h, origin, 45.0);

  Tracey::Scene s(cam, scene);
  Tracey::Result result(100);
  Tracey::PathTracer::render(result, s);
  Tracey::FileWriter writer("out.ppm");
  writer.write_file(result);

  return 0;
}