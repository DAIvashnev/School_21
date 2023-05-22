#ifndef CONTAINERS_INCLUDE_QEQUE_H_
#define CONTAINERS_INCLUDE_QEQUE_H_

#include "deque.h"

namespace s21 {
template <typename _Tp, typename _Sequence = deque<_Tp> >
class queue {
 public:
  typedef typename _Sequence::value_type value_type;
  typedef typename _Sequence::reference reference;
  typedef typename _Sequence::const_reference const_reference;
  typedef typename _Sequence::size_type size_type;

 protected:
  _Sequence c;

 public:
  queue() : c(){};

  explicit queue(int max_size) : c(max_size){};

  queue(const queue &q) : c(q.c){};

  queue(queue &&q) : c(std::move(q.c)){};

  explicit queue(std::initializer_list<value_type> const &items) : c(items){};

  ~queue(){};

  void pop() { c.popFront(); };

  void push(value_type elem) { return c.pushBack(elem); };

  bool empty() { return c.empty(); };

  const_reference front() { return c.Head(); }

  const_reference back() { return c.Tail(); }

  size_type size() { return c.size(); }

  void swap(queue &other) { c.swap(other.c); };

  template <class... Args>
  void emplace_back(Args &&...args) {
    for (auto value : {std::forward<Args>(args)...}) {
      c.pushBack(value);
    }
  }

  queue<value_type> &operator=(queue &q) {
    c = q.c;
    return *this;
  };

  queue<value_type> &operator=(queue &&q) {
    c = std::move(q.c);
    return *this;
  }
};

}  // namespace s21
#endif  // CONTAINERS_INCLUDE_QEQUE_H_