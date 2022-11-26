#pragma once

#include <fstream>
#include <iostream>
#include <memory>

#include "../../libs/json.hpp"
#include "camera.hpp"
#include "geometry/geometry.hpp"
#include "geometry/geometry_list.hpp"
#include "reader.hpp"

using json = nlohmann::json;

namespace Tracey {

class Scene {
 public:
  Scene() {}
  Scene(Tracey::Camera& camera, Tracey::GeometryList& geometry_list)
   : camera_(camera), geometry_(geometry_list) {}
  friend void from_reader(Scene& scene, std::unique_ptr<Tracey::FileReader>& reader);

 private:
  Tracey::Camera camera_;
  Tracey::GeometryList geometry_;
};

void from_reader(Scene& scene, std::unique_ptr<Tracey::FileReader>& reader) {
  std::ifstream f(reader->get_filename());

  if (!f.good()) {
    std::cerr << "File " << reader->get_filename() << " not found" << std::endl;
    return;
  }

    json scene_json = json::parse(f);
    json cam = scene_json.at("camera");
    Tracey::Camera camera = Tracey::from_json(cam);

    auto geometries = scene_json.at("geometries");
    std::cerr << geometries << std::endl;

}

}  // namespace Tracey