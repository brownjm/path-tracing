#include "image.h"
#include "vector3d.h"

#include <fstream>

Image::Image(int numrows, int numcols, std::vector<Color> pix)
  :nrows(numrows), ncols(numcols), pixels(pix) {
}

void Image::write(const std::string& filename) {
  std::ofstream output(filename);
  if(!output) throw std::runtime_error("Cannot open output file: " + filename);
  output << "P3\n";
  output << ncols << " " << nrows << "\n";
  output << "255\n";
  for (int i = 0; i < nrows; ++i) {
    for (int j = 0; j < ncols; ++j) {
      Color c = 255*pow(pixels[ncols*i + j], 0.5);
      if (c.x > 255) c.x = 255;
      if (c.y > 255) c.y = 255;
      if (c.z > 255) c.z = 255;
      output << int(c.x) << " ";
      output << int(c.y) << " ";
      output << int(c.z) << " ";
    }
    output << "\n";
  }
}
