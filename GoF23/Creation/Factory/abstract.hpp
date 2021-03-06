#include <iostream>

// 抽象工厂类：不再只有一类抽象产品，而是有多类抽象产品；工厂对外有多类抽象产品（多个子厂）
// 抽象产品要有统一提取的特征，不能按照品牌去抽象出来
// 具体工厂不再是流水线，而是新的子厂
// 每个子厂负责生产同一品牌具体产品（来自不同抽象产品的以品牌划分的一个集合）
// 对多个抽象产品的具体产品按照一定特点进行划分集合，交付给具体工厂生产（总厂的虚函数）
// 子厂不再是流水线，不再对应一种具体产品，而是一个系列的具体产品（可能来自不同抽象产品）
// 例如：工厂->耐克子厂->耐克鞋子、耐克衣服等具体产品（来自抽象产品衣服、鞋子）
// 同样利用多态和继承

class AbstractProductA {
 public:
  virtual ~AbstractProductA() = default;
  virtual std::string UsefulFunctionA() const = 0;
};

class ConcreteProductA1 : public AbstractProductA {
 public:
  std::string UsefulFunctionA() const override {
    return "The result of the product A1.";
  }
};

class ConcreteProductA2 : public AbstractProductA {
  std::string UsefulFunctionA() const override {
    return "The result of the product A2.";
  }
};

class AbstractProductB {
 public:
  virtual ~AbstractProductB() = default;
  virtual std::string UsefulFunctionB() const = 0;
  virtual std::string AnotherUsefulFunctionB(
      const AbstractProductA &collaborator) const = 0;
};

class ConcreteProductB1 : public AbstractProductB {
 public:
  std::string UsefulFunctionB() const override {
    return "The result of the product B1.";
  }

  std::string AnotherUsefulFunctionB(
      const AbstractProductA &collaborator) const override {
    const std::string result = collaborator.UsefulFunctionA();
    return "The result of the B1 collaborating with ( " + result + " )";
  }
};

class ConcreteProductB2 : public AbstractProductB {
 public:
  std::string UsefulFunctionB() const override {
    return "The result of the product B2.";
  }

  std::string AnotherUsefulFunctionB(
      const AbstractProductA &collaborator) const override {
    const std::string result = collaborator.UsefulFunctionA();
    return "The result of the B2 collaborating with ( " + result + " )";
  }
};

class AbstractFactory {
 public:
  virtual AbstractProductA *CreateProductA() const = 0;
  virtual AbstractProductB *CreateProductB() const = 0;
};

class ConcreteFactory1 : public AbstractFactory {
 public:
  AbstractProductA *CreateProductA() const override {
    return new ConcreteProductA1();
  }
  AbstractProductB *CreateProductB() const override {
    return new ConcreteProductB1();
  }
};

class ConcreteFactory2 : public AbstractFactory {
 public:
  AbstractProductA *CreateProductA() const override {
    return new ConcreteProductA2();
  }
  AbstractProductB *CreateProductB() const override {
    return new ConcreteProductB2();
  }
};

void ClientCode(const AbstractFactory &factory) {
  const AbstractProductA *product_a = factory.CreateProductA();
  const AbstractProductB *product_b = factory.CreateProductB();
  std::cout << product_b->UsefulFunctionB() << "\n";
  std::cout << product_b->AnotherUsefulFunctionB(*product_a) << "\n";
  delete product_a;
  delete product_b;
}

// int main() {
//   std::cout << "Client: Testing client code with the first factory type:\n";
//   AbstractFactory *f1 = new ConcreteFactory1();
//   ClientCode(*f1);
//   delete f1;
//   std::cout << std::endl;
//   std::cout << "Client: Testing the same client code with the second factory
//   type:\n"; ConcreteFactory2 *f2 = new ConcreteFactory2(); ClientCode(*f2);
//   delete f2;
//   return 0;
// }