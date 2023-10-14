#include "student_database.hpp"

#include <cmath>
#include <iostream>
#include <string>

#include "aggregator.hpp"
#include "util.hpp"

using std::string;

int StudentDatabase::cmp_dept_(const Dept &lhs, const Dept &rhs) {
  if (lhs.dept_name < rhs.dept_name) {
    return 1;
  } else if (lhs.dept_name > rhs.dept_name) {
    return -1;
  } else {
    return 0;
  }
}

int StudentDatabase::cmp_stu_(const Student &lhs, const Student &rhs) {
  // 1. Dept
  if (lhs.dept < rhs.dept) {
    return 1;
  } else if (lhs.dept > rhs.dept) {
    return -1;
  }

  // 2. Gender
  if (lhs.gender < rhs.gender) {
    return 1;
  } else if (lhs.gender > rhs.gender) {
    return -1;
  }

  // 3. Name
  if (lhs.name < rhs.name) {
    return 1;
  } else if (lhs.name > rhs.name) {
    return -1;
  }

  // 4. Age
  return rhs.age - lhs.age;
}

Dept *StudentDatabase::find_dept(const std::string &dept_name) const {
  for (Dept &x : dept_list) {
    if (x.dept_name == dept_name) {
      return &x;
    }
  }
  // Equivalent to the following code:
  // for (auto &&it = dept_list.begin(), &&end = dept_list.end(); it != end;
  //      ++it) {
  //   auto &x = *it;
  //   if (x.dept_name == dept_name) {
  //     return &x;
  //   }
  // }
  return nullptr;
}

bool StudentDatabase::is_stu_exists(const Student &stu) const {
  for (const Student &x : stu_list) {
    if (x == stu) {
      return true;
    }
  }
  // Equivalent to the following code:
  // for (auto &&it = stu_list.begin(), &&end = stu_list.end(); it != end; ++it)
  // {
  //   const auto &x = *it;
  //   if (x == stu) {
  //     return true;
  //   }
  // }
  return false;
}

void StudentDatabase::save_node(const Student &data) {
  /** find duplication from the list */
  if (is_stu_exists(data)) {
    throw string("The student already exists");
  }

  Dept *dept = find_dept(data.dept);

  /** check if max limit for dept exceeds */
  if (dept != nullptr) {
    if (dept_list.size() == 9) {
      throw string("max limit (9) for dept count has been exceeded");
    }
    if (dept->cnt == 10000) {
      throw string("max limit (10000) for student of dept has been exceeded");
    }
  }

  /** insert node into the list */
  stu_list.insert(data);
  if (dept == nullptr) {
    dept_list.insert(Dept{data.dept, 1});
  } else {
    ++dept->cnt;
  }
}

void StudentDatabase::delete_node(const Student &data) {
  /** check if there is a node to be deleted */
  if (!is_stu_exists(data)) {
    throw string("Can't Delete it");
  }

  /** delete node from the list */
  stu_list.remove(data);
  Dept *dept = find_dept(data.dept);
  --dept->cnt;
  if (dept->cnt == 0) {
    dept_list.remove(*dept);
  }
}

void StudentDatabase::print_list() {
  if (stu_list.size() == 0) {
    return;
  }

  // sort list before print
  stu_sort();

  std::cout << "Dept"
            << "\t"
            << "Gender"
            << "\t"
            << "Name"
            << "\t"
            << "Age" << std::endl;
  for (const Student &s : stu_list) {
    std::cout << s.dept << "\t" << s.gender << "\t" << s.name << "\t" << s.age
              << std::endl;
  }
}

void StudentDatabase::pivot_table(const PivotColumn piv_col, Aggregator &agg) {
  // check if the list is empty
  if (stu_list.size() == 0) {
    return;
  }
  std::cout << std::fixed;

  /**
   * execute group-by operation and perform
   * pivot with given aggregator
   */
  if (piv_col == PivotColumn::Dept) {
    /**
     * group by dept
     */
    std::cout << "Dept"
              << "\t" << agg.get_name() << std::endl;
    dept_sort();
    for (const Dept &dept : dept_list) {
      agg.init();  // reset aggregator
      const string &D = dept.dept_name;
      int cnt(0);

      // aggregate data
      for (const Student &stu : stu_list) {
        if (stu.dept == D) {
          agg.feed_data(stu.age);
          ++cnt;
        }
      }

      // print result
      if (cnt) {
        const double evaluated = agg.evaluate();
        if (std::fabs(int(evaluated) - evaluated) < 0.0001) {
          std::cout.precision(0);
        } else {
          std::cout.precision(1);
        }
        std::cout << D << "\t" << evaluated << std::endl;
      }
    }
  } else if (piv_col == PivotColumn::Gender) {
    /**
     * group by gender
     */
    std::cout << "Gender"
              << "\t" << agg.get_name() << std::endl;
    for (const string G : {"F", "M"}) {
      agg.init();  // reset aggregator
      int cnt(0);

      // aggregate data
      for (const Student &stu : stu_list) {
        if (stu.gender == G) {
          agg.feed_data(stu.age);
          ++cnt;
        }
      }

      // print result
      if (cnt) {
        const double evaluated = agg.evaluate();
        if (std::fabs(int(evaluated) - evaluated) < 0.0001) {
          std::cout.precision(0);
        } else {
          std::cout.precision(1);
        }
        std::cout << G << "\t" << evaluated << std::endl;
      }
    }
  } else if (piv_col == PivotColumn::DeptGender) {
    /**
     * group by (dept, gender)
     */
    std::cout << "Dept"
              << "\t"
              << "Gender"
              << "\t" << agg.get_name() << std::endl;
    dept_sort();
    for (const Dept &dept : dept_list) {
      const string &D = dept.dept_name;
      for (const string G : {"F", "M"}) {
        agg.init();  // reset aggregator
        int cnt(0);

        // aggregate data
        for (const Student &stu : stu_list) {
          if (stu.dept == D && stu.gender == G) {
            agg.feed_data(stu.age);
            ++cnt;
          }
        }

        // print result
        if (cnt) {
          const double evaluated = agg.evaluate();
          if (std::fabs(int(evaluated) - evaluated) < 0.0001) {
            std::cout.precision(0);
          } else {
            std::cout.precision(1);
          }
          std::cout << D << "\t" << G << "\t" << evaluated << std::endl;
        }
      }
    }
  } else {
    throw string("Invalid PivotColumn");
  }
}