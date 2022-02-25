/**
 * @file SequenList.cpp
 * @author Be-A-God (wx1028674648@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-02-25
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "SequenLIst.hpp"

template <class data_type>
SequenList<data_type>::SequenList(const data_type *&user_array) {
TODO:
  字符串字面量需要修正

  if (!user_array) {
    int len = sizeof(user_array) / sizeof(user_array[0]);
    linear_list = new data_type[len];
    for (int index = 0; const auto &i : user_array) {
      linear_list[index++] = i;
    }
  } else {
    std::cout << "wrong parameter passed! Please using a pointer instead!"
              << endl;
  }
}

template <class data_type>
SequenList<data_type>::SequenList(const SequenList &other) : len(other.len) {
  linear_list = new data_type[len];
  for (int index = 0; const auto &i : other) {
    linear_list[index++] = i;
  }
}

template <class data_type>
SequenList<data_type>::SequenList(SequenList &&other)
    : len(other.len), linear_list(other.linear_list) {
  other.linear_list = nullptr;
}

template <class data_type>
SequenList<data_type> &SequenList<data_type>::operator=(
    const SequenList &other) {
  len = other.len;
  linear_list = new data_type[len];
  for (int index = 0; const auto &i : other) {
    linear_list[index++] = i;
  }
  return *this;
}

template <class data_type>
SequenList<data_type> &SequenList<data_type>::operator=(SequenList &&other) {
  len = other.len;
  if (linear_list) {
    delete[] linear_list;
  }
  linear_list = other.linear_list;
  other.linear_list = nullptr;
  return *this;
}

template <class data_type>
SequenList<data_type>::~SequenList() {
  if (linear_list) {
    delete[] linear_list;
  }
}

template <class data_type>
int SequenList<data_type>::length() const {}

template <class data_type>
data_type SequenList<data_type>::get(int elem) const {}

template <class data_type>
int SequenList<data_type>::locate(data_type target_elem) const {}

template <class data_type>
int SequenList<data_type>::insert(data_type elem, int pos) {}

template <class data_type>
int SequenList<data_type>::deleted(int pos) {}
