#include <cmath>
#include <iostream>
#include <vector>

#include "tracey.hpp"

int main() {
  Tracey::Camera camera(2, 3, 30.0);
  double u = (2 - sqrt(3)) * 1 / 3;
  double v = (2 - sqrt(3)) * 2 / 3;
  double w = -1.0;
  double dl = 1.0 / sqrt(u * u + v * v + w * w);
  u *= dl;
  v *= dl;
  w *= dl;
  auto [u_e, v_e, w_e] = camera.get_direction(1, 0);
  double eps = 1.0e-12;
  // calculate error
  double e1 = std::abs(u - u_e);
  double e2 = std::abs(v - v_e);
  double e3 = std::abs(w - w_e);
  if (e1 < eps && e2 < eps && e3 < eps) {
    return 0;
  } else {
    std::cout << "test failed" << std::endl;
    for (int y = 0; y < 3; y++) {
      for (int x = 0; x < 2; x++) {
        auto dir = camera.get_direction(x, y);
        std::cout << "x = " << x << ", y = " << y << ", du = " << dir[0]
                  << ", dv = " << dir[1] << ", dw = " << dir[2] << std::endl;
      }
    }
    return 1;
  }
}
