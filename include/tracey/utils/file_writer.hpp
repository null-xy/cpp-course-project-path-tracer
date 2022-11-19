#pragma once

#include <Eigen/Dense>
#include <iostream>
#include <vector>

using Eigen::Vector3d;

namespace Tracey {

class FileWriter {
 public:
  FileWriter(std::vector<std::vector<Vector3d>> image) : image_(image) {}

  ~FileWriter() { image_.clear(); }

  // casts the vector of doubles into a valid color composed of 3 hex values
  void WritePixel(std::ostream& os, Vector3d color) {
    int r = static_cast<int>(255.999 * color(0));
    int g = static_cast<int>(255.999 * color(1));
    int b = static_cast<int>(255.999 * color(2));

    os << r << ' ' << g << ' ' << b << '\n';
  }

  // writes the image vector to standard output according to ppm file format
  void WriteFile() {
    int width = image_[0].size();
    int height = image_.size();

    std::cout << "P3\n" << width << ' ' << height << "\n255\n";

    for (int j = height - 1; j >= 0; j--) {
      for (int i = 0; i < width; i++) {
        Vector3d pixel = image_[j][i];
        WritePixel(std::cout, pixel);
      }
    }
  }

 private:
  std::vector<std::vector<Vector3d>> image_;
};

} // namespace Tracey
