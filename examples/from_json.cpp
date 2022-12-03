#include <cassert>
#include <fstream>
#include <iostream>

#include "tracey.hpp"

int main() {
  std::vector<std::vector<Vector3d>> image;
  // insert full path to json file
  std::string filename ="";
  // read file
  auto reader = Tracey::FileReader::create(filename);
  // create scene
  Tracey::Scene scene;
  // read objects into scene from file
  Tracey::from_reader(scene, reader);
  // create result
  Tracey::Result result(100);
  // render the scene into result
  Tracey::PathTracer::render(result, scene);
  // initialize filewriter with output filename
  Tracey::FileWriter writer("out.ppm");
  // write output file
  writer.write_file(result);
}