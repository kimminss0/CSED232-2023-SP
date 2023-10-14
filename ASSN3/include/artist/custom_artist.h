#ifndef CUSTOM_ARTIST_H_
#define CUSTOM_ARTIST_H_

#include "artist.h"

class custom_artist : public artist {
 private:
  static const char decorator[3];

 public:
  /** constructor */
  custom_artist(int width, int height, const std::vector<int> &image)
      : artist{width, height, image} {}

  char mapper(int, int) override;
};

#endif