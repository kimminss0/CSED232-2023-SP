#include "artist/gradient.h"

#include <cmath>
#include <stdexcept>

char gradient::mapper(int x, int y) {
  if (x < 0 || x >= width || y < 0 || y >= height) {
    throw std::invalid_argument(
        "Unexpected internal error: coordinate out of range.");
  }
  if (x == width - 1 || y == height - 1) {
    return ' ';
  }
  const int px_val = image[width * y + x];
  const int px_cmp_x = image[width * y + x + 1];
  const int px_cmp_y = image[width * (y + 1) + x];

  bool is_x_edge = abs(px_val - px_cmp_x) >= 50;
  bool is_y_edge = abs(px_val - px_cmp_y) >= 50;

  return (is_x_edge && is_y_edge) ? '+'
         : is_x_edge              ? '|'
         : is_y_edge              ? '-'
                                  : ' ';
}