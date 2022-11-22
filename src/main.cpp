#include <iostream>
#include <Eigen/Dense>

/*
Eigen::Vector3d ray_color(const Ray& r) {
    Eigen::Vector3d unit_direction = unit_vector(r.Direction());
    auto t = 0.5*(unit_direction.y() + 1.0);
    return (1.0-t)*Eigen::Vector3d(1.0, 1.0, 1.0) + t*Eigen::Vector3d(0.5, 0.7, 1.0);
}
*/