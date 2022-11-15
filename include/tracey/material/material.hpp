#ifndef MATERIAL_CLASS
#define MATERIAL_CLASS
#include "../ray/ray.hpp"
#include "../ray/hittable.hpp"

namespace Tracey{
class Material{
    public:
    virtual bool Scatter(const Ray& ray, const HitRecord& hit, Eigen::Vector3d& attenuation, Ray& Scattered) const=0;
};

template <typename T>
class Lambertian : public Material{
    Lambertian(const Eigen::Vector3d& a):Albedo(a){}

};
}//namespace Tracey

#endif