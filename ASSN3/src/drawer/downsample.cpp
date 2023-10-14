#include "drawer/downsample.h"

#include <string>

using std::string;

string downsample::draw() {
  // get width, height of the image
  const int width = style->get_width();
  const int height = style->get_height();

  // build a result
  string result{};
  for (int h = 0; h < height; h += 2) {
    for (int w = 0; w < width; w += 2) {
      result += style->mapper(w, h);
    }
    result += '\n';
  }
  return result;
}