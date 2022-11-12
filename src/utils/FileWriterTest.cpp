#include <eigen3/Eigen/Dense>

#include "FileWriter.hpp"

using Eigen::Vector3f;

//compile instructions:
//g++ FileWriterTest.cpp FileWriter.cpp -o FileWriterTest
//to save as file, run the compiled file with '> o.ppm'
int main() {

  std::vector<std::vector<Vector3f>> image;
  int height = 512; 
  int width = 256;

  for (int j = height - 1; j >= 0; j--) {
    std::vector<Vector3f> pixelRow; 
    for (int i = 0; i < width; i++) {
      auto r = float(i) / (width - 1);
      auto g = float(j) / (height - 1);
      auto b = 0.55;
      
      Vector3f color(r, g, b);
      pixelRow.push_back(color);
    }
    image.insert(image.begin(), pixelRow);
  }

  FileWriter fw(image);
  fw.WriteFile();
  return 0;
}