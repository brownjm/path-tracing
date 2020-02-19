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
#include "interpreter.h"

int main(int argc, char* argv[]) {
  MPI_Init(&argc, &argv);
  int rank, processors;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &processors);
  
  if (processors < 2) {
    std::cout << "Please launch program with at least 2 processors\n";
    MPI_Finalize();
    return 1;
  }

  if (argc < 2) {
    if (rank == 0) {
      std::cout << "Please provide an input filename" << std::endl;
    }
    MPI_Finalize();
    return 1;
  }

  Interpreter interpreter(argv[1]);
  Camera camera = interpreter.get_camera();
  int width = interpreter.image_width;
  int height = interpreter.image_height;
  int samples = interpreter.rays_number;
  int depth = interpreter.rays_depth;
  std::string filename = interpreter.image_filename;
  std::vector<Sphere>& world = interpreter.objects;

  if (rank == 0) {
    bool print_status = true;
    std::vector<Color> colors = trace_scene(world, camera, width, height, samples, depth,
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
    
    Image img(width, height, colors);
    img.write(filename);
  }
  else {
    bool print_status = false;
    std::vector<Color> colors = trace_scene(world, camera, width, height, samples, depth,
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
