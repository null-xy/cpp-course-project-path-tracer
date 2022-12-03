#include <cassert>
#include <iostream>
#include <fstream>

#include "tracey.hpp"

int main() {
  std::string filename = "/mnt/c/Users/Aleksi/Documents/Koulu/cpp-course-project-path-tracer/example.json";
  auto reader = Tracey::FileReader::create(filename);
  Tracey::Scene scene;
  Tracey::from_reader(scene, reader);

  auto camera = scene.get_camera();
  //auto list = scene.get_geometries();

  assert(camera.get_width() == 100);
  assert(camera.get_height() == 56);
  assert(camera.get_origin() == Vector3d(0.0, 0.0, 0.0));
  assert(camera.get_fov() == 50);

  return 0;
}