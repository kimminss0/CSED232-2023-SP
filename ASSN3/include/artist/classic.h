#ifndef CLASSIC_H_
#define CLASSIC_H_

#include "artist.h"

class classic : public artist {
 private:
  static const char decorator[15];

 public:
  /** constructor */
  classic(int width, int height, const std::vector<int> &image)
      : artist{width, height, image} {}

  char mapper(int, int) override;
};

#endif