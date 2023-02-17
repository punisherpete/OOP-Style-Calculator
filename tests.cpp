#include "Calculator.hpp"

void Test1() {
  std::string expr = "1 + 2";
  int answer = 3;

  std::cout << (Calculator<decltype(answer)>::CalculateExpr(expr) == answer) << std::endl;
}

void Test2() {
  std::string expr = "1-2";
  int answer = -1;

  std::cout << (Calculator<decltype(answer)>::CalculateExpr(expr) == answer) << std::endl;
}

void Test3() {
  std::string expr = "2 * 5";
  int answer = 10;

  std::cout << (Calculator<decltype(answer)>::CalculateExpr(expr) == answer) << std::endl;
}

void Test4() {
  std::string expr = "5 / 2";
  int answer = 2;

  std::cout << (Calculator<decltype(answer)>::CalculateExpr(expr) == answer) << std::endl;
}

void Test5() {
  std::string expr = "1 + -2";
  int answer = -1;

  std::cout << (Calculator<decltype(answer)>::CalculateExpr(expr) == answer) << std::endl;
}

void Test6() {
  std::string expr = "1 + +2";
  int answer = 3;

  std::cout << (Calculator<decltype(answer)>::CalculateExpr(expr) == answer) << std::endl;
}

void Test7() {
  std::string expr = "5 * (10 - 2)";
  int answer = 40;

  std::cout << (Calculator<decltype(answer)>::CalculateExpr(expr) == answer) << std::endl;
}

void Test8() {
  std::string expr = "1.2+2.2";
  double answer = 3.4;

  std::cout << (Calculator<decltype(answer)>::CalculateExpr(expr) == answer) << std::endl;
}

void Test9() {
  std::string expr = "3 - 1.2";
  double answer = 1.8;

  std::cout << (Calculator<decltype(answer)>::CalculateExpr(expr) == answer) << std::endl;
}

void Test10() {
  std::string expr = "3 * 1.2";
  double answer = 3.6;

  std::cout << (Calculator<decltype(answer)>::CalculateExpr(expr) == answer) << std::endl;
}

void Test11() {
  std::string expr = "5 / 2";
  double answer = 2.5;

  std::cout << (Calculator<decltype(answer)>::CalculateExpr(expr) == answer) << std::endl;
}

void Test12() {
  std::string expr = "1.5 + -2";
  double answer = -0.5;

  std::cout << (Calculator<decltype(answer)>::CalculateExpr(expr) == answer) << std::endl;
}

void Test13() {
  std::string expr = "1.5 + +2";
  double answer = 3.5;

  std::cout << (Calculator<decltype(answer)>::CalculateExpr(expr) == answer) << std::endl;
}

void Test14() {
  std::string expr = "5.1 * (10.33 - 2.1)";
  double answer = 41.973;

  std::cout << (Calculator<decltype(answer)>::CalculateExpr(expr) == answer) << std::endl;
}

void Test15() {
  std::string expr = "((1 + (2 + (3 + (4 + (5))))))";
  int answer = 15;

  std::cout << (Calculator<decltype(answer)>::CalculateExpr(expr) == answer) << std::endl;
}


int main() {
  Test1();
  Test2();
  Test3();
  Test4();
  Test5();
  Test6();
  Test7();
  Test8();
  Test9();
  Test10();
  Test11();
  Test12();
  Test13();
  Test14();
  Test15();

  return 0;
}