#ifndef COLOR_CLASS
#define COLOR_CLASS
#include "ray.hpp"

void wirte_color(std::ostream &out, Vector3f pixel_color, int samples_per_pixel){
<<<<<<< HEAD
    /*auto r=pixel_color.x();
=======
    auto r=pixel_color.x();
>>>>>>> 5da39af0524b969c646ee7c5731281e92d2d9a8f
    auto g=pixel_color.y();
    auto b=pixel_color.z();
        // Divide the color by the number of samples.
    auto scale = 1.0 / samples_per_pixel;
<<<<<<< HEAD
    r *= scale;
    g *= scale;
    b *= scale;
=======
    r = sqrt(scale*r);
    g = sqrt(scale*g);
    b = sqrt(scale*b);
>>>>>>> 5da39af0524b969c646ee7c5731281e92d2d9a8f

    // Write the translated [0,255] value of each color component.
    out << static_cast<int>(256 * Tracey::clamp(r, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * Tracey::clamp(g, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * Tracey::clamp(b, 0.0, 0.999)) << '\n';
<<<<<<< HEAD
    */
    out << static_cast<int>(255.999 * pixel_color.x()) << ' '
        << static_cast<int>(255.999 * pixel_color.y()) << ' '
        << static_cast<int>(255.999 * pixel_color.z()) << '\n';
=======
>>>>>>> 5da39af0524b969c646ee7c5731281e92d2d9a8f
    
}

#endif