#include <random>
#include <iostream>
#include <fstream>
#include <functional>
#include <mpi.h>
#include "image.h"
#include "camera.h"
#include "material.h"
#include "vector3d.h"
#include "sphere.h"
#include "tracer.h"
#include "color.h"
#include "random.h"

int main(int argc, char* argv[]) {
  MPI_Init(&argc, &argv);
  int rank, processors;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &processors);
  if (processors < 2) {
    std::cout << "Please launch program with at least 2 processors\n";
    return 1;
  }
  
  const int width = 1280;
  const int height = 720;
  const int samples = 50;
  const int max_depth = 5;
  
  std::vector<Sphere> world = {// Floor
        		       Sphere(Vector3D(0, 0, -2000), 2000, diffuse, White),
                               
        		       // Spheres
                               Sphere(Vector3D(0, -1.1, 1), 1, glass, Red),
        		       Sphere(Vector3D(2.5, -3, 2), 2, glass, White),
        		       Sphere(Vector3D(-1, -2.5, 0.5), 0.5, diffuse, Blue),
                               Sphere(Vector3D(0.3, -4, 0.3), 0.3, diffuse, Green),
                               // Sphere(Vector3D(0, -10, 1), 1, specular, Lightgray),
                               // Sphere(Vector3D(-3, -10, 1), 1, specular, White),

        		       // Light
                               Sphere(Vector3D(0, 100, 100), 100, light, White),
  };


  Vector3D pos(-5, -20, 4);
  Vector3D tar(0, 0, 1);
  Vector3D up(0, 0, 1);
  double fov = 20;
  double aspect = double(width) / height;
  Camera camera(pos, tar, up, fov, aspect);

  if (rank == 0) {
    bool print_status = true;
    std::vector<Color> colors = trace_scene(world, camera, width, height, samples, max_depth,
                                            print_status);
    int N = width*height*3;
    std::vector<double> values(N);

    for (int p = 1; p < processors; ++p) {
      MPI_Recv(values.data(), N, MPI_DOUBLE, p, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      for (int i = 0; i < N; i += 3) {
        double r = values[i+0];
        double g = values[i+1];
        double b = values[i+2];
        colors[i/3] += Color(r, g, b);
      }
    }

    for (auto& c : colors) {
      c /= processors;
    }
    
    Image img(height, width, colors);
    img.write("image.ppm");
  }
  else {
    bool print_status = false;
    std::vector<Color> colors = trace_scene(world, camera, width, height, samples, max_depth,
                                            print_status);
    int N = width*height*3;
    std::vector<double> values(N);
    for (int i = 0; i < N; i += 3) {
      values[i+0] = colors[i/3].x;
      values[i+1] = colors[i/3].y;
      values[i+2] = colors[i/3].z;
    }
    MPI_Send(values.data(), N, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
  }
  
  MPI_Finalize();
}
