/**
 * @file queue.hpp
 * @author Be-A-God (wx1028674648@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-03-06
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <iostream>

struct dynamic_queue {
  int* base;
  int front, rear;
};

class queue {
 public:
  queue();
  queue(queue&& other);
  explicit queue(const queue& other);
  queue& operator=(const queue& other);
  queue& operator=(queue&& other);
  ~queue();
  bool empty() const;
  bool full() const;
  void join(int value);
  int out();
  int top() const;
  int size() const;
  void travel() const;

 private:
  dynamic_queue my_queue;
  const int full_size = 50;
};