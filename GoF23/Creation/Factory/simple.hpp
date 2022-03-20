// 计算器例子

// 使用工厂类静态方法去生成相应产品
// 可以使用工厂对象生成产品，但是不如工厂类静态方法
// 使用函数生成也可以，但缺少封装
// 综合 使用工厂类静态方法最合适（无需定义对象+封装）
// 具体产品从抽象产品中派生，利用多态和继承实现具体对象的创建

#include <exception>
#include <iostream>

// 抽象产品角色

class Calculation {
 public:
  virtual double get_result() = 0;
  virtual ~Calculation() = default;
  double number_1;
  double number_2;
};

// 具体产品角色

class Add : public Calculation {
  double get_result() override { return number_1 + number_2; }
};

class Sub : public Calculation {
  double get_result() override { return number_1 - number_2; }
};

class Multi : public Calculation {
  double get_result() override { return number_1 * number_2; }
};

class Div : public Calculation {
  double get_result() override {
    if (number_2 == 0) {
      throw new std::exception();
    }
    return number_1 / number_2;
  }
};

// 工厂角色

class Factory {
 public:
  static Calculation* create_calculation(char str) {
    Calculation* calc = nullptr;
    switch (str) {
      case '+':
        calc = new Add;
        break;
      case '-':
        calc = new Sub;
        break;
      case '*':
        calc = new Multi;
        break;
      case '/':
        calc = new Div;
        break;
      default:
        std::cout << "输入正确运算符" << std::endl;
        break;
    }
    return calc;
  }
};