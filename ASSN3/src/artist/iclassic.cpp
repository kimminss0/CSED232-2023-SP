#include "artist/iclassic.h"

#include <stdexcept>

const char iclassic::decorator[15] = {' ', '.', '-', '+', '^', '*', 'T', 'O',
                                      'H', 'A', 'X', 'W', '%', '&', '@'};

char iclassic::mapper(int x, int y) {
  if (x < 0 || x >= width || y < 0 || y >= height) {
    throw std::invalid_argument(
        "Unexpected internal error: coordinate out of range.");
  }
  const int px_val = image[width * y + x];
  const int idx = (px_val == 255) ? 14 : px_val / 17;
  return decorator[idx];
}