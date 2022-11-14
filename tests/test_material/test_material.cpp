#include <iostream>
#include <fstream>
#include "../../include/tracey/tracey.hpp"

const double infinity = std::numeric_limits<double>::infinity();

Vector3f RayColor(Tracey::Ray& r) {
  Vector3f unit = r.get_direction().normalized();
  float t = 0.5 * (unit(1) + 1.0);
  return (1.0 - t) * Vector3f(1.0, 1.0, 1.0) + t * Vector3f(0.5, 0.7, 1.0);
}

int main() {

    // Image
    std::ofstream out("out.ppm");
    // Image
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);

    // Camera

    auto viewport_height = 2.0;
    auto viewport_width = aspect_ratio * viewport_height;
    auto focal_length = 1.0;

    Vector3f origin = Vector3f(0, 0, 0);
    Vector3f horizontal = Vector3f(viewport_width, 0, 0);
    Vector3f vertical = Vector3f(0, viewport_height, 0);
    Vector3f lower_left_corner = origin - horizontal/2 - vertical/2 - Vector3f(0, 0, focal_length);

    // Render

    out << "P3\n" << image_width << ' ' << image_height << "\n255\n";


    for (int j = image_height-1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            //Vector3f pixel_color(float(i)/(image_width-1), float(j)/(image_height-1), 0.25);
            //wirte_color(out, pixel_color);
            for (int i = 0; i < image_width; ++i) {
            float u = float(i) / (image_width-1);
            float v = float(j) / (image_height-1);
            Vector3f test_p=lower_left_corner + u*horizontal + v*vertical - origin;
            Tracey::Ray r(origin, test_p);
            Vector3f pixel_color = RayColor(r);
            wirte_color(out, pixel_color);
        }
            /*auto r = double(i) / (image_width-1);
            auto g = double(j) / (image_height-1);
            auto b = 0.25;

            int ir = static_cast<int>(255.999 * r);
            int ig = static_cast<int>(255.999 * g);
            int ib = static_cast<int>(255.999 * b);

            out << ir << ' ' << ig << ' ' << ib << '\n';
            */
        }
    }
}