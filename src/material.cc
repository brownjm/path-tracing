#include "material.h"
#include "ray.h"
#include "hit.h"
#include "vector3d.h"
#include "random.h"

Ray diffuse(const Ray&, const Hit& hit) {
  Vector3D scattered = (hit.normal + Vector3D::random()).unit();
  return Ray(hit.point, scattered);
}

Ray specular(const Ray& ray, const Hit& hit) {
  Vector3D reflected = reflect(ray.direction, hit.normal);
  return Ray(hit.point, reflected);
}

Ray glass(const Ray& ray, const Hit& hit) {
  auto direction = ray.direction;
  auto normal = hit.normal;
  double n1 = 1.0;
  double n2 = 1.5;
  if (direction.dot(normal) > 0) { // inside sphere
    normal *= -1;
    std::swap(n1, n2);
  }

  double cos_theta = -direction.dot(normal);
  double schlick_probability = schlick(cos_theta, n1 / n2);

  if (Random::zero_to_one() < schlick_probability) {
    Vector3D reflected = reflect(direction, normal);
    return Ray(hit.point, reflected);
  }
  else {
    Vector3D refracted = refract(direction, normal, n1 / n2);
    return Ray(hit.point, refracted);
  }
}

Ray light(const Ray&, const Hit&) {
  return Ray(Vector3D(), Vector3D(), false);
}

Vector3D refract(const Vector3D& v, const Vector3D& normal, double index_ratio) {
  Vector3D vec = v.unit();
  double cos_theta = -normal.dot(vec);
  double discriminant = 1.0 - std::pow(index_ratio, 2) * (1 - std::pow(cos_theta, 2));
  if (discriminant >= 0) {
    return index_ratio * vec + (index_ratio * cos_theta - std::sqrt(discriminant)) * normal;
  }
  else return reflect(vec, normal);
}

Vector3D reflect(const Vector3D& v, const Vector3D& normal) {
  return v - (2 * v.dot(normal)) * normal;
}

double schlick(double cos_theta, double index_ratio) {
  double r0 = std::pow((1 - index_ratio) / (1 + index_ratio), 2);
  return r0 + (1 - r0) * std::pow(1 - cos_theta, 5);
}
