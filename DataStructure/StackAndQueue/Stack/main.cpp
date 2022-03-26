/**
 * @file main.cpp
 * @author Be-A-God (wx1028674648@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-03-06
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "stack.hpp"

int main(int argc, char const *argv[]) {
  stack first_stack;
  std::cout.setf(std::ios_base::boolalpha);
  std::cout << "十进制转二进制：" << std::endl;
  first_stack.dec_to_bin(21);
  //   std::cout << "回文判断：" << first_stack.palindrome("asdsddda") <<
  //   std::endl;
  first_stack.push(44);
  first_stack.push(34);
  first_stack.push(24);
  first_stack.push(14);
  first_stack.push(4);
  std::cout << "栈空：" << first_stack.empty() << std::endl;
  std::cout << "栈的大小：" << first_stack.size() << std::endl;
  std::cout << "Pop：" << first_stack.pop() << std::endl;
  std::cout << "Top：" << first_stack.top() << std::endl;
  std::cout << "Pop：" << first_stack.pop() << std::endl;
  std::cout << "Top：" << first_stack.top() << std::endl;
  return 0;
}
