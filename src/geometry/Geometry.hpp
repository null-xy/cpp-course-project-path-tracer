#ifndef PATH_TRACER_GEOMETRY
#define PATH_TRACER_GEOMETRY

#include <eigen3/Eigen/Dense>
#include "../ray/Ray.hpp"

using Eigen::Vector3f;

//wip
class Geometry {
    public:
        Geometry() {}
        virtual bool Intersect(Ray& ray) const;
    private:
};

#endif