#include <iostream>
#include <fstream>
#include "../../include/tracey/tracey.hpp"
<<<<<<< HEAD

/*
float hit_sphere(const Vector3f& center, float radius, const Tracey::Ray& r) {
    Vector3f oc = r.get_origin() - center;
    auto a = r.get_direction().squaredNorm();
    //auto b = 2.0 * (oc.dot(r.get_direction()));
    auto half_b=oc.dot(r.get_direction());
    //auto c = oc.dot(oc) - radius*radius;
    auto c=oc.squaredNorm()-radius*radius;
    //auto discriminant = b*b - 4*a*c;
    auto discriminant = half_b*half_b - a*c;
    if(discriminant<0){
        return -1.0;
    }else{
        return (-half_b - sqrt(discriminant) ) / a;
    }
}

Vector3f RayColor(Tracey::Ray& r) {
    auto t=hit_sphere(Vector3f(0,0,-1), 0.5, r);
    if(t>0.0){
        Vector3f N=(r.at(t)-Vector3f(0,0,-1)).normalized();
        return 0.5*Vector3f(N.x()+1, N.y()+1, N.z()+1);
    }
  Vector3f unit = r.get_direction().normalized();
  t = 0.5 * (unit.y() + 1.0);
  return (1.0 - t) * Vector3f(1.0, 1.0, 1.0) + t * Vector3f(0.5, 0.7, 1.0);
}*/

const double infinity = std::numeric_limits<double>::infinity();

