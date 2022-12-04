#pragma once

#include <Eigen/Dense>
#include <vector>

namespace Tracey {
/**
 * @brief a class for storing the rendered image
 */
class Result {
 public:
 
 /**
 * @brief constructor for Result
 */
  Result()
  : samples_per_pixel_(1) {}
  
 /**
 * @brief constructor for Result
 * 
 * @param s number of samples for a given pixel, i.e. how many times a pixels color gets calculated
 */
  Result(int s) {
    if (s <= 0) {
      samples_per_pixel_ = 1;
    }
    else samples_per_pixel_ = s;
  }

 /**
 * @brief getter for samples_per_pixel_
 */
  int get_samples() const {
    return samples_per_pixel_;
  }

 /**
 * @brief getter for image container
 */
  const std::vector<std::vector<Vector3d>>& get_image() {
    return image_;
  }

  /**
  * @brief updates current image with the param image
  * 
  * @param image an image container
  * @return void
  */
  void update_image(const std::vector<std::vector<Vector3d>>& image) {
    image_ = image;
  }

 private:
  int samples_per_pixel_;
  std::vector<std::vector<Vector3d>> image_;
};

}  // namespace Tracey