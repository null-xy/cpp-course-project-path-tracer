#ifndef HITTABLE_CLASS
#define HITTABLE_CLASS
#include "ray.hpp"


namespace Tracey{

	class Material;
//template <typename T>
struct HitRecord
{
	//T t;
	double t;
	Vector3d point;
	Vector3d normal;
	//Material* material;
	bool front_face;

	inline void set_face_normal(const Tracey::Ray& ray, const Vector3d& outward_normal) {
		front_face = ray.get_direction().dot(outward_normal) < 0;
        normal = front_face ? outward_normal :-outward_normal;
    }
};

class Hittable {
    public:
        virtual bool Hit(const Tracey::Ray& r, double min, double max, HitRecord& rec) const = 0;
};
} //namespace Tracey


#endif