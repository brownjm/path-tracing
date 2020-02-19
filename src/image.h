#ifndef IMAGE_H_
#define IMAGE_H_

#include <vector>
#include <string>

#include "color.h"


class Image {
public:
  Image(int width, int height, std::vector<Color> pixels);
  void write(const std::string& filename);

private:
  int width, height;
  std::vector<Color> pixels;
};


#endif // IMAGE_H_
