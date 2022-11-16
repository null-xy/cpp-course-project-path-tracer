#include <cmath>
#include <iostream>
#include <vector>

#include "tracey.hpp"

/*
In this unit test, image of width 2 and height 3 is constructed. One can
visually verify that the directions are calculated correctly.

Test returns error code 1 if failed, 0 otherwise.
*/
int main(int argc, char *argv[]) {
  (void)argv;
  Tracey::Camera camera(2, 3, Vector3f(0.0, 0.0, 0.0), 30.0);
  double u = (2 - sqrt(3)) * 1 / 3;
  double v = (2 - sqrt(3)) * 2 / 3;
  double w = -1.0;
  double dl = 1.0 / sqrt(u * u + v * v + w * w);
  u *= dl;
  v *= dl;
  w *= dl;
  auto r = camera.get_direction(1, 2);
  Vector3f dir = r.get_direction();
  float u_e = dir(0), v_e = dir(1), w_e = dir(2); 
  double eps = 1.0e-12;
  // calculate error
  double e1 = std::abs(u - u_e);
  double e2 = std::abs(v - v_e);
  double e3 = std::abs(w - w_e);
  bool success = (e1 < eps && e2 < eps && e3 < eps);
  bool print_info = argc > 1;
  if (!success || print_info) {
    for (int y = 0; y < 3; y++) {
      for (int x = 0; x < 2; x++) {
        auto direction = camera.get_direction(x, y).get_direction();
        std::cout << "(" << x << ", " << y << ") -> (" << direction(0) << ", "
                  << direction(1) << ", " << direction(2) << ")" << std::endl;
      }
    }
    return 1;
  } else {
    return 0;
  }
}
