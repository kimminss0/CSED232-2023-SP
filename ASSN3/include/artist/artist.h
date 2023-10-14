#ifndef ARTIST_H_
#define ARTIST_H_

#include <vector>

class artist {
 protected:
  const std::vector<int> image;
  const int width, height;

 public:
  /** constructor */
  artist(int _width, int _height, const std::vector<int> &_image)
      : image(_image), width{_width}, height{_height} {}

  /** destructor */
  virtual ~artist() {}

  virtual char mapper(int, int) = 0;

  int get_width(void) { return width; }
  int get_height(void) { return height; }
};
#endif