#include <iostream>

// version 1
// 使用局部静态变量 懒汉模式 作为模板基类
// 使用友元类声明
// protected 确保派生类能够访问基类构造函数 同时对外隐藏自身构造

template <class T>
class Singleton {
 public:
  Singleton(const Singleton&) = delete;
  Singleton(Singleton&&) = delete;
  Singleton& operator=(const Singleton&) = delete;
  Singleton& operator(Singleton&&) = delete;
  virtual ~Singleton() = default;

  static T& get_instance() {
    static T instance;
    // 此处需要访问其构造函数，故下面需要将具体化基类声明为友元类
    return instance;
  }

 protected:
  // 构造函数保护是为了能够继承出派生类
  // 派生类的创建需要调用基类构造函数
  Singleton() = default;
};

class Drived_singleton final : public Singleton<Drived_singleton> {
 public:
  friend class Singleton<Drived_singleton>;
  Drived_singleton(const Drived_singleton&) = delete;
  Drived_singleton(Drived_singleton&&) = delete;
  Drived_singleton& operator=(const Drived_singleton&) = delete;
  Drived_singleton& operator=(Drived_singleton&&) = delete;

  /* something want to do else */

 private:
  Drived_singleton() = default;
};

/* ***************************** */

// version 2
// 使用外界无法提供的一种类型来构造类（定义在模板基类的保护部份）
// 该类型只能由基类提供
// 从而限制了外界调用构造函数创建实例的情况

template <class T>
class Singleton_1 {
 public:
  Singleton_1(const Singleton_1&) = delete;
  Singleton_1(Singleton_1&&) = delete;
  Singleton_1& operator=(const Singleton_1&) = delete;
  Singleton_1& operator=(Singleton_1&&) = delete;
  virtual ~Singleton_1() = default;

  static T& get_instance() {
    static T instance{token()};
    return instance;
  }

 protected:
  // 该自定义类型只有在该基类和派生类能够看到和使用
  struct token {};
  Singleton_1() = default;
};

class Drived_singleton_1 final : public Singleton_1<Drived_singleton_1> {
 public:
  // 外界无法调用，因为无法传递该类型参数，导致函数不匹配从而构造失败
  Drived_singleton_1(token);
  ~Drived_singleton_1() = default;
  Drived_singleton_1() = delete;
  Drived_singleton_1(const Drived_singleton_1&&) = delete;
  Drived_singleton_1(Drived_singleton_1&&) = delete;
  Drived_singleton_1& operator=(const Drived_singleton_1&) = delete;
  Drived_singleton_1& operator=(Drived_singleton_1&&) = delete;
};