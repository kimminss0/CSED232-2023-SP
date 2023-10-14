#ifndef STUDENT_H_
#define STUDENT_H_

#include <string>

/**
 * Represents a student in the student database.
 * Consists of dept, name, gender, and age.
 */
struct Student {
  std::string dept;
  std::string name;
  std::string gender;
  int age;

  Student(const std::string &dept_, const std::string &name_,
          const std::string &gender_, int age_)
      : dept{dept_}, name{name_}, gender{gender_}, age{age_} {}

  Student(const Student &rhs)
      : dept{rhs.dept}, name{rhs.name}, gender{rhs.gender}, age{rhs.age} {}

  bool operator==(const Student &rhs) const {
    return dept == rhs.dept && name == rhs.name && gender == rhs.gender &&
           age == rhs.age;
  }
};

#endif