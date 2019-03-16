#ifndef HIT_H_
#define HIT_H_

#include "vector3d.h"

class Sphere;

class Hit {
public:
  Hit(bool hit, double time, Vector3D point, Vector3D normal, const Sphere* surface)
    :hit(hit), time(time), point(point), normal(normal), surface(surface) {}

  bool hit;
  double time;
  Vector3D point, normal;
  const Sphere* surface;
};


#endif // HIT_H_
