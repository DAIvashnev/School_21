#ifndef CONTAINERS_INCLUDE_SET_H__
#define CONTAINERS_INCLUDE_SET_H__

#include <cassert>
#include <cstddef>
#include <iostream>
#include <iterator>

#include "rbtree.h"

namespace s21 {

template <typename Key>
class set {
  using key_type = Key;
  using value_type = Key;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = std::size_t;

 public:
  using iterator =
      typename s21_utils::rbTree<Key, std::less<key_type>>::iterator;
  using const_iterator =
      typename s21_utils::rbTree<Key, std::less<key_type>>::const_iterator;

  set(){};

  set(std::initializer_list<value_type> const &list) {
    for (auto e : list) {
      insert(e);
    }
  };

  set(const set &other) { rbTree_ = other.rbTree_; };

  set(set &&other) noexcept { rbTree_ = std::move(other.rbTree_); };

  ~set(){};

  set &operator=(set &other) {
    rbTree_.eraseTree();
    rbTree_ = other.rbTree_;
    return *this;
  };

  set &operator=(set &&other) noexcept {
    rbTree_ = std::move(other.rbTree_);
    return *this;
  };

  bool empty() { return rbTree_.isEmpty(); };

  size_type size() { return rbTree_.ofSize(); };

  size_type max_size() { return rbTree_.maxSize(); };

  std::pair<iterator, bool> insert(const key_type &key) {
    return rbTree_.addNode(key, false);
  }

  iterator find(const key_type &key) { return rbTree_.findKey(key); }

  bool contains(const key_type &key) {
    iterator iter = rbTree_.findKey(key);
    if (iter != end())
      return true;
    else
      return false;
  }

  void erase(iterator iter) { rbTree_.removeNode(iter); }

  size_type erase(key_type key) { return rbTree_.removeNode(key); }

  void clear() { rbTree_.eraseTree(); }

  void swap(set &other) {
    if (this != &other) {
      std::swap(rbTree_.header->left, other.rbTree_.header->left);
      std::swap(rbTree_.nodesNum, other.rbTree_.nodesNum);
      std::swap(rbTree_.leftmost, other.rbTree_.leftmost);
      std::swap(rbTree_.rightmost, other.rbTree_.rightmost);
    }
  };

  void merge(set &other) { rbTree_.mergeTree(other.rbTree_); };

  template <typename... Args>
  s21::vector<std::pair<iterator, bool>> emplace(Args &&...args) {
    return rbTree_.emplace(args...);
  }

  set::iterator begin() noexcept { return rbTree_.begin(); };

  set::iterator end() noexcept { return rbTree_.end(); };

 private:
  s21_utils::rbTree<key_type, std::less<key_type>> rbTree_;
};

};  // namespace s21

#endif  // CONTAINERS_INCLUDE_SET_H__