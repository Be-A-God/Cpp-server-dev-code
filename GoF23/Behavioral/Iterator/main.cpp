/**
 * Iterator Design Pattern
 *
 * Intent: Lets you traverse elements of a collection without exposing its
 * underlying representation (list, stack, tree, etc.).
 */

// Iterator 可以作为抽象基类，声明查询为空、首元素、尾元素、当前元素的方法接口
// Iterator 派生类负责实现迭代方法，实际是对begin()、end()成员方法的封装
// Iterator 的具体迭代实现也可以用户自定义（迭代方式通常需要泛化）
// Iterator 的具体派生类内部对应有迭代对象的类型指针
// 被迭代对象内部需要实现生成Iterator类对象的方法
// Iterator 需要访问被迭代对象内部数据，因此需要将具体的迭代器声明为友元
// 通过被迭代对象调用生成的迭代器实现内部数据的封装（自定义类比较合适）

#include <iostream>
#include <string>
#include <vector>

/**
 * C++ has its own implementation of iterator that works with a different
 * generics containers defined by the standard library.
 */

template <typename T, typename U>
class Iterator {
 public:
  typedef typename std::vector<T>::iterator iter_type;
  Iterator(U *p_data, bool reverse = false) : m_p_data_(p_data) {
    m_it_ = m_p_data_->m_data_.begin();
  }

  void First() { m_it_ = m_p_data_->m_data_.begin(); }

  void Next() { m_it_++; }

  bool IsDone() { return (m_it_ == m_p_data_->m_data_.end()); }

  iter_type Current() { return m_it_; }

 private:
  U *m_p_data_;
  iter_type m_it_;
};

/**
 * Generic Collections/Containers provides one or several methods for retrieving
 * fresh iterator instances, compatible with the collection class.
 */

template <class T>
class Container {
  friend class Iterator<T, Container>;

 public:
  void Add(T a) { m_data_.push_back(a); }

  Iterator<T, Container> *CreateIterator() {
    return new Iterator<T, Container>(this);
  }

 private:
  std::vector<T> m_data_;
};

class Data {
 public:
  Data(int a = 0) : m_data_(a) {}

  void set_data(int a) { m_data_ = a; }

  int data() { return m_data_; }

 private:
  int m_data_;
};

/**
 * The client code may or may not know about the Concrete Iterator or Collection
 * classes, for this implementation the container is generic so you can used
 * with an int or with a custom class.
 */
void ClientCode() {
  std::cout << "________________Iterator with "
               "int______________________________________"
            << std::endl;
  Container<int> cont;

  for (int i = 0; i < 10; i++) {
    cont.Add(i);
  }

  Iterator<int, Container<int>> *it = cont.CreateIterator();
  for (it->First(); !it->IsDone(); it->Next()) {
    std::cout << *it->Current() << std::endl;
  }

  Container<Data> cont2;
  Data a(100), b(1000), c(10000);
  cont2.Add(a);
  cont2.Add(b);
  cont2.Add(c);

  std::cout << "________________Iterator with custom "
               "Class______________________________"
            << std::endl;
  Iterator<Data, Container<Data>> *it2 = cont2.CreateIterator();
  for (it2->First(); !it2->IsDone(); it2->Next()) {
    std::cout << it2->Current()->data() << std::endl;
  }
  delete it;
  delete it2;
}

int main() {
  ClientCode();
  return 0;
}