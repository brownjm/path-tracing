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
#include "interpreter.h"

int main(int argc, char* argv[]) {
  if (argc < 2) {
    std::cout << "Please provide an input filename" << std::endl;
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
  
  std::vector<Color> colors = trace_scene(world, camera, width, height, samples, depth);
  
  Image img(width, height, colors);
  img.write(filename);
}
