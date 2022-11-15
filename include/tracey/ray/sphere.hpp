#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.hpp"

namespace Tracey{
class sphere : public Hittable {
    public:
        sphere() {}
        sphere(Vector3f cen, float r) : center(cen), radius(r) {};

        virtual bool Hit(
            const Ray& r, float t_min, float t_max, HitRecord& rec) const override;

    public:
        Vector3f center;
        float radius;
};

bool sphere::Hit(const Ray& r, float t_min, float t_max, HitRecord& rec) const {
    Vector3f oc = r.get_origin() - center;
    auto a = r.get_direction().squaredNorm();
    auto half_b = oc.dot(r.get_direction());
    auto c = oc.squaredNorm() - radius*radius;

    auto discriminant = half_b*half_b - a*c;
    if (discriminant < 0) return false;
    auto sqrtd = sqrt(discriminant);

    // Find the nearest root that lies in the acceptable range.
    auto root = (-half_b - sqrtd) / a;
    if (root < t_min || t_max < root) {
        root = (-half_b + sqrtd) / a;
        if (root < t_min || t_max < root)
            return false;
    }

    rec.t = root;
    rec.point = r.at(rec.t);
    Vector3f outward_normal = (rec.point - center) / radius;
    rec.set_face_normal(r, outward_normal);
    //rec.normal = (rec.point - center) / radius;

    return true;
}
}//namespace

#endif