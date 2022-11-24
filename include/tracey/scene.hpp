#pragma once

#include <memory>
#include <fstream>
#include <iostream>

#include "../../libs/json.hpp"
#include "camera.hpp"
#include "reader.hpp"
#include "geometry/geometry.hpp"
#include "geometry/geometry_list.hpp"

namespace Tracey {

class Scene {
 public:
  Scene() {}
  Scene(Tracey::Camera& camera, Tracey::GeometryList& geometry_list)
      : camera_(camera), geometry_(geometry_list) {}

  static void from_reader(Scene& scene, std::unique_ptr<Tracey::FileReader>& reader) {
  std::ifstream f(reader->get_filename());

  if (!f.good()) {
    std::cerr << "File " << reader->get_filename() << " not found" << std::endl;
    return; 
  }

}

 private:
  Tracey::Camera camera_;
  Tracey::GeometryList geometry_;
};

}  // namespace Tracey