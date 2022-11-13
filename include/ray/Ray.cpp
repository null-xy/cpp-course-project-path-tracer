#include "Ray.hpp"
#include <iostream>

Ray::Ray() {};

Ray::Ray(Vector3f origin, Vector3f direction)
    : origin_(origin), direction_(direction) {}

Vector3f Ray::GetOrigin() const {
    return origin_;
}

Vector3f Ray::GetDirection() const {
    return direction_;
}

Vector3f Ray::At(float f) const {
    return origin_ + direction_ * f;
}

int main() {
    std::cout << "compiled" << std::endl;
}