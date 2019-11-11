#include "tracer.h"
#include "hit.h"
#include "ray.h"
#include "vector3d.h"
#include "sphere.h"
#include "camera.h"
#include "color.h"
#include "timer.h"
#include "random.h"

#include <iostream>
#include <iomanip>

Hit find_nearest_object(const std::vector<Sphere> world, const Ray& ray) {
  Hit closest = Hit(false, 1e100, Vector3D(0,0,0), Vector3D(0,0,0), &world[0]);
  for (auto& s : world) {
    Hit hit = s.intersect(ray);
    if ((hit.hit == true) && (hit.time < closest.time)) {
      closest = hit;
    }
  }
  return closest;
}

Color trace_path(const std::vector<Sphere>& world, const Ray& ray, int max_depth) {
  if (max_depth == 0) {
    return Black;
  }
  
  Hit hit = find_nearest_object(world, ray);
  if (hit.hit == false) {
    return Black; // ambient
  }

  Ray scattered = hit.surface->material(ray, hit);
  Color color = hit.surface->color;
  if (scattered.active == false) {
    return color;
  }

  return trace_path(world, scattered, max_depth-1) * color;
}

std::vector<Color> trace_scene(const std::vector<Sphere>& world, const Camera& camera,
                               int width, int height, int samples, int max_depth,
                               bool print_status) {
  std::vector<Color> colors(width*height);

  Timer timer;
  if (print_status) {
    std::cout << "Started: " << timer.timestamp() << "\n";
  }

  for (int n = 0; n < samples; ++n) {
    int percentage = int(double(n) / samples * 100);
    if (print_status) {
      std::cout << "\r" << "Progress: " << std::setw(3) << percentage << "%" << std::flush;
    }
    
    for (int i = 0; i < height; ++i) {
      for (int j = 0; j < width; ++j) {
	double x = double(j + Random::zero_to_one()) / (width-1);
        double y = double(i + Random::zero_to_one()) / (height-1);
	Ray ray = camera.compute_ray(x, y);
	colors[i*width + j] += trace_path(world, ray, max_depth);
      }
    }
  }

  for (auto& c : colors) {
    c /= samples;
  }

  if (print_status) {
    std::cout << "\r" << "Progress: " << "100%" << "\n";
    std::cout << "Ended:   " << timer.timestamp() << "\n";
    std::cout << "Elapsed: " << timer.elapsed() << "\n";
  }
  
  return colors;
}
