#ifndef TRACER_H_
#define TRACER_H_


#include "hit.h"
#include "vector3d.h"
#include "color.h"
#include <vector>



class Sphere;
class Ray;
class Camera;

Hit first_hit(const std::vector<Sphere>& world, const Ray& ray);

Color trace_path(const std::vector<Sphere>& world, const Ray& ray, int max_depth);

std::vector<Color> trace_scene(const std::vector<Sphere>& world, const Camera& camera,
			       int width, int height, int samples, int max_depth,
                               bool print_status=true);


#endif // TRACER_H_
