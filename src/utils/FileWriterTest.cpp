#include <eigen3/Eigen/Dense>
#include <iostream>
#include <memory>

#include "../geometry/GeometryList.hpp"
#include "../geometry/Sphere.hpp"
#include "../ray/Ray.hpp"
#include "FileWriter.hpp"

using Eigen::Vector3f;

const double infinity = std::numeric_limits<double>::infinity();

Vector3f RayColor(Ray& r, const Geometry& scene) {
  Hit_Record rec;
  if (scene.Intersect(r, 0, infinity, rec)) {
    return 0.5 * (rec.normal + Vector3f(1.0, 1.0, 1.0));
  }
  Vector3f unit = r.GetDirection().normalized();
  float t = 0.5 * (unit(1) + 1.0);
  return (1.0 - t) * Vector3f(1.0, 1.0, 1.0) + t * Vector3f(0.5, 0.7, 1.0);
}

// compile instructions:
// FileWriterTest.cpp FileWriter.cpp ../ray/Ray.cpp ../geometry/Geometry.hpp
// ../geometry/Sphere.cpp ../geometry/GeometryList.cpp -o FileWriterTest.o to
// save as file, run the compiled file with '> o.ppm'
int main() {
  std::vector<std::vector<Vector3f>> image;

  // image
  float aspectRatio = 16.0 / 9.0;
  int width = 400;
  int height = static_cast<int>(width / aspectRatio);

  // scene
  GeometryList scene;
  scene.Add(std::make_shared<Sphere>(Vector3f(0.0, -100.5, -1.0), 100));
  scene.Add(std::make_shared<Sphere>(Vector3f(0.0, 0.0, -1.0), 0.5));

  // camera
  auto viewPortHeight = 2.0;
  auto viewportWidth = aspectRatio * viewPortHeight;
  auto focalLength = 1.0;

  Vector3f origin(0.0, 0.0, 0.0);
  Vector3f horizontal(viewportWidth, 0.0, 0.0);
  Vector3f vertical(0.0, viewPortHeight, 0.0);
  Vector3f bottomLeftCorner =
      origin - horizontal / 2 - vertical / 2 - Vector3f(0.0, 0.0, focalLength);

  for (int j = height - 1; j >= 0; j--) {
    std::vector<Vector3f> pixelRow;
    for (int i = 0; i < width; i++) {
      auto u = double(i) / (width - 1);
      auto v = double(j) / (height - 1);
      Ray r(origin, bottomLeftCorner + u * horizontal + v * vertical - origin);

      Vector3f color = RayColor(r, scene);
      pixelRow.push_back(color);
    }
    image.insert(image.begin(), pixelRow);
  }

  FileWriter fw(image);
  fw.WriteFile();
  return 0;
}