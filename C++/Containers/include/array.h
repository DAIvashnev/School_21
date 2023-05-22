#ifndef CONTAINERS_INCLUDE_ARRAY_H__
#define CONTAINERS_INCLUDE_ARRAY_H__

#include <iostream>

namespace s21 {
template <typename T, size_t N>
class array {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

 private:
  size_type size_;
  value_type data_[N];

 public:
  //
  // Functions
  //
  array() : size_(N) {}

  array(std::initializer_list<value_type> const &items) : array() {
    if (size_ < items.size())
      throw std::out_of_range("Too many initializers for s21::array");
    size_type i = 0;
    for (auto it = items.begin(); it != items.end(); it++, i++) {
      data_[i] = *it;
    }
  }

  array(const array &other) : array() {
    std::copy(other.cbegin(), other.cend(), data_);
  }

  array(array &&other) : array() {
    std::move(other.cbegin(), other.cend(), data_);
  }

  ~array(){};

  void operator=(array &other) {
    std::copy(other.cbegin(), other.cend(), data_);
  }

  void operator=(array &&other) {
    std::copy(other.cbegin(), other.cend(), data_);
  }

  //
  // Element Access
  //
  reference at(size_type pos) {
    if (!(pos < size())) throw std::out_of_range("Out of range");
    return data_[pos];
  }

  reference operator[](size_type pos) { return data_[pos]; }

  const_reference front() const { return data_[0]; }

  const_reference back() const { return data_[size_ - 1]; }

  iterator data() noexcept { return begin(); }

  //
  // Capacity
  //
  bool empty() const noexcept { return cbegin() == cend(); }

  size_type size() const noexcept { return size_; }

  size_type max_size() const noexcept { return size(); }

  //
  // Modifiers
  //
  void swap(array &other) { std::swap(*this, other); }

  void fill(const_reference value) {
    for (size_type i = 0; i < size_; i++) data_[i] = value;
  }

  iterator begin() noexcept { return data_; }

  iterator end() noexcept { return &data_[size_]; }

  const_iterator cbegin() const noexcept { return data_; }

  const_iterator cend() const noexcept { return &data_[size_]; }
};
}  // namespace s21
#endif  //  CONTAINERS_INCLUDE_ARRAY_H__