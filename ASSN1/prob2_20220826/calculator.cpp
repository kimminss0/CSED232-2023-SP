/**
 * @file calculator.cpp
 * @author 20220826 김민서
 */
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>

namespace calculator {

float sum(float a, float b) { return a + b; }
float sub(float a, float b) { return a - b; }
float mul(float a, float b) { return a * b; }
float div(float a, float b) { return a / b; }
float sqrt(float a) { return std::sqrtf(a); }
float square(float a) { return std::powf(a, 2); }

}  // namespace calculator

int main() {
  /* read operator type from user */
  char opReaded[7];
  std::cin >> opReaded;
  std::string op(opReaded);

  float a, b, calced;

  /* read operands from user and calculate result */
  if (op == "+") {
    std::cin >> a >> b;
    calced = calculator::sum(a, b);
  } else if (op == "-") {
    std::cin >> a >> b;
    calced = calculator::sub(a, b);
  } else if (op == "*") {
    std::cin >> a >> b;
    calced = calculator::mul(a, b);
  } else if (op == "/") {
    std::cin >> a >> b;
    calced = calculator::div(a, b);
  } else if (op == "sqrt") {
    std::cin >> a;
    calced = calculator::sqrt(a);
  } else if (op == "square") {
    std::cin >> a;
    calced = calculator::square(a);
  } else {
    std::cout << "Invalid operator" << std::endl;
    return 1;  // terminate with error
  }

  /* set precision of prompting result */
  const float delta = 0.0001f;
  int precision = std::fabs(calced - static_cast<int>(calced)) < delta ? 0 : 3;

  /* prompt result */
  std::cout << std::fixed << std::setprecision(precision)
            << std::round(calced * 1e3) / 1e3 << std::endl;
  return 0;
}