/**
 * @file test.cpp
 * @author Be-A-God (wx1028674648@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-03-21
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <iostream>
#include <list>

// 组合模式重点在于增减方式和内部的逻辑结构
// 常用list或vector容器
// 由抽象组件提供所有接口声明
// 叶结点和枝干选择相应接口实现
// 注意内存管理和遍历的递归调用
class Component {
 protected:
  std::string node_name;

 public:
  Component(std::string name) : node_name(name) {}
  virtual ~Component() {}
  virtual bool is_composite() = 0;
  virtual void add_node(Component*) = 0;
  virtual void remove_node(Component*) = 0;
  virtual void operation() = 0;
  virtual std::string get_name() const = 0;
  virtual std::string list_tree() = 0;
  virtual Component* get_child(std::string name) = 0;
};

class Leaf : public Component {
 public:
  Leaf(std::string name) : Component(name) {}
  ~Leaf() {}
  bool is_composite() override { return false; }
  void add_node(Component*) override {}
  void remove_node(Component*) override {}
  void operation() override { std::cout << "I'm " << node_name << std::endl; }
  std::string get_name() const override { return node_name; }
  std::string list_tree() override { return "( " + this->get_name() + " )"; }
  Component* get_child(std::string name) override { return nullptr; }
};

class Composite : public Component {
 public:
  Composite(std::string name) : Component(name) {}
  ~Composite() {
    auto it = composite.begin();
    while (it != composite.end()) {
      if (*it != nullptr) {
        std::cout << "delete " << (*it)->get_name() << std::endl;
        delete *it;
        *it = nullptr;
      }
      composite.erase(it);
      it = composite.begin();
    }
  }
  bool is_composite() override { return true; }
  void add_node(Component* node) override { composite.push_back(node); }
  void remove_node(Component* node) override {
    for (auto it = composite.begin(); it != composite.end(); it++) {
      if ((*it)->get_name() == node->get_name()) {
        if (*it != nullptr) {
          delete *it;
          *it = nullptr;
        }
        composite.erase(it);
        break;
      }
    }
  }
  void operation() override { std::cout << "I'm " << node_name << std::endl; }
  std::string get_name() const override { return node_name; }

  std::string list_tree() override {
    std::string result = this->get_name();
    for (Component* i : composite) {
      if (i == composite.back()) {
        result += i->list_tree();
      } else {
        result += i->list_tree() + " + ";
      }
    }
    return "( " + result + " )";
  }

  Component* get_child(std::string name) override {
    for (auto it = composite.begin(); it != composite.end(); it++) {
      if ((*it)->get_name() == name) {
        return *it;
      }
    }
  }

 private:
  // 容器存放指针，需要手动释放
  // 客户端只需要delete根节点就可以完成所有内存的释放
  std::list<Component*> composite;
};

int main(int argc, char const* argv[]) {
  Component* root = new Composite("学校");
  Component* leaf = new Composite("食堂");
  Component* branch_left = new Composite("教学楼");
  Component* branch_right = new Composite("生活区");
  Component* leaf_1 = new Leaf("学生");
  Component* leaf_2 = new Leaf("老师");
  Component* leaf_3 = new Leaf("清洁工");

  branch_left->operation();
  branch_right->operation();
  leaf_1->operation();
  leaf_2->operation();
  root->operation();

  branch_left->add_node(leaf_2);
  branch_left->add_node(leaf_3);
  branch_right->add_node(leaf_1);
  root->add_node(branch_left);
  root->add_node(leaf);
  root->add_node(branch_right);

  std::cout << "Tree: " << root->list_tree() << std::endl;

  delete root;
  return 0;
}
