#pragma once

#include <Eigen/Dense>
#include <fstream>
#include <vector>

using Eigen::Vector3d;

namespace Tracey {

class FileWriter {
 public:
  FileWriter(std::vector<std::vector<Vector3d>> image) : image_(image) {}

  ~FileWriter() { image_.clear(); }

  // casts the vector of doubles into a valid color composed of 3 hex values
  void WritePixel(std::fstream& file, Vector3d color, int samples_per_pixel) {
    // Divide the color by the number of samples.
    double scale = 1.0 / samples_per_pixel;
    double r = sqrt(scale * color(0));
    double g = sqrt(scale * color(1));
    double b = sqrt(scale * color(2));

    file << static_cast<int>(256 * Clamp(r, 0.0, 0.999)) << ' '
         << static_cast<int>(256 * Clamp(g, 0.0, 0.999)) << ' '
         << static_cast<int>(256 * Clamp(b, 0.0, 0.999)) << '\n';
  }

  // writes the image vector to standard output according to ppm file format
  void WriteFile(std::fstream& file, int samples_per_pixel) {
    int width = image_[0].size();
    int height = image_.size();

    file << "P3\n" << width << ' ' << height << "\n255\n";

    for (int j = height - 1; j >= 0; j--) {
      for (int i = 0; i < width; i++) {
        Vector3d pixel = image_[j][i];
        WritePixel(file, pixel, samples_per_pixel);
      }
    }
  }

 private:
  std::vector<std::vector<Vector3d>> image_;
};

}  // namespace Tracey
