#pragma once

#include <array>
#include <cmath>

#include "constants.hpp"
#include "ray/ray.hpp"

namespace Tracey {

/**
 * @brief This class contains functionality required to render a scene.
 *
 */
class Camera {
 private:
  const int width_, height_;
  Vector3f origin_;
  float aspect_ratio_, angle_;

 public:
  /**
   * @brief Construct a new Camera object
   *
   * @param width is the width of the image, e.g. 1024 pixels
   * @param height is the height of the image, e.g. 768 pixels
   * @param fov  is the field of view in degrees, e.g. 30
   */
  Camera(const int width, const int height, const Vector3f& origin,
         const double fov)
      : width_(width), height_(height), origin_(origin) {
    aspect_ratio_ = width_ / float(height_);
    angle_ = std::tan(constants::pi * 0.5 * fov / 180.0);
  }

  /**
   * @brief Get the direction of a single ray.
   *
   * @param x is the image x coordinate
   * @param y is the image y coordinate
   * @return const std::array<double, 3>
   */
  const Ray get_direction(int x, int y) const {
    float inv_height = 1.0 / height_, inv_width = 1.0 / width_;

    float xx = (2 * ((x + 0.5) * inv_width) - 1) * angle_ * aspect_ratio_;
    float yy = (1 - 2 * ((y + 0.5) * inv_height)) * angle_;

    Vector3f dir(xx, yy, -1);
    return Ray(origin_, dir.normalized());
  }
};

}  // namespace Tracey
