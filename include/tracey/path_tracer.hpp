#pragma once

#include <Eigen/Dense>

#include "ray/color.hpp"
#include "camera.hpp"
#include "result.hpp"
#include "scene.hpp"
#include "geometry/geometry.hpp"
#include "geometry/geometry_list.hpp"

namespace Tracey {

class PathTracer {
 public:
  static void render(Result& result, Scene& scene) {
    std::vector<std::vector<Vector3d>> image;
    int max_depth = 50;
    Vector3d background(0.0, 0.0, 0.0);

    int samples_per_pixel = result.get_samples();
    Tracey::GeometryList list = scene.get_geometries();
    Tracey::Camera camera = scene.get_camera();
    int w = camera.get_width(), h = camera.get_height();

    for (int j = h - 1; j >= 0; j--) {
      std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
      std::vector<Vector3d> pixelRow;
      for (int i = 0; i < w; i++) {
        Vector3d pixel_color(0.0, 0.0, 0.0);
        Tracey::Ray r = camera.get_direction(i, j);
        for (int s = 0; s < samples_per_pixel; ++s) {
          pixel_color += Tracey::RayColor(r, background, list, max_depth);
        }
        pixelRow.push_back(pixel_color);
      }
      image.push_back(pixelRow);
    }
    std::cerr << "Done" << std::endl;
    result.update_image(image);
  }
};
}  // namespace Tracey