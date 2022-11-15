#include <eigen3/Eigen/Dense>
#include <iostream>
#include <memory>

#include "../../include/tracey/tracey.hpp"

using Eigen::Vector3d;

const double infinity = std::numeric_limits<double>::infinity();

Vector3d RayColor(Tracey::Ray& r, const Tracey::Geometry& scene) {
  Tracey::Hit_Record rec;
  if (scene.intersect(r, 0, infinity, rec)) {
    return 0.5 * (rec.normal + Vector3d(1.0, 1.0, 1.0));
  }
  Vector3d unit = r.get_direction().normalized();
  float t = 0.5 * (unit(1) + 1.0);
  return (1.0 - t) * Vector3d(1.0, 1.0, 1.0) + t * Vector3d(0.5, 0.7, 1.0);
}

// compile instructions:
// g++ FileWriterTest.cpp -o fw.o
// to save as file, run the compiled file with '> o.ppm'
int main() {
  std::vector<std::vector<Vector3d>> image;

  // image
  float aspectRatio = 16.0 / 9.0;
  int width = 400;
  int height = static_cast<int>(width / aspectRatio);

  // scene
  Tracey::GeometryList scene;
  //scene.Add(std::make_shared<Sphere>(Vector3d(0.0, -100.5, -1.0), 100));
  scene.add(std::make_shared<Tracey::Sphere>(Vector3d(0.0, 0.0, -1), 0.5));

  // camera
  /*auto viewPortHeight = 2.0;
  auto viewportWidth = aspectRatio * viewPortHeight;
  auto focalLength = 1.0;

  Vector3d origin(0.0, 0.0, 0.0);
  Vector3d horizontal(viewportWidth, 0.0, 0.0);
  Vector3d vertical(0.0, viewPortHeight, 0.0);
  Vector3d bottomLeftCorner =
      origin - horizontal / 2 - vertical / 2 - Vector3d(0.0, 0.0, focalLength);
  */

  Tracey::Camera cam(width, aspectRatio * width, 60.0);

  for (int j = height - 1; j >= 0; j--) {
    std::vector<Vector3d> pixelRow;
    for (int i = 0; i < width; i++) {
      auto dir = cam.get_direction(i, j);
      Vector3d dirToVec(dir[0], dir[1], dir[2]);
      Tracey::Ray r(Vector3d(0.0, 0.0, 0.0), dirToVec);

      Vector3d color = RayColor(r, scene);
      pixelRow.push_back(color);
    }
    image.insert(image.begin(), pixelRow);
  }

  Tracey::FileWriter fw(image);
  fw.WriteFile();
  return 0;
}