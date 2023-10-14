#ifndef DRAWER_H_
#define DRAWER_H_

#include <string>

#include "artist/artist.h"

class drawer {
 protected:
  artist *const style;

 public:
  /** constructor */
  drawer(artist *_style) : style(_style) {}

  /** destructor */
  virtual ~drawer();

  // to prevent accidental copying
  // which cause a shllow copy of member 'style'
  drawer(const drawer &) = delete;

  drawer &operator=(const drawer &) = delete;

  virtual std::string draw();
};

#endif