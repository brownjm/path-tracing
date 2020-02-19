#include "vector3d.h"
#include <iostream>

std::ostream& operator<<(std::ostream& os, const Vector3D& v) {
  os << "(" << v.x << " " << v.y << " " << v.z << ")";
  return os;
}

std::istream& operator>>(std::istream& is, Vector3D& v) {
  char paren;
  is >> paren >> v.x >> v.y >> v.z >> paren;
  return is;
}
