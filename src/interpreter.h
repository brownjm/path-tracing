#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <map>

std::map<std::string, Material> materials = {{"diffuse", diffuse},
                                             {"specular", specular},
                                             {"light", light},
                                             {"glass", glass},
};

class Interpreter {
public:
  Interpreter(const std::string& filename);

  Camera get_camera();
  int rays_number, rays_depth;
  int image_width, image_height;
  std::string image_filename;
  std::vector<Sphere> objects;

private:
  Interpreter();
  void parse(std::ifstream& input);
  void parse_camera(const std::string& line);
  void parse_rays(const std::string& line);
  void parse_image(const std::string& line);
  void parse_object(const std::string& line);
  void verify();
  
  Vector3D camera_position, camera_target, up;
  double camera_fov, camera_aspect;
  bool found_camera, found_rays, found_image, found_objects;
};

std::string remove_comment(std::string line);
bool is_whitespace(const std::string& line);
bool is_type(const std::string& line, const std::string& type);

Interpreter::Interpreter(const std::string& filename)
  :up(Vector3D(0, 0, 1)) {
  std::ifstream input(filename);
  if(!input) {
    throw std::runtime_error("Cannot find file: " + filename);
  }
  parse(input);
  verify();
}

void Interpreter::parse(std::ifstream& input) {
  std::string line;
  while (std::getline(input, line)) {
    line = remove_comment(line);
    if (is_whitespace(line)) continue;

    if (is_type(line, "camera")) {
      parse_camera(line);
      found_camera = true;
    }
    else if (is_type(line, "rays")) {
      parse_rays(line);
      found_rays = true;
    }
    else if (is_type(line, "image")) {
      parse_image(line);
      found_image = true;
    }
    else if (is_type(line, "sphere")) {
      parse_object(line);
      found_objects = true;
    }
    else {
      std::cout << "Unknown type: " << line << std::endl;
    }
  }
}

void Interpreter::verify() {
  if (!found_camera) {
    std::cout << "Missing from file: camera" << std::endl;
  }
  if (!found_rays) {
    std::cout << "Missing from file: rays" << std::endl;
  }
  if (!found_image) {
    std::cout << "Missing from file: image" << std::endl;
  }
  if (!found_objects) {
    std::cout << "Missing from file: objects" << std::endl;
  }
}

void Interpreter::parse_camera(const std::string& line) {
  std::stringstream ss;
  ss << line;
  std::string camera;
  ss >> camera >> camera_position >> camera_target >> camera_fov;
}

void Interpreter::parse_rays(const std::string& line) {
  std::stringstream ss;
  ss << line;
  std::string rays;
  ss >> rays >> rays_number >> rays_depth;
}

void Interpreter::parse_image(const std::string& line) {
  std::stringstream ss;
  ss << line;
  std::string image;
  ss >> image >> image_width >> image_height >> image_filename;
  camera_aspect = static_cast<double>(image_width) / image_height;
}

void Interpreter::parse_object(const std::string& line) {
  std::stringstream ss;
  ss << line;
  std::string sphere;
  Vector3D position, color;
  double radius;
  std::string material;
  ss >> sphere >> position >> radius >> material >> color;

  auto i = materials.find(material);
  if (i != materials.end()) {
    objects.emplace_back(position, radius, i->second, color);
  }
  else {
    std::cout << "Unknown material: " << material << std::endl;
    std::cout << "Known materials: ";
    for (auto& m : materials) {
      std::cout << m.first << " ";
    }
    std::cout << std::endl;
  }
}

Camera Interpreter::get_camera() {
  return Camera(camera_position, camera_target, up, camera_fov, camera_aspect);
}

std::string remove_comment(std::string line) {
  auto i = line.find("//");
  if (i != std::string::npos) {
    line = line.substr(0, i);
  }
  return line;
}

bool is_whitespace(const std::string& line) {
  return std::all_of(std::begin(line), std::end(line), ::isspace);
}

bool is_type(const std::string& line, const std::string& type) {
  return line.find(type) == 0;
}

