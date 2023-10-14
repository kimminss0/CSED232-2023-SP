#include "drawer/upsample.h"

#include <string>

using std::string;

string upsample::draw() {
  // get width, height of the image
  const int width = style->get_width();
  const int height = style->get_height();

  // build a result
  string result{};
  for (int h = 0; h < 2 * height; ++h) {
    for (int w = 0; w < 2 * width; ++w) {
      result += style->mapper(w / 2, h / 2);
    }
    result += '\n';
  }
  return result;
}
