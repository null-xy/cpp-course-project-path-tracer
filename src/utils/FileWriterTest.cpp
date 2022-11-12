#include <eigen3/Eigen/Dense>
#include <iostream>

#include "../geometry/Sphere.hpp"
#include "../ray/Ray.hpp"
#include "FileWriter.hpp"

using Eigen::Vector3f;

Vector3f ray_color(Sphere& s, Ray& r) {
  // if ray hits ball, return red
  if (s.Intersect(r)) {
    return Vector3f(1.0, 0.0, 0.0);
  }

  // create a color gradient of blue
  Vector3f unit = r.GetDirection().normalized();
  auto t = 0.5 * (unit(1) + 1.0);
  return (1.0 - t) * Vector3f(1.0, 1.0, 1.0) + t * Vector3f(0.5, 0.7, 1.0);
}

// compile instructions:
// g++ FileWriterTest.cpp FileWriter.cpp ../ray/Ray.cpp ../geometry/Geometry.hpp ../geometry/Sphere.cpp -o FileWriterTest.o
// -o FileWriterTest to save as file, run the compiled file with '> o.ppm'
int main() {
  std::vector<std::vector<Vector3f>> image;
  Sphere ball(Vector3f(0.0, 0.0, -1.0), 0.5);

  // image
  float aspectRatio = 16.0 / 9.0;
  int width = 400;
  int height = static_cast<int>(width / aspectRatio);

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

      Vector3f color = ray_color(ball, r);
      pixelRow.push_back(color);
    }
    image.insert(image.begin(), pixelRow);
  }

  FileWriter fw(image);
  fw.WriteFile();
  return 0;
}