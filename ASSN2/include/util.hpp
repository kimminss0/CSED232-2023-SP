#ifndef UTIL_H_
#define UTIL_H_

#include <string>

#include "student.hpp"
#define LARGE_NUM 10000

/**
 * Utility functions for the program.
 */
namespace util {

/**
 * @brief Check if a string is all upper case
 *        (A-Z), no numbers or special characters
 *
 * @param s string to check
 * @return true if all upper case
 * @return false if contains lower case
 */
bool isupper(const std::string &);

/**
 * @brief Get the user input object, validate the input
 *        is between 'first' and 'last'
 *
 * @param first
 * @param last
 * @return user input if valid
 * @throw if invalid input
 */
int get_menu_input(const int first, const int last);

/**
 * @brief Get the student info and validate
 *
 * @return constructed student object
 */
Student get_student_info();

}  // namespace util

#endif