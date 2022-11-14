#ifndef PATH_TRACER_RAY
#define PATH_TRACER_RAY

#include <eigen3/Eigen/Dense>

using Eigen::Vector3f;

class Ray {
    public:
        Ray();
        Ray(Vector3f origin, Vector3f direction);

        Vector3f GetOrigin() const;
        Vector3f GetDirection() const;
        Vector3f At(float f) const;

    private:
        Vector3f origin_;
        Vector3f direction_;
};

#endif