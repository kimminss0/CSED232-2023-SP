/**
 * @file baseCalculator.cpp
 * @author 20220826 김민서
 */
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <string>

namespace base_calculator {

/**
 * @brief convert digit in string to integer
 *        valid for base 2 ~ 16
 * @param src digit in string
 * @param base base of src, must be 2 ~ 16
 * @return integer
 */
int convertBaseDigitToDecimalInt(char ch, int base);

/**
 * @brief convert number to decimal
 * @param src number of base within binary, octal, or hexadecimal, in string
 * format
 * @return decimal number in integer
 */
int convertToDecimal(std::string src);

/**
 * @brief calculate sum of two numbers
 * @param a first number
 * @param b second number
 * @return sum of a and b
 */
int sum(int a, int b);

/**
 * @brief calculate subtraction of two numbers
 * @param a first number
 * @param b second number
 * @return subtraction of a and b
 */
int sub(int a, int b);

/**
 * @brief calculate multiplication of two numbers
 * @param a first number
 * @param b second number
 * @return multiplication of a and b
 */
int mul(int a, int b);

/**
 * @brief calculate division of two numbers
 * @param a first number
 * @param b second number
 * @return division of a and b
 */
double div(int a, int b);

}  // namespace base_calculator

int base_calculator::convertBaseDigitToDecimalInt(char ch, int base) {
  int digitValue{-1};

  /* convert digit to integer */
  if (ch >= '0' && ch <= '9') {
    digitValue = ch - '0';
  } else if (ch >= 'A' && ch <= 'F') {
    digitValue = ch - 'A' + 10;
  }

  /* check if digit is valid for base */
  if (digitValue >= base) {
    std::cout << "Invalid input for operand: expected a base " << base
              << std::endl;
    exit(1);
  } else if (digitValue == -1) {
    std::cout << "Invalid format for digit: " << ch << std::endl;
    exit(1);
  }
  return digitValue;
}

int base_calculator::convertToDecimal(std::string src) {
  int base;                      // base of input number
  std::string followedByPrefix;  // input number without prefix

  /* parse the prefix of input */
  if (src.substr(0, 2) == "0X") {  // hexadecimal
    base = 16;
    followedByPrefix = src.substr(2);
  } else if (src.substr(0, 2) == "0b") {  // binary
    base = 2;
    followedByPrefix = src.substr(2);
  } else if (src.substr(0, 1) == "0") {  // octal
    base = 8;
    followedByPrefix = src.substr(1);
  } else {
    std::cout << "Invalid operand prefix: Must start with either 0X, 0b, 0"
              << std::endl;
    exit(1);
  }

  /* check if input contains at least one digit */
  if (followedByPrefix.size() == 0) {
    std::cout << "Invalid operand: Must contain at least one digit"
              << std::endl;
    exit(1);
  }

  /* convert to decimal */
  int accumulated{0};
  for (char ch : followedByPrefix) {
    int digitValue = convertBaseDigitToDecimalInt(ch, base);
    accumulated *= base;
    accumulated += digitValue;
  }
  return accumulated;
}

int base_calculator::sum(int a, int b) { return a + b; }

int base_calculator::sub(int a, int b) { return a - b; }

int base_calculator::mul(int a, int b) { return a * b; }

double base_calculator::div(int a, int b) { return double(a) / b; }

int main() {
  char op;
  std::string a, b;

  /* read operator, operand_1, operand_2 from user */
  std::cin >> op >> a >> b;

  /* check if operator is valid */
  bool validOp = false;
  for (char _op : {'+', '-', '*', '/'}) {
    if (op == _op) { validOp = true; }
  }
  if (!validOp) {
    std::cout << "Invalid input for operator" << std::endl;
    return 1;  // terminate with error
  }

  /* convert numbers into decimal */
  int a_converted = base_calculator::convertToDecimal(a);
  int b_converted = base_calculator::convertToDecimal(b);

  /* calculate result && prompt to user */
  if (op == '+') {
    std::cout << base_calculator::sum(a_converted, b_converted) << std::endl;
  } else if (op == '-') {
    std::cout << base_calculator::sub(a_converted, b_converted) << std::endl;
  } else if (op == '*') {
    std::cout << base_calculator::mul(a_converted, b_converted) << std::endl;
  } else if (op == '/') {
    /* set precision of prompting result */
    const double calced = base_calculator::div(a_converted, b_converted);
    const double DELTA = 0.0001;
    const int precision =
        std::fabs(calced - static_cast<int>(calced)) < DELTA ? 0 : 3;
    std::cout << std::fixed << std::setprecision(precision)
              << std::round(calced * 1e3) / 1e3 << std::endl;
  }
  return 0;
}