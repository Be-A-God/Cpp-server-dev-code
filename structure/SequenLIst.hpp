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
#include <concepts>
#include <string>

template <class data_type>
requires(std::same_as<data_type, int*> || std::same_as<data_type, char*> ||
         std::same_as<data_type, std::string*>) class SequenList {
 public:
  SequenList(const data_type*&);
  SequenList(const SequenList&);
  SequenList(SequenList&&);
  SequenList<data_type>& operator=(const SequenList&);
  SequenList<data_type>& operator=(SequenList&&);
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