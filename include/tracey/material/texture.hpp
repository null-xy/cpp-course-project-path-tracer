#ifndef TEXTURE_CLASS
#define TEXTURE_CLASS

#include <Eigen/Dense>

using Eigen::Vector3d;

namespace Tracey {
class Texture {
public:
  virtual Vector3d Color(double u, double v, const Vector3d &point) const = 0;
};

class SolidTexture : public Texture {
public:
  SolidTexture() {}
  SolidTexture(Vector3d color) : color_(color) {}

  Vector3d Color(double u, double v, const Vector3d &point) const {
    return color_;
  }

private:
  Vector3d color_;
};

class ChessBoardTexture : public Texture {
public:
  ChessBoardTexture() {}
  ChessBoardTexture(shared_ptr<Texture> even, shared_ptr<Texture> odd)
      : even_(even), odd_(odd) {}

  ChessBoardTexture(Vector3d color1, Vector3d color2)
      : even_(std::make_shared<SolidTexture>(color1)),
        odd_(std::make_shared<SolidTexture>(color2)) {}

  Vector3d Color(double u, double v, const Vector3d &point) const {
    auto sines =
        sin(10 * point.x()) * sin(10 * point.y()) * sin(10 * point.z());
    if (sines < 0) {
      return odd_->Color(u, v, point);
    } else {
      return even_->Color(u, v, point);
    }
  }

private:
  shared_ptr<Texture> odd_;
  shared_ptr<Texture> even_;
};
} // namespace Tracey

#endif