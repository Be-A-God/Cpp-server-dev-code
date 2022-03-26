/**
 * @file stack.hpp
 * @author Be-A-God (wx1028674648@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-03-06
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <iostream>

struct dynamic_stack {
  int *base;
  int *top;
};

class stack {
 public:
  stack();
  explicit stack(const stack &other);
  stack(stack &&other);
  stack &operator=(const stack &other);
  stack &operator=(stack &&other);
  ~stack();
  void push(const int value);
  int size() const;
  bool empty() const;
  int pop();
  int top();
  void dec_to_bin(int dec);
  bool palindrome(const char *str);

 private:
  dynamic_stack my_stack;
  const int full_size{50};
};