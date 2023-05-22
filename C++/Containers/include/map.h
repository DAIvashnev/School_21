//
// Created by ruslan on 15.05.23.
//

#ifndef CONTAINERS_INCLUDE_MAP_H_
#define CONTAINERS_INCLUDE_MAP_H_

#include <vector>

#include "rbtree.h"

namespace s21 {

template <typename Key, typename T>
class map {
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = std::size_t;

 public:
  using iterator = typename s21_utils::rbTree<
      value_type, s21_utils::mapComparator<value_type>>::iterator;
  using const_iterator = typename s21_utils::rbTree<
      value_type, s21_utils::mapComparator<value_type>>::const_iterator;

  map() = default;

  map(std::initializer_list<value_type> const &items) {
    for (auto e : items) {
      insert(e);
    }
  };

  map(const map &m) { rbTree_ = m.rbTree_; };

  map(map &&m) noexcept { rbTree_ = std::move(m.rbTree_); };

  ~map() = default;

  map &operator=(const map &other) {
    rbTree_.eraseTree();
    rbTree_ = other.rbTree_;
    return *this;
  };

  map &operator=(map &&other) noexcept {
    rbTree_ = std::move(other.rbTree_);
    return *this;
  };

  T &at(const Key &key) {
    iterator ret = rbTree_.findKey(std::make_pair(key, mapped_type{}));
    if (ret == end()) throw std::out_of_range("Bad at");
    return ret->second;
  };

  T &operator[](const Key &key) {
    auto ret = insert(key, {});
    return ret.first->second;
  }

  iterator begin() noexcept { return rbTree_.begin(); };

  iterator end() noexcept { return rbTree_.end(); };

  bool empty() const noexcept { return rbTree_.isEmpty(); }

  size_type size() const { return rbTree_.ofSize(); }

  size_type max_size() const { return rbTree_.maxSize(); }

  void clear() { rbTree_.eraseTree(); }

  void swap(map &other) noexcept {
    if (this != &other) {
      std::swap(rbTree_.header->left, other.rbTree_.header->left);
      std::swap(rbTree_.nodesNum, other.rbTree_.nodesNum);
      std::swap(rbTree_.leftmost, other.rbTree_.leftmost);
      std::swap(rbTree_.rightmost, other.rbTree_.rightmost);
    }
  };

  std::pair<iterator, bool> insert(const value_type &value) {
    return rbTree_.addNode(value, false);
    ;
  }

  std::pair<iterator, bool> insert(const Key &key, const T &obj) {
    return insert(std::make_pair(key, obj));
  }

  std::pair<iterator, bool> insert_or_assign(const Key &key, const T &obj) {
    auto pair = std::make_pair(key, obj);
    bool status = false;
    auto ret = rbTree_.findKey(pair);
    if (ret == end()) {
      insert(pair);
      status = true;
    } else {
      ret->second = obj;
    }
    return std::make_pair(ret, status);
  }

  void merge(map &other) { rbTree_.mergeTree(other.rbTree_); };

  void erase(iterator iter) { rbTree_.removeNode(iter); }

  bool contains(const Key &key) {
    return rbTree_.findKey(std::make_pair(key, mapped_type{})) != rbTree_.end();
  }

  template <typename... Args>
  s21::vector<std::pair<iterator, bool>> emplace(Args &&...args) {
    return rbTree_.emplace(args...);
  }

 private:
  s21_utils::rbTree<value_type, s21_utils::mapComparator<value_type>> rbTree_;
};
}  // namespace s21

#endif  // CONTAINERS_INCLUDE_MAP_H_
