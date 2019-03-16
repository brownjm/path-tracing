#ifndef CAMERA_H_
#define CAMERA_H_

#include <tuple>
#include "vector3d.h"
#include "ray.h"


std::tuple<Vector3D, Vector3D, Vector3D> camera_frame(const Vector3D& eye,
						const Vector3D& target,
						const Vector3D& up);

class Camera {
public:
  Camera(Vector3D eye, Vector3D target, Vector3D up, double fov, double aspect);

  Ray compute_ray(double s, double t) const;
  
  Vector3D eye, horizontal, vertical, corner;
};

#endif // CAMERA_H_
