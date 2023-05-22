//
// Created by ruslan on 29.04.23.
//

#ifndef CONTAINERS_INCLUDE_NODE_H_
#define CONTAINERS_INCLUDE_NODE_H_

#include <algorithm>

namespace s21 {
/*
 * storage should be separate class / smart ptr?
 * Shall copy_ctor copy prev and next ptrs?
 * Change to struct
 */
template <typename T>
struct Node {
  Node *prev_, *next_;
  T storage_;

  template <typename TT>
  explicit Node(TT &&storage, Node *next = nullptr, Node *prev = nullptr)
      : prev_(prev), next_(next), storage_(std::forward<TT>(storage)) {}

  Node(const Node &other)
      : prev_(nullptr), next_(nullptr), storage_(other.storage_) {}

  Node(Node &&other) noexcept : prev_(other.prev_), next_(other.next_) {
    storage_ = std::move(other.storage_);
  }

  Node &operator=(const Node &other) & {
    if (this != &other) {
      storage_ = other.storage_;
    }
    return *this;
  }

  Node &operator=(Node &&other) noexcept {
    prev_ = other.prev_;
    next_ = other.next_;
    storage_ = std::move(other.storage_);
    return *this;
  };

  ~Node() = default;
};

}  // namespace s21

#endif  // CONTAINERS_INCLUDE_NODE_H_
