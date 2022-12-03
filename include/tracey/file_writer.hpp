#pragma once

#include <Eigen/Dense>
#include <fstream>
#include <iostream>
#include <vector>
#include "constants.hpp"
#include "result.hpp"

using Eigen::Vector3d;

namespace Tracey {

class FileWriter {
 public:
  FileWriter(const std::string& filename, const std::string& path = "") {
    file_ = path + filename;
  }

  // writes the image vector to standard output according to ppm file format
  void write_file(Result& result) {
    std::ofstream file;
    file.open(file_, std::fstream::out);

    if (!file.good()) {
      std::cerr << "error writing file" << std::endl;
      return;
    }

    auto image = result.get_image();
    int samples_per_pixel = result.get_samples();
    int width = image[0].size();
    int height = image.size();
    std::cerr << width << " " << height << std::endl;

    file << "P3\n" << width << ' ' << height << "\n255\n";

    for (int j = height - 1; j >= 0; j--) {
      for (int i = 0; i < width; i++) {
        Vector3d pixel = image[j][i];
        write_pixel(file, pixel, samples_per_pixel);
      }
    }
  }

 private:
  std::string file_;

  // casts the vector of doubles into a valid color composed of 3 hex values
  void write_pixel(std::ofstream& file, Vector3d color, int samples_per_pixel) {
    // Divide the color by the number of samples.
    double scale = 1.0 / samples_per_pixel;
    double r = sqrt(scale * color(0));
    double g = sqrt(scale * color(1));
    double b = sqrt(scale * color(2));

    file << static_cast<int>(256 * Clamp(r, 0.0, 0.999)) << ' '
         << static_cast<int>(256 * Clamp(g, 0.0, 0.999)) << ' '
         << static_cast<int>(256 * Clamp(b, 0.0, 0.999)) << '\n';
  }
};

}  // namespace Tracey
