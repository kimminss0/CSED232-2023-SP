#include "parser/parser.h"

#include <exception>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using std::string;
using std::vector;

vector<int> parser::load_image(const char *path) {
  vector<int> image_seq{};
  std::ifstream image{};

  try {
    image.open(string{path});
    string s;
    std::getline(image, s);
    std::stringstream sstream(s);

    // get width and height of the image
    string w, h;
    std::getline(sstream, w, '|');
    std::getline(sstream, h, '|');
    if (image.fail()) {
      throw std::runtime_error(
          "Invalid image format: must contain width and height of image.");
    }

    // convert to integer and validate its range
    int width = std::stoi(w);
    int height = std::stoi(h);
    if (width <= 0 || height <= 0) {
      throw std::runtime_error(
          "Invalid image format: width and height must be positive.");
    }
    image_seq.reserve(width * height + 2);
    image_seq.push_back(width);
    image_seq.push_back(height);

    // read pixels and store to the vector
    int cnt{0};
    while (!sstream.eof()) {
      // read one pixel
      string px;
      std::getline(sstream, px, '|');
      if (sstream.fail()) {
        throw std::runtime_error("Invalid image format: invalid pixel format");
      }

      // convert to integer and validate its range
      int px_val = std::stoi(px);
      if (px_val < 0 || px_val > 255) {
        throw std::runtime_error(
            "Invalid image format: each pixel must be in range [0,255].");
      }

      // insert to the vector
      image_seq.push_back(px_val);
      ++cnt;
    }

    // validate the number of pixels match.
    if (cnt != width * height) {
      throw std::runtime_error(
          "Invalid image format: the number of pixels does not match with the "
          "image size.");
    }
  } catch (const std::exception &e) {
    std::cerr << e.what() << std::endl;
    if (image.is_open()) {
      image.close();
    }
    throw;
  }
  return image_seq;
}

vector<string> parser::load_config(const char *path) {
  vector<string> config_seq{};
  std::ifstream config_file{};

  try {
    config_file.open(string{path});
    string s;
    std::getline(config_file, s);
    std::stringstream sstream(s);

    while (!sstream.eof()) {
      // read a config str, separated by a delimeter '|'
      string sub_str;
      std::getline(sstream, sub_str, '|');
      if (sstream.fail()) {
        throw std::runtime_error(
            "Unexpected error: cannot parse the config string.");
      }
      config_seq.push_back(sub_str);
    }
    config_file.close();
  } catch (const std::exception &e) {
    std::cerr << e.what() << std::endl;
    if (config_file.is_open()) {
      config_file.close();
    }
    throw;
  }
  return config_seq;
}

void parser::write_result(const char *path, const string &img) {
  std::ofstream image_file{};
  try {
    image_file.open(path);
    image_file << img;
    image_file.close();
  } catch (...) {
    if (image_file.is_open()) {
      image_file.close();
    }
    throw;
  }
}