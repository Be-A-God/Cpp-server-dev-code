// 静态指针内存回收： 智能指针/友元类/嵌套类
// 友元类暂不实现

#include <iostream>
#include <memory>

// version 1
// 创建静态对象
// 无内存泄漏及线程安全问题

class Singleton_1 {
 public:
  Singleton_1(const Singleton_1&) = delete;
  Singleton_1(Singleton_1&&) = delete;
  Singleton_1& operator=(const Singleton_1&) = delete;
  Singleton_1& operator=(Singleton_1&&) = delete;
  ~Singleton_1() = default;

  // 一开始就创建对象，之后返回的都是一开始创建的对象，不会产生线程安全问题
  // 静态对象程序结束后回收，不考虑内存泄漏
  static Singleton_1& get_instance() { return instance; }

 private:
  Singleton_1() = default;
  static Singleton_1 instance;
};
//创建对象
Singleton_1 Singleton_1::instance;

/* ********************************* */

// version 2
// 使用静态指针
// TODO 存在内存泄漏的问题

class Singleton_2 {
 public:
  Singleton_2(const Singleton_2&) = delete;
  Singleton_2(Singleton_2&&) = delete;
  Singleton_2& operator=(const Singleton_2&) = delete;
  Singleton_2& operator=(Singleton_2&&) = delete;
  ~Singleton_2() = default;

  static Singleton_2* get_instance() { return instance_ptr; }

 private:
  Singleton_2() = default;
  static Singleton_2* instance_ptr;
};

Singleton_2* Singleton_2::instance_ptr = new Singleton_2;

/* ********************************* */

// version 3
// 使用静态指针 + 嵌套类

class Singleton_3 {
 public:
  Singleton_3(const Singleton_3&) = delete;
  Singleton_3(Singleton_3&&) = delete;
  Singleton_3& operator=(const Singleton_3&) = delete;
  Singleton_3& operator=(Singleton_3&&) = delete;
  ~Singleton_3() = default;

  static Singleton_3* get_instance() { return instance_ptr; }

 private:
  Singleton_3() = default;
  static Singleton_3* instance_ptr;
  class Auto_release {
   public:
    ~Auto_release() {
      if (!instance_ptr) {
        return;
      }
      delete instance_ptr;
      instance_ptr = nullptr;
    }
  };
  static Auto_release release;
};

Singleton_3* Singleton_3::instance_ptr = new Singleton_3;
Singleton_3::Auto_release Singleton_3::release;

/* ********************************* */

// version 4
// 使用智能指针

class Singleton_4 {
 public:
  Singleton_4(const Singleton_4&) = delete;
  Singleton_4(Singleton_4&&) = delete;
  Singleton_4& operator=(const Singleton_4&) = delete;
  Singleton_4& operator=(Singleton_4&&) = delete;
  ~Singleton_4() = default;

  static std::shared_ptr<Singleton_4> get_instance() { return instance_ptr; }

 private:
  Singleton_4() = default;
  static std::shared_ptr<Singleton_4> instance_ptr;
};

std::shared_ptr<Singleton_4> Singleton_4::instance_ptr =
    std::make_shared<Singleton_4>();