#pragma once

#include <Eigen/Dense>
#include <vector>

namespace Tracey {

class Result {
 public:
  Result()
  : samples_per_pixel_(1) {}
  Result(int s) {
    if (s <= 0) {
      samples_per_pixel_ = 1;
    }
    else samples_per_pixel_ = s;
  }

  int get_samples() const {
    return samples_per_pixel_;
  }

  const std::vector<std::vector<Vector3d>>& get_image() {
    return image_;
  }

  void update_image(const std::vector<std::vector<Vector3d>>& image) {
    image_ = image;
  }

 private:
  int samples_per_pixel_;
  std::vector<std::vector<Vector3d>> image_;
};

}  // namespace Tracey