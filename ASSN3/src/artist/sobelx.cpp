#include "artist/sobelx.h"

#include <cmath>
#include <stdexcept>

char sobelx::mapper(int x, int y) {
  if (x < 0 || x >= width || y < 0 || y >= height) {
    throw std::invalid_argument(
        "Unexpected internal error: coordinate out of range.");
  }
  if (x == width - 1) {
    return ' ';
  }
  const int px_val = image[width * y + x];
  const int px_cmp = image[width * y + x + 1];
  return (abs(px_val - px_cmp) >= 50) ? '|' : ' ';
}