/**
 * @brief 线程安全的队列(不基于标准库容器)
 * @author Be-A-God
 * @date 2022-03-30
 */

#include <condition_variable>
#include <iostream>
#include <memory>
#include <mutex>
#include <thread>

template<class T>
class thread_safe_queue {
 public:
  thread_safe_queue();
  thread_safe_queue(const thread_safe_queue &) = delete;
  thread_safe_queue(thread_safe_queue &&) = delete;
  thread_safe_queue &operator=(const thread_safe_queue &) = delete;
  thread_safe_queue &operator=(thread_safe_queue &&) = delete;
  ~thread_safe_queue() = default;

  std::shared_ptr<T> try_pop();
  bool try_pop(T &value);
  std::shared_ptr<T> wait_and_pop();
  void wait_and_pop(T &value);
  void push(T new_value);
  bool empty();

 private:
  // 单链表模拟队列
  struct node {
    std::shared_ptr<T> data;
    std::unique_ptr<T> next;
  };
  // 队列头和队列尾的互斥锁
  std::mutex head_mutex;
  std::mutex tail_mutex;
  // 指向队头的智能指针
  std::unique_ptr<node> head;
  // 指向队尾,不需要自动销毁指向内存,使用普通指针
  node *tail;
  // 条件变量
  std::condition_variable data_cond;
  // 辅助函数,对外不开放接口
  node *get_tail();
  std::unique_ptr<node> pop_head();
  std::unique_lock<std::mutex> wait_for_data();
  std::unique_ptr<node> wait_pop_head();
  std::unique_ptr<node> wait_pop_head(T &value);
  std::unique_ptr<node> try_pop_head();
  std::unique_ptr<node> try_pop_head(T &value);
};

template<class T>
thread_safe_queue<T>::thread_safe_queue()
    : head(new thread_safe_queue::node), tail(head.get()) {}

template<class T>
std::shared_ptr<T> thread_safe_queue<T>::try_pop() {
//  辅助函数内上锁,队列不为空则返回队头指针,队列为空则返回空内容的unique_ptr
  std::unique_ptr<node> old_head = try_pop_head();
  return old_head ? old_head->data : std::shared_ptr<T>();
}

template<class T>
bool thread_safe_queue<T>::try_pop(T &value) {
  std::unique_ptr<node> const old_head = try_pop_head(value);
  return old_head;
}

template<class T>
std::shared_ptr<T> thread_safe_queue<T>::wait_and_pop() {
//  前面的辅助函数已上锁,同时确保队列中数据不为空,此处只需要调用返回即可
  std::unique_ptr<node> const old_head = wait_pop_head();
  return old_head->data;
//  队头指针离开作用域时自动销毁其内存(两个指针所占的内存,但指针所指的内存仍旧可达)
}

template<class T>
void thread_safe_queue<T>::wait_and_pop(T &value) {
//  辅助函数上锁,确保队列不为空,同时通过引用将数据传送回去
  std::unique_ptr<node> const old_head = wait_pop_head(value);
}

template<class T>
void thread_safe_queue<T>::push(T new_value) {
  std::shared_ptr<T> new_data(std::make_shared<T>(std::move(new_value)));
  std::unique_ptr<node> p(new node);
  // 以上多线程访问时,新建资源不需要加锁,无先行次序要求
  {
    std::lock_guard<std::mutex> tail_lock(tail_mutex);
    // tail 指向的节点始终空数据(虚节点)
    tail->data = new_data;
    node *const new_tail = p.get();
    tail->next = std::move(p);
    tail = new_tail;
  }
  data_cond.notify_one();
}

template<class T>
bool thread_safe_queue<T>::empty() {
  std::lock_guard<std::mutex> head_lock(head_mutex);
  return (head.get() == get_tail());
}

template<class T>
std::unique_ptr<node> thread_safe_queue<T>::pop_head() {
//  将队头指针更新并返回旧的队头指针
//  该函数为辅助函数,调用只提供内部接口,且调用前有加锁操作故此处无需加锁
  std::unique_ptr<node> old_head = std::move(head);
  head = std::move(old_head->next);
  return old_head;
}

template<class T>
std::unique_lock<std::mutex> thread_safe_queue<T>::wait_for_data() {
  // 等待队列不为空,即有数据加入
  std::unique_lock<std::mutex> head_lock(head_mutex);
  data_cond.wait(head_lock, [&] { return head.get() != get_tail(); });
  return std::move(head_lock);
}

template<class T>
std::unique_ptr<node> thread_safe_queue<T>::wait_pop_head() {
  std::unique_lock<std::mutex> head_lock(wait_for_data());
//  返回锁时证明队列中已有数据
//  此时返回队头指针
  return pop_head();
}

template<class T>
std::unique_ptr<node> thread_safe_queue<T>::wait_pop_head(T &value) {
  std::unique_lock<std::mutex> head_lock(wait_for_data());
//  返回元素值(通过引用)
  value = std::move(*head->data);
  return pop_head();
}

template<class T>
std::unique_ptr<node> thread_safe_queue<T>::try_pop_head() {
  std::lock_guard<std::mutex> head_lock(head_mutex);
  if (head.get() == get_tail()) {
    return std::unique_ptr<node>();
  }
//  队列不为空则返回指向队头的指针
  return pop_head();
}

template<class T>
std::unique_ptr<node> thread_safe_queue<T>::try_pop_head(T &value) {
  std::lock_guard<std::mutex> head_lock(head_mutex);
  if (head.get() == get_tail()) {
    return std::unique_ptr<node>();
  }
  value = std::move(*head->data);
  return pop_head();
}

template<class T>
node *thread_safe_queue<T>::get_tail() {
  std::lock_guard<std::mutex> tail_lock(tail_mutex);
  return tail;
}
