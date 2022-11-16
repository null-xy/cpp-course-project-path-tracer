#ifndef HITABLE_LIST_CLASS
#define HITABLE_LIST_CLASS
#include "hittable.hpp"

#include <memory>
#include <vector>

using std::shared_ptr;
using std::make_shared;
namespace Tracey {
class HittableList : public Hittable{
    public:
    HittableList(){}

    HittableList(shared_ptr<Hittable> obj){ add(obj);}
    void Clear() {objects_.clear();}
    void add(shared_ptr<Hittable> obj) {objects_.push_back(obj);}

    virtual bool Hit(const Tracey::Ray& r, double min, double max, HitRecord& hit) const override;
    
    std::vector<shared_ptr<Hittable>> objects_;
};

bool HittableList::Hit(const Tracey::Ray& r, double min, double max, HitRecord& hit) const{
    HitRecord temp;
    bool hit_anything=false;
    auto closest_so_far=max;
    
    for (const auto& object : objects_) {
        if (object->Hit(r, min, closest_so_far, temp)) {
            hit_anything = true;
            closest_so_far = temp.t;
            hit = temp;
        }
    }

    return hit_anything;
}
}//namespace Tracey
#endif