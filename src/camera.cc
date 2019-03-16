#include "camera.h"
#include <cmath>


std::tuple<Vector3D, Vector3D, Vector3D> camera_frame(const Vector3D& eye,
						      const Vector3D& target,
						      const Vector3D& up) {
  Vector3D w = (eye - target).unit();
  Vector3D u = up.cross(w).unit();
  Vector3D v = w.cross(u);
  return std::tie(u, v, w);
}

Camera::Camera(Vector3D eye, Vector3D target, Vector3D up, double fov, double aspect)
  :eye(eye) {
  Vector3D u, v, w;
  std::tie(u, v, w) = camera_frame(eye, target, up);
  double theta = fov * M_PI / 180;
  double height = 2 * std::tan(theta / 2.0);
  double width = height * aspect;
  horizontal = width * u;
  vertical = height * v;
  Vector3D image_center = eye - w;
  corner = image_center - 0.5 * (horizontal - vertical);
}

Ray Camera::compute_ray(double s, double t) const {
  Vector3D point = corner + s * horizontal - t * vertical;
  Vector3D direction = (point - eye).unit();
  return Ray(eye, direction);
}
