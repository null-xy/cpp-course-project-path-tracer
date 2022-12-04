#pragma once

#include <Eigen/Dense>
#include <array>
#include <cmath>
#include <iostream>

#include "constants.hpp"
#include "ray/ray.hpp"

using Eigen::Vector3d;
using json = nlohmann::json;

namespace Tracey {

/**
 * @brief This class contains functionality required to render a scene.
 *
 */
class Camera {
 public:
  Camera()
      : width_(0), height_(0), origin_(Vector3d(0.0, 0.0, 0.0)), angle_(0.0) {}
  /**
   * @brief Construct a new Camera object
   *
   * @param width is the width of the image, e.g. 1024 pixels
   * @param height is the height of the image, e.g. 768 pixels
   * @param origin is the location in xyz-coordinates
   * @param fov  is the field of view in degrees, e.g. 30
   */
  Camera(const int width, const int height, const Vector3d& origin,
         const double fov)
      : width_(width), height_(height), fov_(fov), origin_(origin) {
    angle_ = std::tan(constants::pi * 0.5 * fov / 180.0);
  }

  /**
  * @brief copy constructor
  */
  Camera(const Tracey::Camera& cam) {
    width_ = cam.width_;
    height_ = cam.height_;
    origin_ = cam.origin_;
    fov_ = cam.fov_;
    angle_ = cam.angle_;
  }

  /**
   * @brief Get the direction of a single ray towards pixel (x, y)
   *
   * @param x is the image x coordinate
   * @param y is the image y coordinate
   * @return const Ray(origin, direction)
   */
  const Ray get_direction(int x, int y) const {
    double xx = (angle_ * (2.0 * x - width_ + 1)) / height_;
    double yy = (angle_ * (height_ - 2 * y - 1)) / height_;

    Vector3d dir(xx, yy, -1);
    return Ray(origin_, dir.normalized());
  }

  /**
   * @brief getter for width of image
   */
  int get_width() const { return width_; }

  /**
   * @brief getter for height of image
   */
  int get_height() const { return height_; }
  
  /**
   * @brief getter for fov
   */
  int get_fov() const { return fov_; }
  
  /**
   * @brief getter for origin of camera
   */
  Vector3d get_origin() const { return origin_; }
  
  /**
  * @brief copy constructor
  */
  Camera operator=(const Tracey::Camera& cam) {
    width_ = cam.width_;
    height_ = cam.height_;
    origin_ = cam.origin_;
    fov_ = cam.fov_;
    angle_ = cam.angle_;
    return *this;
  }

 private:
  int width_, height_, fov_;
  Vector3d origin_;
  double angle_;
};

}  // namespace Tracey
