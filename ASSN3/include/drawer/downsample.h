#ifndef DOWNSAMPLE_H_
#define DOWNSAMPLE_H_

#include <string>

#include "drawer.h"

class downsample : public drawer {
 public:
  /** constructor */
  downsample(artist *style) : drawer{style} {}

  std::string draw() override;
};

#endif