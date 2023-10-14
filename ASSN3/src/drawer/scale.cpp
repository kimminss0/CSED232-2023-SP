#include "drawer/scale.h"

#include <stdexcept>
#include <string>

using std::string;

string scale::draw() {
  if (scale_x == 0 || scale_y == 0) {
    throw std::invalid_argument("scale factor must be nonzero");
  }

  // get width, height of the image
  const int width = style->get_width();
  const int height = style->get_height();

  // calculate a result
  string result{};
  for (int h = 0; h < (scale_y > 0 ? scale_y : 1) * height;
       h += (scale_y > 0 ? 1 : -scale_y)) {
    for (int w = 0; w < (scale_x > 0 ? scale_x : 1) * width;
         w += (scale_x > 0 ? 1 : -scale_x)) {
      result += style->mapper((scale_x > 0 ? w / scale_x : w),
                              (scale_y > 0 ? h / scale_y : h));
    }
    result += '\n';
  }
  return result;
}
