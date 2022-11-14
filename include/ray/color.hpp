#ifndef COLOR_CLASS
#define COLOR_CLASS
#include "ray.hpp"

void wirte_color(std::ostream &out, Eigen::Vector3d pixel_color){
    //auto r=pixel_color.x();
    //auto g=pixel_color.y();
    //auto b=pixel_color.z();
    out << static_cast<int>(255.999 * pixel_color.x()) << ' '
        << static_cast<int>(255.999 * pixel_color.y()) << ' '
        << static_cast<int>(255.999 * pixel_color.z()) << '\n';
}

#endif