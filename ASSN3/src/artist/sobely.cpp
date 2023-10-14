#include "artist/sobely.h"

#include <cmath>
#include <stdexcept>

char sobely::mapper(int x, int y) {
  if (x < 0 || x >= width || y < 0 || y >= height) {
    throw std::invalid_argument(
        "Unexpected internal error: coordinate out of range.");
  }
  if (y == height - 1) {
    return ' ';
  }
  const int px_val = image[width * y + x];
  const int px_cmp = image[width * (y + 1) + x];
  return (abs(px_val - px_cmp) >= 50) ? '-' : ' ';
}