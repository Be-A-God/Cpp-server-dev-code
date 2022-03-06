/**
 * @file stack.cpp
 * @author Be-A-God (wx1028674648@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-03-06
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "stack.hpp"

#include <cstring>

stack::stack() {
  my_stack.base = new int[full_size + 1];
  my_stack.top = my_stack.base;

  if (my_stack.base && my_stack.top) {
    std::cout << "顺序栈创建成功！空间容量为" << full_size << std::endl;
  } else {
    std::cout << "顺序栈创建失败！" << std::endl;
    exit(-1);
  }
}

stack::stack(const stack& other) {
  int size = other.size();
  my_stack.base = new int[full_size + 1];
  my_stack.top = my_stack.base + size;
  while (--size >= 0) {
    *(my_stack.base + size) = *(other.my_stack.base + size);
  }
}

stack::stack(stack&& other) {
  my_stack.base = other.my_stack.base;
  my_stack.top = other.my_stack.top;
  other.my_stack.base = other.my_stack.top = nullptr;
}

stack& stack::operator=(const stack& other) {
  int size = other.size();
  my_stack.top = my_stack.base + size;
  while (--size >= 0) {
    *(my_stack.base + size) = *(other.my_stack.base + size);
  }

  return *this;
}

stack& stack::operator=(stack&& other) {
  if (my_stack.base) {
    delete[] my_stack.base;
  }

  my_stack.base = other.my_stack.base;
  my_stack.top = other.my_stack.top;
  other.my_stack.base = other.my_stack.top = nullptr;

  return *this;
}

stack::~stack() {
  if (my_stack.base) {
    delete[] my_stack.base;
  }
  std::cout << "顺序栈已销毁！" << std::endl;
}

void stack::push(const int value) {
  if (my_stack.top - my_stack.base == full_size) {
    std::cout << "栈满！Push失败！" << std::endl;
  }
  *my_stack.top++ = value;
}

int stack::size() const { return my_stack.top - my_stack.base; }

bool stack::empty() const {
  return my_stack.base == my_stack.top ? true : false;
}

int stack::pop() {
  if (my_stack.top - my_stack.base == 0) {
    std::cout << "栈空！Pop失败！" << std::endl;
    return -1;
  } else {
    return *--my_stack.top;
  }
}

int stack::top() {
  if (my_stack.top - my_stack.base == 0) {
    std::cout << "栈空！取元素失败！" << std::endl;
    return -1;
  } else {
    return *(my_stack.top - 1);
  }
}

void stack::dec_to_bin(int dec) {
  my_stack.top = my_stack.base;
  while (dec) {
    push(dec % 2);
    dec /= 2;
  }
  while (!empty()) {
    std::cout << pop();
  }

  std::cout << std::endl;
}

bool stack::palindrome(const char* str) {
  my_stack.top = my_stack.base;
  int size = strlen(str), i = 0;

  for (; i < size / 2; i++) {
    push(str[i]);
  }
  if (size % 2) {
    i++;
  }
  while (!empty()) {
    if (str[i] != pop()) {
      return false;
    }
    i++;
  }
  return true;
}
