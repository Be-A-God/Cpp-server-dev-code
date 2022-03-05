/**
 * @file singly_linked_list.hpp
 * @author Be-A-God (wx1028674648@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-02-27
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once
#include <iostream>

template <typename elem_type>
struct Node {
  elem_type data;
  Node<elem_type> *next;
};

template <class elem_type>
requires(std::is_same<elem_type, int>::value ||
         std::is_same<elem_type, char>::value) class singly_linked_list final {
 public:
  singly_linked_list();
  ~singly_linked_list();

  singly_linked_list(const singly_linked_list<elem_type> &) = delete;
  singly_linked_list<elem_type> &operator=(
      const singly_linked_list<elem_type> &) = delete;
  singly_linked_list(singly_linked_list<elem_type> &&) = delete;
  singly_linked_list<elem_type> &operator=(singly_linked_list<elem_type> &&) =
      delete;

  const Node<elem_type> *find_elem(elem_type value) const;
  const Node<elem_type> *find_countdown_k(int k) const;
  const Node<elem_type> *find_middle() const;
  elem_type get_elem(int pos) const;
  bool delete_repeat();
  bool reverse_list();
  bool empty_list();
  bool insert_elem(int pos, elem_type value);
  bool delete_elem(elem_type value);
  bool delete_elem(int pos);
  bool is_empty() const;
  int get_length() const;
  void travel_list() const;
  void create_head_plug();
  void create_tail_plug();
  //   void merge_order_list(singly_linked_list<elem_type> &other_list);

 private:
  Node<elem_type> *head_node_point;
};

template <class elem_type>
singly_linked_list<elem_type>::singly_linked_list() : head_node_point(nullptr) {
  head_node_point = new Node<elem_type>;

  if (!head_node_point) {
    std::cout << "链表创建失败！" << std::endl;
    exit(1);
  }

  head_node_point->next = nullptr;
  head_node_point->data = 0;

  std::cout << "链表创建成功" << std::endl;
}

template <class elem_type>
singly_linked_list<elem_type>::~singly_linked_list() {
  Node<elem_type> *cur_ptr = head_node_point->next;
  Node<elem_type> *temp_ptr;

  head_node_point->next = nullptr;
  delete head_node_point;

  while (cur_ptr) {
    temp_ptr = cur_ptr;
    cur_ptr = cur_ptr->next;
    temp_ptr->next = nullptr;
    delete temp_ptr;
  }

  std::cout << "链表销毁成功" << std::endl;
}

template <class elem_type>
const Node<elem_type> *singly_linked_list<elem_type>::find_elem(
    elem_type value) const {
  Node<elem_type> *temp_ptr = head_node_point->next;

  while (temp_ptr && temp_ptr->data != value) {
    temp_ptr = temp_ptr->next;
  }

  return temp_ptr ? temp_ptr : []() -> {
    std::cout << "查找元素失败：链表中没有该元素值！" << std::endl;
    return nullptr;
  };
}

template <class elem_type>
const Node<elem_type> *singly_linked_list<elem_type>::find_countdown_k(
    int k) const {
  Node<elem_type> *fast_ptr = head_node_point->next;
  Node<elem_type> *slow_ptr = fast_ptr;

  while (fast_ptr->next) {
    if (--k <= 0) {
      slow_ptr = slow_ptr->next;
    }
    fast_ptr = fast_ptr->next;
  }
  return k > 0 ? nullptr : slow_ptr;
}

template <class elem_type>
const Node<elem_type> *singly_linked_list<elem_type>::find_middle() const {
  if (!head_node_point->next) {
    return nullptr;
  }

  Node<elem_type> *fast_ptr = head_node_point;
  Node<elem_type> *slow_ptr = fast_ptr;

  while (fast_ptr && fast_ptr->next) {
    fast_ptr = fast_ptr->next;
    fast_ptr = fast_ptr->next;
    slow_ptr = slow_ptr->next;
  }

  return slow_ptr;
}

template <class elem_type>
elem_type singly_linked_list<elem_type>::get_elem(int pos) const {
  int i = 1;
  Node<elem_type> *cur_ptr = head_node_point->next;

  while (cur_ptr && i < pos) {
    cur_ptr = cur_ptr->next;
    i++;
  }

  return (i > pos || !cur_ptr)
         ? []() -> elem_type { std::cout << "链表不存在该位置！" << std::endl; return -1; }
         : cur_ptr->data;
}

template <class elem_type>
void singly_linked_list<elem_type>::create_head_plug() {
  int elem_nums = 0;
  std::cout << "请输入插入的元素个数：" << std::endl;
  while (!(std::cin >> elem_nums) && elem_nums <= 0) {
    std::cout << "元素个数输入有误，请重新输入！" << std::endl;
  }

  std::cout << "[头插法创建链表]请依次输入元素:" << std::endl;

  while (--elem_nums >= 0) {
    Node<elem_type> *temp_ptr = new Node<elem_type>;
    std::cin >> temp_ptr->data;
    temp_ptr->next = head_node_point->next;
    head_node_point->next = temp_ptr;
  }
}

template <class elem_type>
void singly_linked_list<elem_type>::create_tail_plug() {
  Node<elem_type> *tail_ptr = head_node_point;
  while (!tail_ptr->next) {
    tail_ptr = tail_ptr->next;
  }

  int elem_nums = 0;

  std::cout << "请输入插入的元素个数：" << std::endl;
  while (!(std::cin >> elem_nums) && elem_nums <= 0) {
    std::cout << "元素个数输入有误，请重新输入！" << std::endl;
  }

  std::cout << "[尾插法创建链表]请依次输入元素:" << std::endl;

  while (--elem_nums >= 0) {
    Node<elem_type> *temp_ptr = new Node<elem_type>;
    std::cin >> temp_ptr->data;
    temp_ptr->next = nullptr;
    tail_ptr->next = temp_ptr;
    tail_ptr = temp_ptr;
  }
}

template <class elem_type>
bool singly_linked_list<elem_type>::delete_repeat() {}

template <class elem_type>
bool singly_linked_list<elem_type>::reverse_list() {}

template <class elem_type>
bool singly_linked_list<elem_type>::empty_list() {}

template <class elem_type>
bool singly_linked_list<elem_type>::insert_elem(int pos, elem_type value) {}

template <class elem_type>
bool singly_linked_list<elem_type>::delete_elem(elem_type value) {}

template <class elem_type>
bool singly_linked_list<elem_type>::delete_elem(int pos) {}

template <class elem_type>
bool singly_linked_list<elem_type>::is_empty() const {}

template <class elem_type>
int singly_linked_list<elem_type>::get_length() const {}

template <class elem_type>
void singly_linked_list<elem_type>::travel_list() const {}
