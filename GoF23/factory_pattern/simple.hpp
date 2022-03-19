// 计算器例子

#include <iostream>

// 抽象产品角色

class Calculation {
 public:
  virtual double get_result() = 0;
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
      throw new std::exception("除数不能为0");
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
}