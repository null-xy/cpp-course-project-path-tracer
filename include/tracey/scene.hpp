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

  Vector3d vector_from_json(json vector_obj) {
    double x = vector_obj.value("x", 0.0);
    double y = vector_obj.value("y", 0.0);
    double z = vector_obj.value("z", 0.0);

    return Vector3d(x, y, z);
  }

  void camera_from_json(json cam_obj) {
    int h = cam_obj.value("height", 0.0);
    int w = cam_obj.value("width", 0.0);
    int fov = cam_obj.value("fov", 0.0);
    Vector3d origin = vector_from_json(cam_obj.at("origin"));

    camera_ = Tracey::Camera(h, w, origin, fov);
  }

  std::shared_ptr<Tracey::Material> material_from_json(json material_obj) {
    std::string type = material_obj.value("type", "");
    Vector3d albedo = vector_from_json(material_obj.at("albedo"));

    if (type == "metal") {
      double fuzz = material_obj.value("fuzz", 0.0);
      auto material = std::make_shared<Tracey::Metal>(albedo, fuzz);
      return material;
    }
    if (type == "glass") {
      double fuzz = material_obj.value("fuzz", 0.0);
      double refractive_index = material_obj.value("refractive_index", 0.0);
      auto material =
          std::make_shared<Tracey::Glass>(albedo, fuzz, refractive_index);
      return material;
    }
    auto material = std::make_shared<Tracey::Lambertian>(albedo);
    return material;
  }

  std::shared_ptr<Tracey::Geometry> geometry_from_json(json geometry_obj) {
    json params = geometry_obj.at("params");
    std::string type = geometry_obj.value("type", "");
    Vector3d origin = vector_from_json(geometry_obj.at("origin"));
    json material_obj = params.at("material");
    std::shared_ptr<Tracey::Material> material =
        material_from_json(material_obj);

    if (type == "sphere") {
      double radius = params.value("radius", 0.0);
      auto sphere = std::make_shared<Tracey::Sphere>(origin, radius, material);
      return sphere;
    }
    if (type == "box") {
      Vector3d dimensions = vector_from_json(geometry_obj.at("dimensions"));
      std::array<double, 3> dim = {dimensions(0), dimensions(1), dimensions(2)};
      Vector3d vec1 = vector_from_json(geometry_obj.at("vec1")).normalized();
      Vector3d vec2 = vector_from_json(geometry_obj.at("vec2")).normalized();
      Vector3d vec3 = vector_from_json(geometry_obj.at("vec3")).normalized();
      std::array<Vector3d, 3> base{vec1, vec2, vec3};
      auto box = std::make_shared<Tracey::Box>(origin, base, dim, material);
      return box;
    }
    return nullptr;
  }

  void geometries_from_json(json geometries) { 
    return;
  }

  const Tracey::Camera& get_camera() const { return camera_; }

  Tracey::GeometryList& get_geometries() { return geometry_; }

  friend void from_reader(Scene& scene,
                          std::unique_ptr<Tracey::FileReader>& reader);

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
  scene.camera_from_json(cam);

  auto geometries = scene_json.at("geometries");
  auto sphere_obj = geometries[0];

  auto sphere = scene.geometry_from_json(sphere_obj);
  scene.geometry_.add(sphere);
}

}  // namespace Tracey