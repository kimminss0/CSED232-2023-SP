#include <iostream>
#include <string>

#include "util.hpp"

int util::get_menu_input(const int first, const int last) {
  int option;
  std::cout << "Selection: ";
  std::cin >> option;
  if (std::cin.fail()) {
    std::cin.clear();
    std::cin.ignore(LARGE_NUM, '\n');
    throw std::string("Invalid input");
  }
  if (option < first || option > last) {
    throw std::string("Invalid input");
  }
  return option;
}
