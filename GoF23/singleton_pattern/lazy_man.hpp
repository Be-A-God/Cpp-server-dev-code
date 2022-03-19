// 内存泄漏解决： 嵌套类实现/智能指针/友元类
// 线程安全： 静态局部变量/双检锁+原子操作

#include <iostream>
#include <memory>  //shared_ptr
#include <mutex>   //mutex

// Version 1
// TODO 存在线程安全问题：多个线程由于竞争同时进入指针判断后会创建多个实例
// TODO 内存泄漏：静态指针指向的内存到最后都没有手动释放

class Singleton_1 {
 public:
  Singleton_1(const Singleton_1&) = delete;
  Singleton_1(Singleton_1&&) = delete;
  Singleton_1& operator=(const Singleton_1&) = delete;
  Singleton_1& operator=(Singleton_1&&) = delete;
  ~Singleton_1() = default;

  static Singleton_1* get_instance() {
    if (!instance_ptr) {
      instance_ptr = new Singleton_1;
    }
    return instance_ptr;
  }

 private:
  static Singleton_1* instance_ptr;
  Singleton_1() = default;
};

Singleton_1* Singleton_1::instance_ptr = nullptr;

/* ********************************************* */

// version 2
// 使用智能指针解决内存泄漏问题
// 程序结束时智能指针对象自动折构，所指向的内存空间会自动释放
// 缺点：要求其使用者只能使用智能指针指向该对象（约束）
// TODO 线程安全

class Singleton_2 {
 public:
  Singleton_2(const Singleton_2&) = delete;
  Singleton_2(Singleton_2&&) = delete;
  Singleton_2& operator=(const Singleton_2&) = delete;
  Singleton_2& operator=(Singleton_2&&) = delete;
  ~Singleton_2() = default;

  static std::shared_ptr<Singleton_2> get_instance() {
    if (!instance_ptr) {
      instance_ptr = std::make_shared<Singleton_2>();
    }
    return instance_ptr;
  }

 private:
  Singleton_2() = default;
  static std::shared_ptr<Singleton_2> instance_ptr;
};

std::shared_ptr<Singleton_2> Singleton_2::instance_ptr = nullptr;

/* ********************************************* */

// version 3
// 使用 Double-check 双检锁 部分解决线程安全问题
// 缺点： 不能保证双检锁一定有效
// 原因： 创建对象 new 包含三步
// 分配内存 1
// 调用构造函数 2
// 内存地址返回 3
// 只有步骤 1 是确定的，步骤 2 和 3 是任意顺序的
// 如果线程 A 分配好内存并且返回地址但还没有来得及构造对象
// 此时线程 B 判断条件不为空，直接返回未构造的对象
// TODO 使用内存模型进行原子操作
// TODO 内存泄漏

class Singleton_3 {
 public:
  Singleton_3(const Singleton_3&) = delete;
  Singleton_3(Singleton_3&&) = delete;
  Singleton_3& operator=(const Singleton_3&) = delete;
  Singleton_3& operator=(Singleton_3&&) = delete;
  ~Singleton_3() = default;

  static Singleton_3* get_instance() {
    if (!instance_ptr) {
      std::lock_guard<std::mutex> lock(ptr_mutex);
      if (!instance_ptr) {
        instance_ptr = new Singleton_3;
      }
    }
    return instance_ptr;
  }

 private:
  Singleton_3() = default;
  static Singleton_3* instance_ptr;
  static std::mutex ptr_mutex;
};

Singleton_3* Singleton_3::instance_ptr = nullptr;
// 创建对象
std::mutex Singleton_3::ptr_mutex;

/* ********************************************* */

// version 4
// 使用 双检锁 + 原子操作 彻底解决线程安全问题
// 缺点： 过于复杂
// TODO 内存泄漏
// TODO 暂时无法实现
// 内存模型和原子操作不熟悉
// 使用 call_once 取代

class Singleton_4 {
 public:
  Singleton_4(const Singleton_4&) = delete;
  Singleton_4(Singleton_4&&) = delete;
  Singleton_4& operator=(const Singleton_4&) = delete;
  Singleton_4& operator=(Singleton_4&&) = delete;
  ~Singleton_4() = default;

  static Singleton_4* get_instance() {
    static std::once_flag flag;
    std::call_once(flag, [&] { instance_ptr = new Singleton_4; });
    return instance_ptr;
    // Singleton_4* tmp = instance_ptr.load(std::memory_order_relaxed);
  }

 private:
  Singleton_4() = default;
  static Singleton_4* instance_ptr;
  //   static std::mutex mutex_ptr;
  //   static std::atomic<Singleton_4*> instance_ptr;
};

Singleton_4* Singleton_4::instance_ptr = nullptr;
// std::atomic<Singleton_4*> Singleton_4::instance_ptr;

/* ********************************************* */

// version 5
// 使用嵌套类解决内存泄漏
// TODO 线程安全

class Singleton_5 {
 public:
  Singleton_5(const Singleton_5&) = delete;
  Singleton_5(Singleton_5&&) = delete;
  Singleton_5& operator=(const Singleton_5&) = delete;
  Singleton_5& operator=(Singleton_5&&) = delete;
  ~Singleton_5() = default;

  // 如果使用自身的折构函数去清除空间，会导致递归调用

  // if(NULL != m_p)   该指针在创建唯一实例后一定不为空，条件成立
  // {
  //     delete m_p;   delete会先调用折构函数，之后再销毁空间，此处发生递归调用
  //     m_p = NULL;
  // }

  static Singleton_5* get_instance() {
    if (!instance_ptr) {
      instance_ptr = new Singleton_5;
    }
    return instance_ptr;
  }

