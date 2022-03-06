#include "singly_linked_list.hpp"

int main(int argc, char const *argv[]) {
  singly_linked_list<int> my_list;
  my_list.create_tail_plug();
  my_list.travel_list();
  my_list.delete_abs_repeat();
  my_list.travel_list();
  my_list.create_tail_plug();
  my_list.travel_list();
  my_list.reverse_list();
  my_list.travel_list();
  my_list.delete_elem(2);
  my_list.travel_list();
  std::cout << my_list.get_length() << std::endl;
  my_list.empty_list();
  std::cout << "empty or not:" << my_list.is_empty() << std::endl;
  my_list.travel_list();
  my_list.create_tail_plug();
  const Node<int> *elem_ptr = my_list.find_middle();
  std::cout << "middle:" << elem_ptr->data << std::endl;
  elem_ptr = my_list.find_countdown_k(4);
  std::cout << "countdown k:" << elem_ptr->data << std::endl;
  my_list.insert_elem(3, 1024);
  my_list.travel_list();

  return 0;
}
