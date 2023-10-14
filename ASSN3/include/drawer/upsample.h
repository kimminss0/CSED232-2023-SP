#ifndef UPSAMPLE_H_
#define UPSAMPLE_H_

#include <string>

#include "drawer.h"

class upsample : public drawer {
 public:
  /** constructor */
  upsample(artist *style) : drawer{style} {};

  std::string draw() override;
};

#endif