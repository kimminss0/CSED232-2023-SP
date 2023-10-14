#ifndef SOBELX_H_
#define SOBELX_H_

#include "artist.h"

class sobelx : public artist {
 public:
  /** constructor */
  sobelx(int width, int height, const std::vector<int> &image)
      : artist{width, height, image} {}

  char mapper(int, int) override;
};

#endif