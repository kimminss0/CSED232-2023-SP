#ifndef GRADIENT_H_
#define GRADIENT_H_

#include "artist.h"

class gradient : public artist {
 public:
  /** constructor */
  gradient(int width, int height, const std::vector<int> &image)
      : artist{width, height, image} {}

  char mapper(int, int) override;
};

#endif