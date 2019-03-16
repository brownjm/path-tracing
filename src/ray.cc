#include "ray.h"

Ray::Ray(Vector3D orig, Vector3D dest, bool act)
  :origin(orig), direction(dest), active(act) {}


std::ostream& operator<<(std::ostream& os, const Ray& ray) {
  std::cout << "Ray(" << ray.origin << "->" << ray.direction << ", " << ray.active << ")";
  return os;
}
