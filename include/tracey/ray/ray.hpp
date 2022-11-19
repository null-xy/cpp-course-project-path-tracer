#pragma once

#include <Eigen/Dense>

using Eigen::Vector3d;

namespace Tracey {
/**
 * @brief This class depicts a ray of light
 */
class Ray {
public:
  /**
   * @brief Construct a new Ray object
   *
   * @param origin is the starting point of the vector in (x, y, z)
   * @param direction is the component vector of the ray in (x, y, z)
   */
  Ray() {}
  Ray(const Vector3d &origin, const Vector3d &direction)
      : origin_(origin), direction_(direction) {}

  /**
   * @brief Returns the origin of the ray
   */
  Vector3d get_origin() const { return origin_; }

  /**
   * @brief Returns the direction of the ray
   */
  Vector3d get_direction() const { return direction_; }

  /**
   * @brief Returns the destination point of the Ray object
   *
   * @param f is the factor that direction is multiplied by
   */
  Vector3d at(double f) const { return origin_ + direction_ * f; }

  /**
   * @brief Returns a random vector inside the unit sphere
   */
  friend inline Vector3d random_in_unit_sphere();

  /**
   * @brief Returns a reflection of the parameter vector
   * 
   * @param ray_in_direction direction for incoming ray
   * @param gradient direction perpendicular to the geometry
   * @return a relected vector
   */
  friend inline Vector3d Reflect(const Vector3d &ray_in_direction,
                                 const Vector3d &gradient);

  /**
   * @brief Returns a refraction of the parameter vector
   * 
   * @param ray_in_direction direction for incoming ray
   * @param gradient direction perpendicular to the geometry
   * @param n1_over_n2 refractive index from n1 / refractive index from n2
   * @return a relected vector
   */
  friend inline Vector3d Refract(const Vector3d &ray_in_direction,
                                 const Vector3d &gradient, double ni_over_nt);

private:
  Vector3d origin_;
  Vector3d direction_;
};

Vector3d random_in_unit_sphere() {
  Vector3d p;

  while (true) {
    double r = static_cast<double>(rand()) / static_cast<double>(RAND_MAX);
    double g = static_cast<double>(rand()) / static_cast<double>(RAND_MAX);
    double b = static_cast<double>(rand()) / static_cast<double>(RAND_MAX);
    Vector3d p(r, g, b);
    if (p.norm() >= 1.0) continue;
    return p;
  }
}

Vector3d Reflect(const Vector3d &ray_in_direction, const Vector3d &gradient) {
  return ray_in_direction - 2 * ray_in_direction.dot(gradient) * gradient;
}

//theta: angle from the direction perpendicular to ray hit geometry
//cos_theta: cos(theta)
Vector3d Refract(const Vector3d &ray_in_direction, const Vector3d &gradient,
                 double n1_over_n2) {
  double cos_theta = fmin((-ray_in_direction).dot(gradient), 1.0);
  Vector3d ray_out_perpendicular =
      n1_over_n2 * (ray_in_direction + cos_theta * gradient);
  Vector3d ray_out_parallel =
      -sqrt(fabs(1.0 - ray_out_perpendicular.squaredNorm())) * gradient;
  return ray_out_perpendicular + ray_out_parallel;
}

} // namespace Tracey