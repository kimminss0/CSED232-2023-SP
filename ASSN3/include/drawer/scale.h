#ifndef SCALE_H_
#define SCALE_H_

#include <string>

#include "drawer.h"

class scale : public drawer {
 private:
  int scale_x, scale_y;

 public:
  /** constructor */
  scale(artist *style, int _scale_x, int _scale_y)
      : drawer{style}, scale_x{_scale_x}, scale_y{_scale_y} {}

  std::string draw() override;
};

#endif