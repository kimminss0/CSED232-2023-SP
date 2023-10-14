#ifndef DEPT_H_
#define DEPT_H_

#include <string>

/**
 * Represents a department in the student database.
 * Contains dept name and # of students.
 */
struct Dept {
  std::string dept_name;
  int cnt;

  Dept(const std::string& dept_name_, int cnt_)
      : dept_name{dept_name_}, cnt(cnt_) {}

  bool operator==(const Dept& rhs) const {
    return dept_name == rhs.dept_name && cnt == rhs.cnt;
  }
};

#endif