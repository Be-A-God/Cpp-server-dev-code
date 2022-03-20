#include <iostream>

// 同样多种具体产品抽象成一个抽象产品（和简单工厂方法一样）：抽象产品只有一类
// 简单工厂模式的工厂并没有对具体产品的生产进行分工而是统一生产
// 工厂方法则实现多样化（可以理解为多个流水线）
// 一条流水线针对一种具体产品
// 每多一种具体产品就需要多出来一种工厂流水线
// 抽象产品一个，抽象工厂一个
// 具体产品多种，具体工厂（流水线）多种（满足一对一关系），具体产品由具体工厂（流水线）负责实现
// 利用多态和继承，用户指定具体工厂（流水线）便可以生产出对应具体产品
// 添加产品只需要派生出新类，无需修改源代码

// 抽象产品类

class Product {
 public:
  virtual ~Product() = default;
  virtual std::string Operation() const = 0;
};

// 具体产品类

class ConcreteProduct1 : public Product {
 public:
  std::string Operation() const override { return "{具体产品1}"; }
};

class ConcreteProduct2 : public Product {
 public:
  std::string Operation() const override { return "{具体产品2}"; }
};

// 抽象工厂类

class Creator {
 public:
  virtual ~Creator() = default;
  virtual Product* FactoryMethod() const = 0;

  // 类方法创建对象
  std::string SomeOperation() const {
    Product* product = this->FactoryMethod();
    std::string result =
        "Creator: The same creator's code has just worked with " +
        product->Operation();
    delete product;
    return result;
  }
};

// 具体工厂类

class ConcreteCreator1 : public Creator {
 public:
  Product* FactoryMethod() const override { return new ConcreteProduct1; }
};

class ConcreteCreator2 : public Creator {
 public:
  Product* FactoryMethod() const override { return new ConcreteProduct2; }
};

// 客户端

void ClientCode(const Creator& creator) {
  std::cout
      << "Client: I'm not aware of the creator's class, but it still works.\n"
      << creator.SomeOperation() << std::endl;
}