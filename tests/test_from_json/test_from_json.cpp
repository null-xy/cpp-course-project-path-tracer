#include <cassert>
#include <iostream>

#include "tracey.hpp"

int main() {
  json sphere_obj = json::parse(R"({
            "type": "sphere",
            "params": {
                "x": 0.0,
                "y": 0.0,
                "z": -1.0,
                "radius": 0.5,
                "material": {
                    "type": "lambertian",
                    "albedo_x": 0.8,
                    "albedo_y": 0.8,
                    "albedo_z": 0.0
                }
            }
        })");

  std::vector<std::vector<Vector3d>> image;
  double aspectRatio = 16.0 / 9.0;
  int w = 400;
  int h = static_cast<int>(w / aspectRatio);
  int samples_per_pixel = 100;
  int max_depth = 50;

  Tracey::GeometryList list;
  Tracey::Camera cam(w, h, Vector3d(0.0, 0.0, 0.0), 90);
  Tracey::Scene scene(cam, list);
  std::shared_ptr<Tracey::Geometry> sphere =
      scene.geometry_from_json(sphere_obj);
  scene.get_geometries().add(sphere);

  for (int j = h - 1; j >= 0; j--) {
    std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
    std::vector<Vector3d> pixelRow;
    for (int i = 0; i < w; i++) {
      Vector3d pixel_color(0, 0, 0);
      Tracey::Ray r = cam.get_direction(i, j);
      for (int s = 0; s < samples_per_pixel; ++s) {
        pixel_color += Tracey::RayColor(r, scene.get_geometries(), max_depth);
      }
      pixelRow.push_back(pixel_color);
    }
    image.push_back(pixelRow);
  }
  std::cerr << "Done" << std::endl;

  Tracey::FileWriter fw("from_json.ppm", image);
  fw.write_file(samples_per_pixel);

  return 0;
}