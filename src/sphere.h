#ifndef SPHERE_H_
#define SPHERE_H_

#include <iostream>
#include <random>
#include <functional>

#include "ray.h"
#include "material.h"
#include "color.h"
#include "hit.h"

class Sphere {
public:
  Sphere(Vector3D center, double radius, Material material,
	 Color color);
	 
  Hit intersect(const Ray& ray) const;

  Vector3D center;
  double radius;
  Material material;
  Color color;
};






#endif // SPHERE_H_
