#include <cassert>
#include <iostream>
#include <fstream>

#include "tracey.hpp"

int main() {
  std::vector<std::vector<Vector3d>> image;
  //insert full path to file
  std::string filename = "/mnt/c/Users/Aleksi/Documents/Koulu/cpp-course-project-path-tracer/example.json";
  auto reader = Tracey::FileReader::create(filename);
  Tracey::Scene scene;
  Tracey::from_reader(scene, reader);

  int samples_per_pixel = 100;
  int max_depth = 50;

  auto camera = scene.get_camera();
  auto list = scene.get_geometries();
  int w = camera.get_width(), h = camera.get_height();

  for (int j = h - 1; j >= 0; j--) {
    std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
    std::vector<Vector3d> pixelRow;
    for (int i = 0; i < w; i++) {
      Vector3d pixel_color(0, 0, 0);
      Tracey::Ray r = camera.get_direction(i, j);
      for (int s = 0; s < samples_per_pixel; ++s) {
        pixel_color += Tracey::RayColor(r, list, max_depth);
      }
      pixelRow.push_back(pixel_color);
    }
    image.push_back(pixelRow);
  }
  std::cerr << "Done" << std::endl; 

  Tracey::FileWriter fw("from_json.ppm", image);
  fw.write_file(samples_per_pixel);

  return 0;

  return 0;
}