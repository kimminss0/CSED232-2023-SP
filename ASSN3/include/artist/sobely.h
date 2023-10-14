#ifndef SOBELY_H_
#define SOBELY_H_

#include "artist.h"

class sobely : public artist {
 public:
  /** constructor */
  sobely(int width, int height, const std::vector<int> &image)
      : artist{width, height, image} {}

  char mapper(int, int) override;
};

#endif