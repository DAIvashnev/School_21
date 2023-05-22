#ifndef CONTAINERS_INCLUDE_MULTISET_H__
#define CONTAINERS_INCLUDE_MULTISET_H__

#pragma once

#include <cassert>
#include <cstddef>
#include <iostream>
#include <iterator>

#include "rbtree.h"

namespace s21 {

template <typename Key>
class multiset {
  using key_type = Key;
  using value_type = Key;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = std::size_t;

 public:
  using iterator = typename s21_utils::rbTree<Key, std::less<Key>>::iterator;
  using const_iterator =
      typename s21_utils::rbTree<Key, std::less<Key>>::const_iterator;

  multiset(){};

  multiset(std::initializer_list<value_type> const &list) {
    for (auto e : list) {
      insert(e);
    }
  };

  multiset(const multiset &other) { rbTree_.copyEqual(other.rbTree_); };

  multiset(multiset &&other) noexcept { rbTree_ = std::move(other.rbTree_); };

  ~multiset() = default;

  multiset operator=(multiset &other) {
    rbTree_.eraseTree();
    rbTree_.copyEqual(other.rbTree_);
    return *this;
  };

  multiset operator=(multiset &&other) noexcept {
    rbTree_ = std::move(other.rbTree_);
    return *this;
  };

  iterator begin() { return rbTree_.begin(); };

  iterator end() { return rbTree_.end(); };

  iterator lower_bound(const key_type &key) {
    return rbTree_.lower_bound(key);
  };

  iterator upper_bound(const key_type &key) {
    return rbTree_.upper_bound(key);
  };

  bool empty() { return rbTree_.isEmpty(); };

  size_type size() { return rbTree_.ofSize(); };

  size_type max_size() { return rbTree_.maxSize(); };

  std::pair<iterator, bool> insert(const key_type &key) {
    auto res = rbTree_.addNode(key, true);
    return std::make_pair(res.first, res.second);
  }

  iterator find(const key_type &key) { return rbTree_.findKey(key); }

  bool contains(const key_type &key) {
    iterator iter = rbTree_.findKey(key);
    if (iter != end())
      return true;
    else
      return false;
  }

  size_type count(const key_type &key) {
    iterator temp = lower_bound(key);
    iterator upper = upper_bound(key);
    size_type count = 0;
    while (temp != upper) {
      ++temp;
      count++;
    }
    return count;
  }

  std::pair<iterator, iterator> equal_range(const Key &key) {
    return std::make_pair(lower_bound(key), upper_bound(key));
  }

  iterator erase(iterator iter) { return rbTree_.removeNode(iter); }

  void clear() { rbTree_.eraseTree(); }

  void swap(multiset &other) {
    if (this != &other) {
      std::swap(rbTree_.header->left, other.rbTree_.header->left);
      std::swap(rbTree_.nodesNum, other.rbTree_.nodesNum);
      std::swap(rbTree_.leftmost, other.rbTree_.leftmost);
      std::swap(rbTree_.rightmost, other.rbTree_.rightmost);
    }
  };

  void merge(multiset &other) { rbTree_.mergeTreeEqual(other.rbTree_); };

  template <typename... Args>
  s21::vector<std::pair<iterator, bool>> emplace(Args &&...args) {
    return rbTree_.emplaceMulti(args...);
  }

 private:
  s21_utils::rbTree<value_type, std::less<key_type>> rbTree_;
};

};  // namespace s21

#endif  // CONTAINERS_INCLUDE_MULTISET_H__
