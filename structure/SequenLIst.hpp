/*
 * @Author: Be-A-God
 * @Date: 2022-02-25 18:39:47
 * @Last Modified by:   Be-A-God
 * @Last Modified time: 2022-02-25 18:39:47
 */

#pragma once
#include <concepts>
#include <string>

template <class data_type, int elem_nums>
requires(std::same_as<data_type, int> || std::same_as<data_type, char> ||
         std::same_as<data_type, std::string>) class SequenList {
 public:
  SequenList(const data_type&);
  SequenList(const SequenList&);
  SequenList(SequenList&&);
  SequenList& operator=(const SequenList&);
  SequenList& operator=(const SequenList&&);
  //   void initiate();  使用构造函数代替
  int length() const;
  data_type get(int) const;
  int locate(data_type) const;
  int insert(data_type, int);
  int deleted(int);
  ~SequenList();

 private:
  data_type* linear_list;
  int len;
};