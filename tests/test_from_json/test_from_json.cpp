#include <cassert>
#include <iostream>
#include <fstream>

#include "tracey.hpp"

int main() {
  //path to example.json
  std::string filename = "/mnt/c/Users/Aleksi/Documents/Koulu/cpp-course-project-path-tracer/example_scene.json";
  auto reader = Tracey::FileReader::create(filename);
  Tracey::Scene scene;
  Tracey::from_reader(scene, reader);

  auto camera = scene.get_camera();
  auto list = scene.get_geometries();

  // camera has corerect parameters
  assert(camera.get_width() == 400);
  assert(camera.get_height() == 225);
  assert(camera.get_origin() == Vector3d(0.0, 0.0, 2.0));
  assert(camera.get_fov() == 50);

  // geometries are correctly initialized
  for (auto g : list.get_objects()) {
    assert(g != nullptr);
  }

  return 0;
}