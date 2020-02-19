#ifndef VECTOR3D_H_
#define VECTOR3D_H_

#include <random>
#include <iostream>
#include "random.h"

class Vector3D {
public:
  Vector3D()
    :x(0.0), y(0.0), z(0.0) {}

  Vector3D(double xx, double yy, double zz)
    :x(xx), y(yy), z(zz) {}
  
  Vector3D& operator+=(const Vector3D& rhs) {
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    return *this;
  }

  Vector3D& operator-=(const Vector3D& rhs) {
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
    return *this;
  }

  Vector3D& operator*=(const Vector3D& rhs) {
    x *= rhs.x;
    y *= rhs.y;
    z *= rhs.z;
    return *this;
  }
  
  Vector3D& operator*=(double s) {
    x *= s;
    y *= s;
    z *= s;
    return *this;
  }

  Vector3D& operator/=(double s) {
    x /= s;
    y /= s;
    z /= s;
    return *this;
  }
  
  double dot(const Vector3D& v) const {
    return x*v.x + y*v.y + z*v.z;
  }
  
  Vector3D cross(const Vector3D& v) const {
    return Vector3D(y*v.z - z*v.y, z*v.x - x*v.z, x*v.y - y*v.x);
  }
  
  double norm() const {
    return std::sqrt(x*x + y*y + z*z);
  }
  
  Vector3D unit() const {
    double n = norm();
    return Vector3D(x/n, y/n, z/n);
  }
  
  static Vector3D random() {
    Vector3D v;
    do {
    v = Vector3D(Random::neg_one_to_one(),
                 Random::neg_one_to_one(),
                 Random::neg_one_to_one());
    } while (v.dot(v) >= 1.0);

    return v.unit();
  }

  double x, y, z;

};


std::ostream& operator<<(std::ostream& os, const Vector3D& v);
std::istream& operator>>(std::istream& is, Vector3D& v);
  
inline Vector3D operator+(Vector3D lhs, const Vector3D& rhs) {
  lhs += rhs;
  return lhs;
}

inline Vector3D operator-(Vector3D lhs, const Vector3D& rhs) {
  lhs -= rhs;
  return lhs;
}

inline Vector3D operator*(Vector3D lhs, const Vector3D& rhs) {
  lhs *= rhs;
  return lhs;
}

inline Vector3D operator*(Vector3D lhs, double s) {
  lhs *= s;
  return lhs;
}

inline Vector3D operator*(double s, Vector3D v1) {
  return v1 * s;
}

inline Vector3D pow(const Vector3D& v, double n) {
  return Vector3D(std::pow(v.x, n), std::pow(v.y, n), std::pow(v.z, n));
}

#endif // VECTOR3D_H_
