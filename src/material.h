#ifndef MATERIAL_H_
#define MATERIAL_H_

class Ray;
class Hit;
class Vector3D;

Ray diffuse(const Ray& ray, const Hit& hit);
Ray specular(const Ray& ray, const Hit& hit);
Ray light(const Ray& ray, const Hit& hit);
Ray glass(const Ray& ray, const Hit& hit);
Vector3D refract(const Vector3D& vector, const Vector3D& normal, double index_ratio);
Vector3D reflect(const Vector3D& vector, const Vector3D& normal);
double schlick(double cos_theta, double index_ratio);



#endif // MATERIAL_H_
