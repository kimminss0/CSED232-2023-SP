#include <iostream>
#include <string>

#include "student.hpp"
#include "util.hpp"

using std::string;

Student util::get_student_info() {
  string dept, name, gender;
  int age;

  std::cin.ignore(LARGE_NUM, '\n');
  std::cout << "Dept: ";
  std::getline(std::cin, dept);
  std::cout << "Gender: ";
  std::getline(std::cin, gender);
  std::cout << "Name: ";
  std::getline(std::cin, name);
  std::cout << "Age: ";
  std::cin >> age;
  if (std::cin.fail()) {
    std::cin.clear();
    std::cin.ignore(10000, '\n');
    throw std::string("Invalid input");
  }

  for (const string& x : {dept, gender, name}) {
    bool is_space_contained(false);
    for (char c : x) {
      // check if the string contains a whitespace
      if (c == ' ') {
        is_space_contained = true;
        break;
      }
    }
    if (is_space_contained) {
      throw string(
          "Invalid input: dept, gender, name cannot contain a whitespace");
    }
  }

  if (!util::isupper(dept)) {
    throw string("Invalid input for dept: must be represented in uppercase");
  }

  if (gender != "M" && gender != "F") {
    throw string("Invalid input for gender: must be either M or F");
  }

  if (age < 18 || age > 30) {
    throw string("Invalid input for age: must be in range [18, 30]");
  }

  return Student{dept, name, gender, age};
}