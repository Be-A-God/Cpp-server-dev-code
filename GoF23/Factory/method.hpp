#include <iostream>

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