/*Vector3f RayColor(const Tracey::Ray& r, const Tracey::Geometry& scene, int depth) {
  Tracey::Hit_Record rec;
  //Tracey::HitRecord rec;
  if(depth<=0)
    return Vector3f(0,0,0);

  if (scene.intersect(r, 0, infinity, rec)) {
    Vector3f target = rec.p+ rec.normal + Tracey::RandomInUnitSphere();
    return 0.5 * RayColor(Tracey::Ray(rec.p, target - rec.p), scene, depth-1);
  }

  Vector3f unit = r.get_direction().normalized();
  float t = 0.5 * (unit.y() + 1.0);
  return (1.0 - t) * Vector3f(1.0, 1.0, 1.0) + t * Vector3f(0.5, 0.7, 1.0);
}
*/
//, int depth
Vector3f RayColor(const Tracey::Ray& r, const Tracey::Geometry& scene) {
  Tracey::Hit_Record rec;
  /*
  if(depth<=0){
    return Vector3f(0,0,0);
  }
 */
  if (scene.intersect(r, 0, infinity, rec)) {
    return 0.5 * (rec.normal + Vector3f(1.0, 1.0, 1.0));
    //Vector3f target = rec.p + rec.normal + Tracey::RandomInUnitSphere();
    //return 0.5 * RayColor(Tracey::Ray(rec.p, target - rec.p), scene,depth-1);
=======
#include "../../include/tracey/ray/sphere.hpp"
#include "../../include/tracey/ray/hittable_list.hpp"

//, int depth
const double infinity = std::numeric_limits<double>::infinity();
Vector3f RayColor(const Tracey::Ray& r, const Tracey::Hittable& scene,int depth) {
  Tracey::HitRecord rec;
  if(depth<=0){
    return Vector3f(0,0,0);
  }
  if (scene.Hit(r, 0.001, infinity, rec)) {
    //return 0.5 * (rec.normal + Vector3f(1.0, 1.0, 1.0));
    Vector3f target = rec.point + rec.normal + Tracey::RandomInUnitSphere().normalized();
    return 0.5 * RayColor(Tracey::Ray(rec.point, target - rec.point), scene,depth-1);
>>>>>>> 5da39af0524b969c646ee7c5731281e92d2d9a8f
  }
  Vector3f unit = r.get_direction().normalized();
  float t = 0.5 * (unit.y() + 1.0);
  return (1.0 - t) * Vector3f(1.0, 1.0, 1.0) + t * Vector3f(0.5, 0.7, 1.0);
}

int main() {

    // Image
    std::ofstream out("out.ppm");
    // Image
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int samples_per_pixel=100;
    const int max_depth = 50;

    // Camera

/*    auto viewport_height = 2.0;
    auto viewport_width = aspect_ratio * viewport_height;
    auto focal_length = 1.0;

    Vector3f origin = Vector3f(0, 0, 0);
    Vector3f horizontal = Vector3f(viewport_width, 0, 0);
    Vector3f vertical = Vector3f(0, viewport_height, 0);
    Vector3f lower_left_corner = origin - (horizontal/2) - (vertical/2) - Vector3f(0, 0, focal_length);
*/

  //Tracey::Camera cam(image_width, aspect_ratio * image_width, 60.0);
    // Render
<<<<<<< HEAD
  Tracey::GeometryList scene;
  scene.add(std::make_shared<Tracey::Sphere>(Vector3f(0.0, 0.0, -1), 0.5));
  scene.add(std::make_shared<Tracey::Sphere>(Vector3f(0.0, -100.5, -1), 100));
=======
  Tracey::HittableList scene;
  scene.add(std::make_shared<Tracey::sphere>(Vector3f(0.0, 0.0, -1), 0.5));
  scene.add(std::make_shared<Tracey::sphere>(Vector3f(0.0, -100.5, -1), 100));

>>>>>>> 5da39af0524b969c646ee7c5731281e92d2d9a8f

    out << "P3\n" << image_width << ' ' << image_height << "\n255\n";


    for (int j = image_height-1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
<<<<<<< HEAD
            float u=float(i)/(image_width-1);
            float v=float(j)/(image_height-1);
            Vector3f origin(0, 0, 0);
            float viewport_height=2.0;
            float viewport_width=aspect_ratio * viewport_height;
            
            Vector3f horizontal(viewport_width, 0.0, 0.0);
            Vector3f vertical(0.0, viewport_height, 0.0);
            Vector3f lower_left_corner=origin - (horizontal/2) - (vertical/2) - Vector3f(0,0,1.0);
            Tracey::Ray r(origin, lower_left_corner + u*horizontal + v*vertical);
            Vector3f pixel_color = RayColor(r, scene);
            wirte_color(out, pixel_color,samples_per_pixel);
            /*Vector3f pixel_color(0,0,0);
           // for(int s=0;s<samples_per_pixel;++s){
                float u=(i+(rand() / (RAND_MAX + 1.0)))/(image_width-1);
                float v=(j+(rand() / (RAND_MAX + 1.0)))/(image_height-1);
=======
            Vector3f pixel_color(0,0,0);
            for(int s=0;s<samples_per_pixel;++s){
                float u=(i+(rand() / (RAND_MAX + 1.0)))/(image_width-1);
                float v=(j+(rand() / (RAND_MAX + 1.0)))/(image_height-1);
                //camera
>>>>>>> 5da39af0524b969c646ee7c5731281e92d2d9a8f
                Vector3f origin(0, 0, 0);
                float viewport_width=2.0;
                float viewport_height=1.0;
                Vector3f horizontal(viewport_width, 0.0, 0.0);
                Vector3f vertical(0.0, viewport_height, 0.0);
                Vector3f lower_left_corner=origin - (horizontal/2) - (vertical/2) - Vector3f(0,0,1.0);
<<<<<<< HEAD
                Tracey::Ray r(Vector3f(0.0, 0.0, 0.0), lower_left_corner + u*horizontal + v*vertical - origin);
                */
                //Tracey::Ray r=cam.get_direction(u,v);

                //pixel_color += RayColor(r, scene, max_depth);
           // }
            //wirte_color(out, pixel_color,samples_per_pixel);
=======
                Tracey::Ray r(origin, lower_left_corner + u*horizontal + v*vertical - origin);
                
                //Tracey::Ray r=cam.get_direction(u,v);
                //pixel_color = RayColor(r, scene, max_depth) ;
                pixel_color += RayColor(r, scene,max_depth);
            }
            wirte_color(out, pixel_color, samples_per_pixel);
>>>>>>> 5da39af0524b969c646ee7c5731281e92d2d9a8f
        } 
    }std::cerr << "\nDone.\n";
}