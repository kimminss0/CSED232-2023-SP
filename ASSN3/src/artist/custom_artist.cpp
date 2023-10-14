#include "artist/custom_artist.h"

#include <stdexcept>

const char custom_artist::decorator[3] = {'X', '.', ' '};

char custom_artist::mapper(int x, int y) {
  if (x < 0 || x >= width || y < 0 || y >= height) {
    throw std::invalid_argument(
        "Unexpected internal error: coordinate out of range.");
  }
  const int px_val = image[width * y + x];
  const int idx = (px_val == 255) ? 2 : px_val / 85;
  return decorator[idx];
}