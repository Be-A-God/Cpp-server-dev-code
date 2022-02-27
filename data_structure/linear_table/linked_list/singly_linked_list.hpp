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

  Node<elem_type> *find_elem(elem_type value);
  Node<elem_type> *find_countdown_k(int k);
  Node<elem_type> *find_middle();
  elem_type get_elem(int pos);
  bool create_head_plug();
  bool create_tail_plug();
  bool delete_repeat();
  bool reverse_list();
  bool empty_list();
  bool insert_elem(int pos, elem_type value);
  bool delete_elem(elem_type value);
  bool delete_elem(int pos);
  bool is_empty();
  int get_length();
  void travel_list();
  //   void merge_order_list(singly_linked_list<elem_type> &other_list);

 private:
  Node<elem_type> *head_node_point;
};