#include "sphere.h"
#include "hit.h"
#include "ray.h"

#include <cmath>


/*
  Intersection of ray and sphere is computed by time of intersection

  If ray and sphere intersect at time, then
  | ray(time) = center | = radius
  Squaring this equation gives
  a*time^2 + 2 * b * time + c = 0
  where
  a = |direction|^2 = 1
  b = direction.dot(temp)
  c = |temp|^2 - radius^2
  temp = origin - center

  The solutions are
  time = -b - sqrt(d) OR -b + sqrt(d)
  where d = b^2 - a * c
*/

Sphere::Sphere(Vector3D cen, double r, std::function<Ray(Ray, Hit)> mat, Color col)
  :center(cen), radius(r), material(mat), color(col) {}

Hit Sphere::intersect(const Ray& ray) const {
  const double EPSILON = 1e-4;
  Vector3D oc = ray.origin - center;
  double b = ray.direction.dot(oc);
  double c = oc.dot(oc) - std::pow(radius, 2);
  double d = pow(b, 2) - c;
  if (d < 0) {
    return Hit(false, 0, Vector3D(0,0,0), Vector3D(0,0,0), this);
  }

  double x = -b;
  double y = std::sqrt(d);
  double time = 0;
  if ((x - y) > EPSILON) {
    time = x - y;
  }
  else if ((x + y) > EPSILON) {
    time = x + y;
  }
  else {
    return Hit(false, 0, Vector3D(0,0,0), Vector3D(0,0,0), this);
  }

  Vector3D point = ray.origin + time * ray.direction;
  Vector3D normal = 1.0/radius * (point - center);
  return Hit(true, time, point, normal, this);
}

