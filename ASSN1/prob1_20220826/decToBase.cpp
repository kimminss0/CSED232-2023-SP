/**
 * @file decToBase.cpp
 * @author 20220826 김민서
 */
#include <iostream>
#include <string>

using std::string;

namespace base_converter {
string decToBase(const int src, const int base) {
  int reducer = src;
  string accumulator = "";
  while (reducer) {
    const int remainder = reducer % base;
    reducer /= base;

    /* the following works well for both base < 10 && base > 10 */
    const char digit =
        (remainder < 10 ? '0' + remainder : 'A' + remainder - 10);
    accumulator = digit + accumulator;
  }
  return accumulator;
}
}  // namespace base_converter

int main(void) {
  int src;
  int baseTarget;

  /* read a decimal number to be converted and target base */
  std::cin >> src >> baseTarget;

  /* convert the number to the target base */
  switch (baseTarget) {
    case 2:  // fall through
    case 8:  // fall through
    case 16:
      std::cout << base_converter::decToBase(src, baseTarget) << std::endl;
      break;
    default:
      std::cout << "Invalid target base" << std::endl;
      return 1;
  }
}