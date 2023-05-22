#ifndef CONTAINERS_INCLUDE_STACK_H__
#define CONTAINERS_INCLUDE_STACK_H__

#include "deque.h"

namespace s21 {
template <typename _Tp, typename _Sequence = deque<_Tp> >
class stack {
 public:
  typedef typename _Sequence::value_type value_type;
  typedef typename _Sequence::reference reference;
  typedef typename _Sequence::const_reference const_reference;
  typedef typename _Sequence::size_type size_type;

 protected:
  _Sequence c;

 public:
  stack() : c(){};

  explicit stack(size_type max_size) : c(max_size){};

  stack(const stack &s) : c(s.c){};

  stack(stack &&s) : c(std::move(s.c)){};

  explicit stack(std::initializer_list<value_type> const &items) : c(items){};

  ~stack(){};

  void pop() { c.popBack(); };

  void push(const_reference value) { return c.pushBack(value); };

  bool empty() { return c.empty(); };

  const_reference top() { return c.Tail(); };

  size_type size() { return c.size(); };

  void swap(stack &other) { c.swap(other.c); };

  stack<value_type> &operator=(stack &&s) {
    c = std::move(s.c);
    return *this;
  }

  template <class... Args>
  void emplace_front(Args &&...args) {
    for (auto value : {std::forward<Args>(args)...}) {
      c.pushBack(value);
    }
  }

  stack<value_type> &operator=(const stack &s) {
    c = s.c;
    return *this;
  };
};

}  // namespace s21
#endif  // CONTAINERS_INCLUDE_STACK_H__