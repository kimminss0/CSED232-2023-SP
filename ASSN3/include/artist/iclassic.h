#ifndef ICLASSIC_H_
#define ICLASSIC_H_

#include "artist.h"

class iclassic : public artist {
 private:
  static const char decorator[15];

 public:
  /** constructor */
  iclassic(int width, int height, const std::vector<int> &image)
      : artist{width, height, image} {}

  char mapper(int, int) override;
};

#endif