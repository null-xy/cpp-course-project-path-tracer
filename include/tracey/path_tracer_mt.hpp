#pragma once

#include <Eigen/Dense>
#include <algorithm>
#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

#include "camera.hpp"
#include "geometry/geometry.hpp"
#include "geometry/geometry_list.hpp"
#include "ray/color.hpp"
#include "result.hpp"
#include "scene.hpp"

namespace Tracey {

class PathTracerMT {
public:
  static void render(Result &result, Scene &scene) {
    int nthreads = std::thread::hardware_concurrency() ?: 1;
    std::cout << "Using multithreaded path tracer" << std::endl;
    std::cout << nthreads << " concurrent threads possible" << std::endl;

    Tracey::Camera camera = scene.get_camera();
    int w = camera.get_width();
    int h = camera.get_height();
    size_t N = w * h;
    std::vector<Vector3d> pixel_colors(N);

    auto start = std::chrono::system_clock::now();
    int nbatches = nthreads;
    int batch_size = N / nbatches;
    std::cout << "Image size N = " << N << std::endl;
    std::cout << "Rendering image in " << nbatches
              << " batches, batch size = " << batch_size << " ..." << std::endl;

    std::vector<std::thread> threads;
    for (int batch_num = 0; batch_num < nbatches; batch_num++) {
      size_t sidx = batch_size * batch_num;
      size_t eidx = batch_size * (batch_num + 1);
      eidx = std::min(eidx, N);
      std::cout << "batch " << batch_num << " range: [" << sidx << ", " << eidx
                << "]" << std::endl;

      threads.push_back(
          std::thread([sidx, eidx, &result, &scene, &pixel_colors]() {
            int samples_per_pixel = result.get_samples();
            Tracey::GeometryList list = scene.get_geometries();
            Tracey::Camera camera = scene.get_camera();
            int w = camera.get_width();
            int h = camera.get_height();
            int max_depth = 50;
            Vector3d background(0.0, 0.0, 0.0);

            for (size_t i = sidx; i < eidx; i++) {
              Vector3d pixel_color(0.0, 0.0, 0.0);
              Tracey::Ray r = camera.get_direction(i % w, h - i / w);
              for (int s = 0; s < samples_per_pixel; ++s) {
                pixel_color += Tracey::RayColor(r, background, list, max_depth);
              }
              pixel_colors[i] = pixel_color;
            }
          }));
    }

    std::for_each(threads.begin(), threads.end(),
                  [](std::thread &t) { t.join(); });

    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << "Image rendered in " << elapsed_seconds.count() << " seconds"
              << std::endl;

    std::cout << "Updating image ..." << std::endl;
    std::vector<std::vector<Vector3d>> image;
    size_t idx = 0;
    for (int j = 0; j < h; j++) {
      std::vector<Vector3d> pixelRow;
      for (int i = 0; i < w; i++) {
        pixelRow.push_back(pixel_colors[idx]);
        idx += 1;
      }
      image.push_back(pixelRow);
    }
    result.update_image(image);
    std::cerr << "Done" << std::endl;
  }
};

} // namespace Tracey
