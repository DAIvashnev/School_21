#ifndef CONTAINERS_INCLUDE_DEQUE_H_
#define CONTAINERS_INCLUDE_DEQUE_H_

#include <cstdlib>
#include <iostream>

namespace s21 {
#define CHANK_SIZE 102

template <typename T>
class deque {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = std::size_t;

 private:
  value_type *values;
  int possible_size, head, tail;
  size_type size_;

 protected:
  int GetHead() const noexcept { return head; };

  int GetTail() const noexcept { return tail; };

 public:
  deque() : deque(CHANK_SIZE){};

  explicit deque(size_type max_size) : head(-1), tail(0), size_(0) {
    values = new value_type[max_size];
    possible_size = (int)max_size;
  };

  explicit deque(std::initializer_list<value_type> const &items)
      : deque(items.size()) {
    int j = 0;
    for (auto i : items) {
      new (values + j) T(i);
      j++;
    }
    size_ = items.size();
    head = -1;
    tail = items.size();
  };

  deque(const deque &other) : deque(other.possible_size) {
    for (size_t i = 0; i < other.size_; i++) {
      values[i] = other.values[i];
    }
    tail = other.size_;
    size_ = other.size_;
  };

  deque(deque &&other) {
    values = other.values;
    tail = other.tail;
    size_ = other.size_;
    head = other.head;
    possible_size = other.possible_size;
    other.values = nullptr;
    other.size_ = 0;
    other.possible_size = 0;
    other.head = -1;
    other.tail = 0;
  };

  ~deque() noexcept {
    clear_values();
    values = nullptr;
    size_ = 0;
    possible_size = 0;
    head = 0;
    tail = 0;
  };

  void popBack() {
    if (size_ == 0) {
      throw std::out_of_range("The object is empty");
    } else {
      size_--;
      --tail;
    }
  };

  reference Tail() {
    if (size_ == 0) {
      throw std::out_of_range("The object is empty");
    }
    return operator[]((tail - 1));
  };

  reference Head() {
    if (size_ == 0) {
      throw std::out_of_range("The object is empty");
    }
    return operator[]((head + 1));
  };

  void popFront() {
    if (size_ == 0) {
      throw std::out_of_range("The object is empty");
    } else {
      size_--;
      ++head;
    }
  };

  void pushBack(const_reference elem) noexcept {
    if (tail == head + possible_size + 1) resize();
    operator[](tail++) = elem;
    size_++;
  };

  void pushFront(const_reference elem) noexcept {
    if (tail == head + possible_size + 1) resize();
    operator[](head--) = elem;
    size_++;
  };

  void swap(deque &other) noexcept {
    deque tmp(other);
    other = *this;
    *this = tmp;
  }

  bool empty() const noexcept { return size_ == 0; };

  size_type size() const noexcept { return size_; };

  int GetPossibleSize() const noexcept { return possible_size; };

  value_type &operator[](int i) {
    if (i < 0)
      i += possible_size;
    else if (i > possible_size)
      i %= possible_size;
    return values[i];
  };

  deque<value_type> &operator=(const deque &other) {
    if (this != &other) {
      possible_size = other.possible_size;
      clear_values();
      deep_copy(other);
    }
    return *this;
  };

  deque<value_type> &operator=(deque &&other) {
    if (this != other) {
      possible_size = other.possible_size;
      clear_values();
      values = other.values;
      head = other.head;
      tail = other.tail;
      size_ = other.size_;
    }
    return *this;
  };

 private:
  void deep_copy(deque other) {
    values = new value_type[possible_size];
    for (size_t i = 0; i < other.size(); i++) {
      values[i] = other[other.head + i + 1];
    }
    head = -1;
    tail = other.size_;
    size_ = other.size_;
  }

  void resize() {
    deque tmp(*this);
    clear_values();
    possible_size *= 2;
    deep_copy(tmp);
  }

  void clear_values() {
    if (values) delete[] values;
  }
};

}  // namespace s21

#endif  // CONTAINERS_INCLUDE_DEQUE_H_
