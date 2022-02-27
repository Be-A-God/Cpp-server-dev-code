/**
 * @file SequenLIst.hpp
 * @author Be-A-God (wx1028674648@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-02-25
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once
// #include <concepts>
#include <iostream>
#include <string>

// TODO: 安全优化；全类型支持
template <class data_type>
concept type_ruler = std::is_same<data_type, int>::value ||
                     std::is_same<data_type, char>::value ||
                     std::is_same<data_type, std::string>::value;

template <class data_type>
requires type_ruler<data_type> class SequenList {
 public:
  SequenList() = delete;
  SequenList(const data_type *user_array, int size);
  SequenList(const SequenList<data_type> &other);
  SequenList(SequenList<data_type> &&other);
  SequenList<data_type> &operator=(const SequenList<data_type> &other);
  SequenList<data_type> &operator=(SequenList<data_type> &&other);
  //   void initiate();  使用构造函数代替
  int length() const;
  data_type get(const int &index) const;
  int locate(const data_type &target_elem) const;
  int insert(const data_type &elem, const int &pos);
  int deleted(const int &pos);
  void travel() const;
  ~SequenList();

 private:
  data_type *linear_list;
  int len;
};

template <class data_type>
SequenList<data_type>::SequenList(const data_type *user_array, int size)
    : len(size) {
  // TODO: 字符串字面量存在结束符问题
  if (user_array) {
    linear_list = new data_type[len];
    for (int index = 0; index < len; index++) {
      linear_list[index] = user_array[index];
    }
    std::cout << "普通构造函数" << std::endl;
  } else {
    std::cout << "wrong parameter passed! Please using a pointer instead!"
              << std::endl;
  }
}

template <class data_type>
SequenList<data_type>::SequenList(const SequenList<data_type> &other)
    : len(other.len) {
  linear_list = new data_type[len];
  for (int index = 0; index < len; index++) {
    linear_list[index] = other.linear_list[index];
  }
  std::cout << "复制构造函数" << std::endl;
}

template <class data_type>
SequenList<data_type>::SequenList(SequenList<data_type> &&other)
    : len(other.len), linear_list(other.linear_list) {
  other.linear_list = nullptr;
  std::cout << "移动构造函数" << std::endl;
}

template <class data_type>
SequenList<data_type> &SequenList<data_type>::operator=(
    const SequenList<data_type> &other) {
  len = other.len;
  linear_list = new data_type[len];
  for (int index = 0; index < len; index++) {
    linear_list[index] = other.linear_list[index];
  }
  std::cout << "复制赋值运算符" << std::endl;
  return *this;
}

template <class data_type>
SequenList<data_type> &SequenList<data_type>::operator=(
    SequenList<data_type> &&other) {
  len = other.len;
  if (linear_list) {
    delete[] linear_list;
  }
  linear_list = other.linear_list;
  other.linear_list = nullptr;
  std::cout << "移动赋值运算符" << std::endl;
  return *this;
}

template <class data_type>
SequenList<data_type>::~SequenList() {
  if (linear_list) {
    delete[] linear_list;
  }
  std::cout << "~(): sequen_table destoried" << std::endl;
}

template <class data_type>
int SequenList<data_type>::length() const {
  if (linear_list) {
    return len;
  }
  std::cout << "Length: sequen_table is empty!" << std::endl;
  return -1;
}

template <class data_type>
data_type SequenList<data_type>::get(const int &index) const {
  if (linear_list && index >= 0 && index < len) {
    return linear_list[index];
  }
  std::cout << "Get: The following index is wrong!Being from zero";
  // TODO: 返回类类型不好处理，暂且不返回
  // return std::is_same<std::string, data_type>::value ? "" : -1;
}

template <class data_type>
int SequenList<data_type>::locate(const data_type &target_elem) const {
  if (linear_list) {
    int i = 0;
    while (i < len && linear_list[i] != target_elem) {
      i++;
    }
    return linear_list[i] == target_elem ? i : -1;
  }
  std::cout << "Locate: The sequen_table is empty!" << std::endl;
  return -1;
}

template <class data_type>
int SequenList<data_type>::insert(const data_type &elem, const int &pos) {
  if (linear_list && pos >= 0 && pos < len) {
    data_type *temp = new data_type[len + 1];
    int i = 0;
    while (i != pos) {
      temp[i] = linear_list[i];
      i++;
    }
    int j = i;
    temp[i++] = elem;
    while (i <= len) {
      temp[i] = linear_list[j];
      i++;
      j++;
    }
    delete[] linear_list;
    linear_list = temp;
    len++;
    return 1;
  }
  std::cout << "Insert: The sequen_table is empty or param is wrong!"
            << std::endl;
  return -1;
}

template <class data_type>
int SequenList<data_type>::deleted(const int &pos) {
  if (linear_list && pos >= 0 && pos < len) {
    len--;
    data_type *temp = new data_type[len];
    int i = 0;
    while (i != pos) {
      temp[i] = linear_list[i];
      i++;
    }
    int j = i;
    i++;
    while (j < len) {
      temp[j] = linear_list[i];
      j++;
      i++;
    }
    delete[] linear_list;
    linear_list = temp;
    temp = nullptr;
    return 1;
  }
  std::cout << "Delete: The sequen_table is empty or param is wrong!"
            << std::endl;
  return -1;
}

template <class data_type>
void SequenList<data_type>::travel() const {
  if (linear_list) {
    for (int index = 0; index < len; index++) {
      std::cout << linear_list[index] << '\t';
    }
  } else {
    std::cout << "Travel: sequen_table is empty!";
  }
  std::cout << std::endl;
}
