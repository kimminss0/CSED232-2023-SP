#ifndef STUDENT_DATABASE_H_
#define STUDENT_DATABASE_H_

#include <iostream>
#include <string>

#include "aggregator.hpp"
#include "dept.hpp"
#include "list.hpp"
#include "student.hpp"

/** Enum for indicating which column to be grouped by in pivot operation */
enum class PivotColumn { Dept, Gender, DeptGender };

class StudentDatabase {
 private:
  /** list of dept data, contains dept name and # of students */
  List<Dept> dept_list;

  /** list of student data */
  List<Student> stu_list;

  /** comparator for sorting dept list */
  static int cmp_dept_(const Dept& lhs, const Dept& rhs);

  /** comparator for sorting student list */
  static int cmp_stu_(const Student& lhs, const Student& rhs);

  /**
   * @brief Find dept by given name
   *
   * @param dept_name dept name to search
   * @return pointer to the dept name |
   * @return nullptr if not found
   */
  Dept* find_dept(const std::string& dept_name) const;

  /**
   * @brief Check if the given student data exists in the list
   *
   * @param stu The student data to be checked
   * @return true if exists
   * @return false if not exists
   */
  bool is_stu_exists(const Student& stu) const;

  /** sort the dept list */
  void dept_sort() { dept_list.sort(cmp_dept_); }

  /** sort the student list */
  void stu_sort() { stu_list.sort(cmp_stu_); }

 public:
  /** Constructor */
  StudentDatabase() : dept_list{}, stu_list{} {}

  /**
   * @brief Save a student data into the list
   *
   * @param data The student data to be saved
   * @throw if the student already exists
   * @throw if the dept count exceeds 9
   * @throw if the student count of dept exceeds 10000
   */
  void save_node(const Student&);

  /**
   * @brief Delete a student data from the list
   *
   * @param data The student data to be deleted
   * @throw if the student does not exist
   */
  void delete_node(const Student&);

  /** Print the list of student data */
  void print_list();

  /**
   * @brief Execute pivot operation with given aggregator
   *
   * @param piv_col The column to be pivoted
   * @param agg The aggregator to be used
   */
  void pivot_table(const PivotColumn piv_col, Aggregator& agg);
};

#endif