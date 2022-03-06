/**
 * @file queue.cpp
 * @author Be-A-God (wx1028674648@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-03-06
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "queue.hpp"

queue::queue() {
  my_queue.base = new int[full_size];
  if (!my_queue.base) {
    std::cout << "队列创建失败！" << std::endl;
    exit(-1);
  }
  my_queue.front = my_queue.rear = 0;
  std::cout << "队列创建成功！（调用默认构造函数）" << std::endl;
}

queue::queue(const queue& other) {
  my_queue.base = new int[full_size];
  int front = my_queue.front = other.my_queue.front;
  int rear = my_queue.rear = other.my_queue.rear;

  while (front != rear) {
    my_queue.base[front] = other.my_queue.base[front];
    front = (front + 1) % full_size;
  }

  std::cout << "队列创建成功！（调用复制构造函数）" << std::endl;
}

queue::queue(queue&& other) {
  my_queue.base = other.my_queue.base;
  my_queue.front = other.my_queue.front;
  my_queue.rear = other.my_queue.rear;
  other.my_queue.base = nullptr;

  std::cout << "队列创建成功！（调用移动构造函数）" << std::endl;
}

queue& queue::operator=(const queue& other) {
  int front = my_queue.front = other.my_queue.front;
  int rear = my_queue.rear = other.my_queue.rear;

  while (front != rear) {
    my_queue.base[front] = other.my_queue.base[front];
    front = (front + 1) % full_size;
  }

  std::cout << "队列赋值完成！（调用复制赋值运算符）" << std::endl;

  return *this;
}

queue& queue::operator=(queue&& other) {
  if (my_queue.base) {
    delete[] my_queue.base;
  }
  my_queue.base = other.my_queue.base;
  my_queue.front = other.my_queue.front;
  my_queue.rear = other.my_queue.rear;
  other.my_queue.base = nullptr;

  std::cout << "队列赋值完成！（调用移动赋值运算符）" << std::endl;

  return *this;
}

queue::~queue() {
  if (my_queue.base) {
    delete[] my_queue.base;
  }

  std::cout << "队列已销毁！" << std::endl;
}

bool queue::empty() const {
  return my_queue.front == my_queue.rear ? true : false;
}

bool queue::full() const {
  return (my_queue.rear + 1) % full_size == my_queue.front ? true : false;
}

void queue::join(int value) {
  if (full()) {
    std::cout << "队列满！入队失败！" << std::endl;
  } else {
    my_queue.base[my_queue.rear] = value;
    my_queue.rear = (my_queue.rear + 1) % full_size;
  }
}

int queue::out() {
  if (empty()) {
    std::cout << "队列为空！出队失败！" << std::endl;
    return -1;
  }
  int value = my_queue.base[my_queue.front];
  my_queue.front = (my_queue.front + 1) % full_size;
  return value;
}

int queue::top() const {
  if (empty()) {
    std::cout << "队列为空！取队列首元素失败！" << std::endl;
    return -1;
  }
  return my_queue.base[my_queue.front];
}

int queue::size() const {
  //   int front = my_queue.front;
  //   int rear = my_queue.rear;
  //   int count = 0;
  //   while (front != rear) {
  //     front = (front + 1) % full_size;
  //     count++;
  //   }
  //   return count;

  return (my_queue.rear - my_queue.front + full_size) % full_size;
}

void queue::travel() const {
  int front = my_queue.front;
  int rear = my_queue.rear;

  while (front != rear) {
    std::cout << my_queue.base[front] << '\t';
    front = (front + 1) % full_size;
  }

  std::cout << std::endl;
}
