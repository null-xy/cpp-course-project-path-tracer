#pragma once

#include <array>
#include <cmath>

#include "constants.hpp"

namespace Tracey {

/**
 * @brief This class contains functionality required to render a scene.
 *
 */
class Camera {

private:
  int m_width, m_height;
  double m_u0, m_du, m_v0, m_dv;

public:
  /**
   * @brief Construct a new Camera object
   *
   * @param width is the width of the image, e.g. 1024 pixels
   * @param height is the height of the image, e.g. 768 pixels
   * @param fov  is the field of view in degrees, e.g. 30
   */
  Camera(const int width, const int height, const double fov)
      : m_width(width), m_height(height) {
    double a1 = std::tan(constants::pi * 0.5 * fov / 180.0);
    double a2 = a1 * m_width / m_height;
    double i1 = 1.0 / m_width;
    double i2 = 1.0 / m_height;
    m_u0 = a2 * (i1 - 1.0);
    m_du = 2.0 * a2 * i1;
    m_v0 = a1 * (i2 - 1.0);
    m_dv = 2.0 * a1 * i2;
  }

  /**
   * @brief Get the direction of a single ray.
   *
   * @param x is the image x coordinate
   * @param y is the image y coordinate
   * @return const std::array<double, 3>
   */
  const std::array<double, 3> get_direction(int x, int y) const {
    double u = m_u0 + x * m_du;
    double v = m_v0 + y * m_dv;
    double w = -1.0;
    double inv_norm = 1.0 / std::sqrt(1.0 + u * u + v * v);
    return {inv_norm * u, inv_norm * v, inv_norm * w};
  }
};

} // namespace Tracey
