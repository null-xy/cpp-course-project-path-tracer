#pragma once

#include <fstream>
#include <iostream>
#include <memory>

#include "../../libs/json.hpp"
#include "camera.hpp"
#include "geometry/geometry.hpp"
#include "geometry/geometry_list.hpp"
#include "ray/light_source.hpp"
#include "reader.hpp"

using json = nlohmann::json;

namespace Tracey {

/**
 * @brief Class that depicts the scene to be rendered
 */
class Scene {
 public:
  Scene() {}
  Scene(Tracey::Camera& camera, Tracey::GeometryList& geometry_list)
      : camera_(camera), geometry_(geometry_list) {}

  /**
   * @brief Parse a Vector3d from a json object
   */
  Vector3d vector_from_json(json vector_obj) {
    double x = vector_obj.value("x", 0.0);
    double y = vector_obj.value("y", 0.0);
    double z = vector_obj.value("z", 0.0);

    return Vector3d(x, y, z);
  }

  /**
   * @brief Parse a Camera object from a json object
   */
  void camera_from_json(json cam_obj) {
    int w = cam_obj.value("width", 0);
    int h = cam_obj.value("height", 0);
    int fov = cam_obj.value("fov", 0);
    Vector3d origin = vector_from_json(cam_obj.at("origin"));

    camera_ = Tracey::Camera(w, h, origin, fov);
  }

  /**
  * @brief Parse a Texture object from a json object
  */
  std::shared_ptr<Tracey::Texture> texture_from_json(json texture_obj) {
    std::string type = texture_obj.value("type", "");

    if (type == "solid") {
      Vector3d color = vector_from_json(texture_obj.at("color"));
      auto texture = std::make_shared<SolidTexture>(color);
      return texture;
    }

    if (type == "chessboard") {
      Vector3d color1 = vector_from_json(texture_obj.at("color1"));
      Vector3d color2 = vector_from_json(texture_obj.at("color2"));
      auto texture = std::make_shared<ChessBoardTexture>(color1, color2);
      return texture;
    }

    return nullptr;
  }

  /**
   * @brief Parse a Material object from a json object
   */
  std::shared_ptr<Tracey::Material> material_from_json(json material_obj) {
    std::string type = material_obj.value("type", "");

    if (type == "metal") {
      Vector3d albedo = vector_from_json(material_obj.at("albedo"));
      double fuzz = material_obj.value("fuzz", 0.0);
      auto material = std::make_shared<Tracey::Metal>(albedo, fuzz);
      return material;
    }

    if (type == "glass") {
      Vector3d albedo = vector_from_json(material_obj.at("albedo"));
      double fuzz = material_obj.value("fuzz", 0.0);
      double refractive_index = material_obj.value("refractive_index", 0.0);
      auto material =
          std::make_shared<Tracey::Glass>(albedo, fuzz, refractive_index);
      return material;
    }

    if (type == "lambertian") {    
    json texture_obj = material_obj.at("texture");
    auto texture = texture_from_json(texture_obj);
    auto material = std::make_shared<Tracey::Lambertian>(texture);
    return material;
    }

    if (type == "light") {
    Vector3d albedo = vector_from_json(material_obj.at("albedo"));
    auto light = std::make_shared<Tracey::LightSource>(albedo);
    return light;
    }

    return nullptr;
  }

  /**
   * @brief Parse a Geometry object from a json object
   */
  std::shared_ptr<Tracey::Geometry> geometry_from_json(json geometry_obj) {
    json params = geometry_obj.at("params");
    json material_obj = params.at("material");

    std::string type = geometry_obj.value("type", "");
    Vector3d origin = vector_from_json(params.at("origin"));

    std::shared_ptr<Tracey::Material> material =
        material_from_json(material_obj);

    if (type == "sphere") {
      double radius = params.value("radius", 0.0);
      auto sphere = std::make_shared<Tracey::Sphere>(origin, radius, material);
      return sphere;
    }

    if (type == "box") {
      Vector3d dimensions = vector_from_json(params.at("dimensions"));
      std::array<double, 3> dim = {dimensions(0), dimensions(1), dimensions(2)};
      Vector3d vec1 = vector_from_json(params.at("vec1")).normalized();
      Vector3d vec2 = vector_from_json(params.at("vec2")).normalized();
      Vector3d vec3 = vector_from_json(params.at("vec3")).normalized();
      std::array<Vector3d, 3> base{vec1, vec2, vec3};
      auto box = std::make_shared<Tracey::Box>(origin, base, dim, material);
      return box;
    }

    if (type == "plane") {
      Vector3d normal = vector_from_json(params.at("normal"));
      double radius = params.value("radius", 0.0);
      auto plane =
          std::make_shared<Tracey::Plane>(origin, normal, radius, material);
      return plane;
    }

    return nullptr;
  }

  /**
   * @brief Parse a list of Geometries from a json object and add them to member
   * geometry_
   */
  void geometries_from_json(json geometries_obj) {
    for (auto obj : geometries_obj) {
      auto geometry = geometry_from_json(obj);
      geometry_.add(geometry);
    }
    return;
  }

  /**
   * @brief getter for camera_
   */
  const Tracey::Camera& get_camera() const { return camera_; }

  /**
   * @brief getter for geometry_
   */
  Tracey::GeometryList& get_geometries() { return geometry_; }

  /**
   * @brief reads a json file and appends the objects to the scene
   * @param scene the scene that the objects will be added to
   * @param reader a filereader that has read the file
   * @return void, since function modifies the state of scene
   */
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
  json camera_obj = scene_json.at("camera");
  scene.camera_from_json(camera_obj);

  json geometries_obj = scene_json.at("geometries");

  scene.geometries_from_json(geometries_obj);
}

}  // namespace Tracey