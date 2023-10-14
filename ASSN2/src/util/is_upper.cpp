#include <string>

#include "util.hpp"

using namespace std;

bool util::isupper(const std::string &s) {
  for (char v : s) {
    if (v < 'A' || v > 'Z') {
      return false;
    }
  }
  return true;
}