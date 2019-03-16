#include <random>
#include <iostream>
#include <functional>
#include "image.h"
#include "camera.h"
#include "material.h"
#include "vector3d.h"
#include "sphere.h"
#include "tracer.h"
#include "color.h"

#include "random.h"

int main() {
  const int width = 640;// 1600; // 640;
  const int height = 360; //900; // 360;
  const int samples = 1000;
  const int max_depth = 5;
  
  std::vector<Sphere> world = {// Walls
        		       //Sphere(Vector3D(2000, 0, 0), 1995, diffuse, White),
        		       //Sphere(Vector3D(-2000, 0, 0), 1995, diffuse, White),
        		       //Sphere(Vector3D(0, 2000, 0), 1990, diffuse, White),
        		       //Sphere(Vector3D(0, -2000, 0), 1990, diffuse, White),
        		       Sphere(Vector3D(0, 0, -2000), 2000, diffuse, White),
        		       //Sphere(Vector3D(0, 0, 2000), 1990, diffuse, White),
                               
                               
        		       // Spheres
                               //Sphere(Vector3D(0, -1.1, 1), 1, glass, Red),
        		       Sphere(Vector3D(2.2, -3, 2), 2, glass, White),
        		       //Sphere(Vector3D(-1, -2.5, 0.5), 0.5, glass, Lightgray),

        		       // Light
        		       // Sphere(Vector3D(-7, -7, 7), 4, light, White),
                               // Sphere(Vector3D(-5, 3, 5), 3, light, Color(0.7, 0.4, 0.2)),
                               Sphere(Vector3D(-100, -100, 100), 150, light, White),

  };


  Vector3D pos(0, -20, 4);
  Vector3D tar(0, 0, 1);
  Vector3D up(0, 0, 1);
  double fov = 20;
  double aspect = double(width) / height;
  Camera camera(pos, tar, up, fov, aspect);

  std::vector<Color> colors = trace_scene(world, camera, width, height, samples, max_depth);
  //std::vector<Color> colors = trace_scene(furnace, camera, width, height, samples, max_depth);
  
  Image img(height, width, colors);
  img.write("image.ppm");
}
