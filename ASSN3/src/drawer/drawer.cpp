#include "drawer/drawer.h"

#include <string>

using std::string;

string drawer::draw() {
  // get width, height of the image
  const int width = style->get_width();
  const int height = style->get_height();

  // build a result
  string result{};
  for (int h = 0; h < height; ++h) {
    for (int w = 0; w < width; ++w) {
      result += style->mapper(w, h);
    }
    result += '\n';
  }
  return result;
}

drawer::~drawer() { delete style; }