#ifndef RAY_H_
#define RAY_H_

#include "vector3d.h"
#include <iostream>

class Ray {
public:
  Ray(Vector3D origin, Vector3D destination, bool active=true);
  
  Vector3D origin, direction;
  bool active;
};


std::ostream& operator<<(std::ostream& os, const Ray& ray);


#endif // RAY_H_
