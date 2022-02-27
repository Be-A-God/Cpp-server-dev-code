/**
 * @file MySequenList.cpp
 * @author Be-A-God (wx1028674648@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-02-26
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "SequenLIst.hpp"

int main(int argc, char const *argv[]) {
  // int *type_int = new int[10]{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  // int type_int[]{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  // char *type_char =
  //     new char[10]{'d', 'f', 's', 's', 'g', '5', 'o', '=', 'l', 'v'};
  std::string type_string[]{"this",  "is",     "test", "for", "my",
                            "first", "prgram", "may",  "not", "well"};

  std::string type_string_assign[]{"test",  "for",    "test", "for", "my",
                                   "first", "prgram", "may",  "not", "well"};

  SequenList<std::string> my_sequen_list(type_string, 10);
  SequenList<std::string> my_sequen_list_copy(my_sequen_list);
  SequenList<std::string> my_sequen_list_move(std::move(my_sequen_list));
  // SequenList<std::string> my_sequen_list_assign =
  //     std::move(my_sequen_list_copy);
  SequenList<std::string> my_sequen_list_assign(type_string_assign, 10);
  my_sequen_list_assign = std::move(my_sequen_list_copy);

  std::cout << "size: " << my_sequen_list_assign.length() << std::endl;
  std::cout << "get: " << my_sequen_list_assign.get(3) << std::endl;
  std::cout << "locate: " << my_sequen_list_assign.locate("sadasd")
            << std::endl;
  std::cout << "locate: " << my_sequen_list_assign.locate("for") << std::endl;

  my_sequen_list_assign.deleted(0);
  my_sequen_list_assign.insert("insertFirst", 0);
  my_sequen_list_assign.insert("tailOfTwo", 9);

  std::cout << "locate: " << my_sequen_list_assign.locate("tailOfTwo")
            << std::endl;
  std::cout << "locate: " << my_sequen_list_assign.locate("prgram")
            << std::endl;
  std::cout << "size: " << my_sequen_list_assign.length() << std::endl;

  my_sequen_list_assign.travel();

  // if (type_string) {
  //   delete[] type_string;
  // }

  return 0;
}
