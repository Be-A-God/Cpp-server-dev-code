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

#include "queue.hpp"

int main(int argc, char const *argv[]) {
  queue first_queue;
  queue second_queue(std::move(first_queue));
  int n = 0;
  while (n < 50) {
    second_queue.join(100 - n);
    n++;
  }
  second_queue.travel();
  std::cout.setf(std::ios_base::boolalpha);
  std::cout << "队列大小：" << second_queue.size() << std::endl;
  std::cout << "队列为空：" << second_queue.empty() << std::endl;
  std::cout << "队列为满：" << second_queue.full() << std::endl;
  std::cout << "队列大小：" << second_queue.size() << std::endl;
  std::cout << "队列首元素：" << second_queue.top() << std::endl;
  std::cout << "队列出队元素：" << second_queue.out() << std::endl;
  std::cout << "队列大小：" << second_queue.size() << std::endl;
  std::cout << "队列为满：" << second_queue.full() << std::endl;
  second_queue.travel();

  return 0;
}