 private:
  class Auto_release {
   public:
    // 私有折构函数，对象无法访问
    ~Auto_release() {
      if (!Singleton_5::instance_ptr) {
        return;
      }

      delete Singleton_5::instance_ptr;
      Singleton_5::instance_ptr = nullptr;
    }
  };

  Singleton_5() = default;
  static Singleton_5* instance_ptr;
  static Singleton_5::Auto_release release;
};

// 创建对象，生命周期为整个程序生命周期
Singleton_5::Auto_release Singleton_5::release;
Singleton_5* Singleton_5::instance_ptr = nullptr;

/* ********************************************* */

// version 6
// 嵌套类 + 双检锁
// 彻底解决内存泄漏
// 部分解决线程安全问题

class Singleton_6 {
 public:
  Singleton_6(const Singleton_6&) = delete;
  Singleton_6(Singleton_6&&) = delete;
  Singleton_6& operator=(const Singleton_6&) = delete;
  Singleton_6& operator=(Singleton_6&&) = delete;
  ~Singleton_6() = default;

  static Singleton_6* get_instance() {
    if (!instance_ptr) {
      std::lock_guard<std::mutex> lock(ptr_mutex);
      if (!instance_ptr) {
        instance_ptr = new Singleton_6;
      }
    }
    return instance_ptr;
  }

 private:
  Singleton_6() = default;

  class Auto_release {
   public:
    ~Auto_release() {
      if (!Singleton_6::instance_ptr) {
        return;
      }
      delete Singleton_6::instance_ptr;
      Singleton_6::instance_ptr = nullptr;
    }
  };

  static Singleton_6* instance_ptr;
  static std::mutex ptr_mutex;
  static Singleton_6::Auto_release release;
};

Singleton_6::Auto_release Singleton_6::release;
Singleton_6* Singleton_6::instance_ptr = nullptr;

/* ********************************************* */

// version 7
// 智能指针 + 双检锁
// 彻底解决内存泄漏
// 部分解决线程安全问题

class Singleton_7 {
 public:
  Singleton_7(const Singleton_7&) = delete;
  Singleton_7(Singleton_7&&) = delete;
  Singleton_7& operator=(const Singleton_7&) = delete;
  Singleton_7& operator=(Singleton_7&&) = delete;
  ~Singleton_7() = default;

  static Singleton_7* get_instance() {
    if (!instance_ptr) {
      std::lock_guard<std::mutex> lock(ptr_mutex);
      if (!instance_ptr) {
        instance_ptr = new Singleton_7;
      }
    }
    return instance_ptr;
  }

 private:
  Singleton_7() = default;
  static std::shared_ptr<Singleton_7*> instance_ptr;
  static std::mutex ptr_mutex;
};

std::mutex Singleton_7::ptr_mutex;
std::shared_ptr<Singleton_7*> Singleton_7::instance_ptr = nullptr;

/* ********************************************* */

// version 8
// 智能指针 + 双检锁 + 原子操作
// 智能指针 + call_once
// 彻底解决内存泄漏、线程安全问题

class Singleton_8 {
 public:
  Singleton_8(const Singleton_8&) = delete;
  Singleton_8(Singleton_8&&) = delete;
  Singleton_8& operator=(const Singleton_8&) = delete;
  Singleton_8& operator=(Singleton_8&&) = delete;
  ~Singleton_8() = default;

  static std::shared_ptr<Singleton_8*> get_instance() {
    static std::once_flag flag;
    std::call_once(flag,
                   [&] { instance_ptr = std::make_shared<Singleton_8>() });
    return instance_ptr;
  }

 private:
  Singleton_8() = default;
  std::shared_ptr<Singleton_8*> instance_ptr;
};

std::shared_ptr<Singleton_8*> Singleton_8::instance_ptr = nullptr;

/* ********************************************* */

// version 9
// 嵌套类 + 双检锁 + 原子操作
// 嵌套类 + call_once
// 彻底解决内存泄漏、线程安全问题

class Singleton_9 {
 public:
  Singleton_9(const Singleton_9&) = delete;
  Singleton_9(Singleton_9&&) = delete;
  Singleton_9& operator=(const Singleton_9&) = delete;
  Singleton_9& operator=(Singleton_9&&) = delete;
  ~Singleton_9() = default;

  static Singleton_9* get_instance() {
    static std::once_flag flag;
    std::call_once(flag, [&] { instance_ptr = new Singleton_9; });
    return instance_ptr;
  }

 private:
  Singleton_9() = default;
  static Singleton_9* instance_ptr;

  class Auto_release {
   public:
    ~Auto_release() {
      if (!Singleton_9::instance_ptr) {
        return;
      }
      delete Singleton_9::instance_ptr;
      Singleton_9::instance_ptr = nullptr;
    }
  };

  static Singleton_9::Auto_release release;
};

Singleton_9::Auto_release Singleton_9::release;
Singleton_9* Singleton_9::instance_ptr = nullptr;

/* ********************************************* */

// version 10
// 静态成员方法的局部静态变量
// 简洁高效
// C++11开始静态局部变量保证其原子性和线程安全
// 线程竞争时等待静态局部变量初始化完成，且静态局部变量只初始化一次
// 最优解

class Singleton {
 public:
  Singleton(const Singleton&) = delete;
  Singleton(Singleton&&) = delete;
  Singleton& operator=(const Singleton&) = delete;
  Singleton& operator=(Singleton&&) = delete;
  ~Singleton() = default;

  static Singleton get_instance() {
    static Singleton instance;
    return instance;
  }

 private:
  Singleton() = default;
};