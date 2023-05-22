//
// Created by ruslan on 02.05.23.
//

#ifndef CONTAINERS_INCLUDE_LIST_H_
#define CONTAINERS_INCLUDE_LIST_H_

#include <cstdlib>
#include <limits>

#include "node.h"

namespace s21 {
template <typename T>
class list {
 public:
  using size_type = std::size_t;
  using value_type = T;
  using node = Node<value_type>;
  using reference = T &;
  using const_reference = const T &;

  struct ListIterator;
  struct ConstListIterator;

  using iterator = ListIterator;
  using const_iterator = ConstListIterator;

 public:
  list() : size_(0) {}

  explicit list(size_type n) : size_(0) {
    for (size_type i = 0, ie = n; i < ie; ++i) {
      push_back({});
    }
  }

  list(const list &other) : size_(other.size_) {
    list tmp(size_);

    auto it2 = other.cbegin();
    for (auto it1 = tmp.begin(), ite = tmp.end(); it1 != ite; ++it1, ++it2) {
      *it1 = *it2;
    }
    *this = std::move(tmp);
  }

  list(list &&other) noexcept
      : head_(other.head_), tail_(other.tail_), size_(other.size_) {
    other.head_ = nullptr;
    other.tail_ = nullptr;
  }

  list(const std::initializer_list<value_type> &items) : size_(0) {
    for (auto &&i : items) {
      push_back(i);
    }
  }

  list &operator=(list &&other) &noexcept {
    size_ = other.size_;
    std::swap(head_, other.head_);
    std::swap(tail_, other.tail_);
    return *this;
  }

  list &operator=(const list &other) {
    if (this != &other) {
      list tmp = other;
      *this = std::move(tmp);
    }
    return *this;
  }

  ~list() {
    while (head_) {
      node *cur = head_;
      head_ = cur->next_;
      delete cur;
    }
  }

  iterator begin() noexcept { return iterator(head_); }

  iterator end() noexcept { return iterator(nullptr); }

  const_iterator cbegin() const noexcept { return const_iterator(head_); }

  const_iterator cend() const noexcept { return const_iterator(nullptr); }

  const_reference front() const &noexcept { return head_->storage_; }

  const_reference back() const &noexcept { return tail_->storage_; }

  bool empty() const noexcept { return head_ == nullptr; }

  size_type size() const noexcept { return size_; }

  [[nodiscard]] size_type max_size() const noexcept {
    return std::numeric_limits<size_type>::max() / sizeof(node) / 2;
  }

  void clear() {
    this->~list();
    size_ = 0;
    head_ = tail_ = nullptr;
  }

  iterator insert(iterator pos, const_reference value) {
    if (pos == end()) {
      push_back(value);
      return iterator(tail_);
    } else if (pos == begin()) {
      push_front(value);
      return begin();
    } else {
      ++size_;
      node *new_node = new node{value, pos.m_node, pos.m_node->prev_};
      pos.m_node->prev_->next_ = new_node;
      pos.m_node->prev_ = new_node;
      return iterator{new_node};
    }
  }

  iterator erase(iterator pos) {
    if (pos == begin()) {
      pop_front();
      return iterator{head_};
    } else if (pos.m_node == tail_) {
      pop_back();
      return end();
    } else {
      --size_;
      node *ret = pos.m_node->next_;
      pos.m_node->prev_->next_ = pos.m_node->next_;
      pos.m_node->next_->prev_ = pos.m_node->prev_;
      delete pos.m_node;
      return iterator{ret};
    }
  }

  void push_back(const_reference value) {
    ++size_;
    node *new_node = new node{value, nullptr, tail_};
    if (tail_) tail_->next_ = new_node;
    tail_ = new_node;
    if (!head_) head_ = tail_;
  }

  void pop_back() {
    --size_;
    node *tmp = tail_->prev_;
    delete tail_;
    tail_ = tmp;
    if (size_ < 1)
      head_ = tail_;
    else
      tail_->next_ = nullptr;
  }

  void push_front(const_reference value) {
    ++size_;
    node *new_node = new node{value, head_};
    if (head_) head_->prev_ = new_node;
    head_ = new_node;
    if (!tail_) tail_ = head_;
  }

  void pop_front() {
    --size_;
    node *tmp = head_->next_;
    delete head_;
    head_ = tmp;
    if (size_ < 1)
      tail_ = head_;
    else
      head_->prev_ = nullptr;
  }

  void swap(list &other) noexcept {
    std::swap(size_, other.size_);
    std::swap(head_, other.head_);
    std::swap(tail_, other.tail_);
  }

  void reverse() noexcept {
    if (size_ < 2) {
      return;
    }
    node *current_node = head_;
    node *next_node = nullptr;
    while (current_node != nullptr) {
      next_node = current_node->next_;
      std::swap(current_node->prev_, current_node->next_);
      current_node = next_node;
    }
    std::swap(head_, tail_);
  }

  void sort() noexcept {
    bool swapped = true;
    while (swapped && size_ > 0) {
      swapped = false;
      auto it = begin();
      auto prev = it++;
      while (it != end()) {
        if (*it < *prev) {
          std::swap(*prev, *it);
          swapped = true;
        }
        ++prev;
        ++it;
      }
    }
  }

  void unique() {
    if (size_ < 2) return;
    auto it2 = begin();
    ++it2;
    for (auto it = begin(), ite = end(); it2 != ite; ++it, ++it2) {
      while (*it == *it2) {
        iterator tmp = it2++;
        erase(tmp);
        if (it2 == end()) return;
      }
    }
  }

  void merge(list &other) {
    if (this == &other || other.empty()) {
      return;
    } else if (empty()) {
      std::swap(*this, other);
      return;
    }

    node *lhs = head_;
    node *rhs = other.head_;
    node *prev = nullptr;

    while (lhs && rhs) {
      if (rhs->storage_ < lhs->storage_) {
        node *next = rhs->next_;
        rhs->next_ = lhs;
        rhs->prev_ = prev;
        if (prev) {
          prev->next_ = rhs;
        } else {
          head_ = rhs;
        }
        lhs->prev_ = rhs;
        prev = rhs;
        rhs = next;
        ++size_;
        --other.size_;
      } else {
        prev = lhs;
        lhs = lhs->next_;
      }
    }

    if (rhs) {
      prev->next_ = rhs;
      rhs->prev_ = prev;
      tail_ = other.tail_;
      size_ += other.size_;
      other.size_ = 0;
    }

    other.head_ = nullptr;
    other.tail_ = nullptr;
  }

  void splice(iterator pos, list &other) {
    if (other.empty()) {
      return;
    } else if (empty()) {
      swap(other);
    } else {
      node *first = other.head_;
      node *last = other.tail_;
      node *before_pos_node;
      if (pos != end()) {
        before_pos_node = pos.m_node->prev_;
        pos.m_node->prev_ = last;
      } else
        before_pos_node = tail_;

      first->prev_ = before_pos_node;
      if (before_pos_node) {
        before_pos_node->next_ = first;
      } else {
        head_ = first;
      }

      last->next_ = pos.m_node;

      size_ += other.size_;
      other.head_ = nullptr;
      other.tail_ = nullptr;
      other.size_ = 0;
    }
  }

  template <typename... Args>
  void emplace_back(Args &&...args) {
    (emplace_back_single(std::forward<Args>(args)), ...);
  }

  template <typename L>
  void emplace_back_single(L &&value) {
    ++size_;
    node *new_node = new node{std::forward<L>(value), nullptr, tail_};
    if (tail_) tail_->next_ = new_node;
    tail_ = new_node;
    if (!head_) head_ = tail_;
  }

  template <typename... Args>
  void emplace_front(Args &&...args) {
    emplace(cbegin(), std::forward<Args>(args)...);
  }

  template <typename... Args>
  iterator emplace(const_iterator pos, Args &&...args) {
    if (pos == cend()) {
      emplace_back(std::forward<Args>(args)...);
      return iterator(tail_);
    } else {
      iterator it{const_cast<node *>(pos.m_node)};
      (emplace_single(it, std::forward<Args>(args)), ...);
      return --it;
    }
  }

  template <typename L>
  void emplace_single(iterator pos, L &&value) {
    ++size_;
    node *new_node =
        new node{std::forward<L>(value), pos.m_node, pos.m_node->prev_};
    if (pos.m_node->prev_) {
      pos.m_node->prev_->next_ = new_node;
    } else {
      head_ = new_node;
    }
    pos.m_node->prev_ = new_node;
  }

  struct ListIterator {
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T *;
    using reference = T &;

    ListIterator() = default;

    explicit ListIterator(node *node) noexcept : m_node(node) {}

    ListIterator(const ListIterator &other) noexcept : m_node(other.m_node){};

    ListIterator &operator=(const ListIterator &other) &noexcept {
      if (this != &other) m_node = other.m_node;
      return *this;
    };

    ListIterator &operator++() &noexcept {
      m_node = m_node->next_;
      return *this;
    }

    ListIterator operator++(int) noexcept {
      auto temp = *this;
      ++(*this);
      return temp;
    }

    ListIterator &operator--() &noexcept {
      m_node = m_node->prev_;
      return *this;
    }

    ListIterator operator--(int) noexcept {
      auto temp = *this;
      --(*this);
      return temp;
    }

    bool operator==(const ListIterator &other) const noexcept {
      return m_node == other.m_node;
    }

    bool operator!=(const ListIterator &other) const noexcept {
      return !(*this == other);
    }

    reference operator*() const &noexcept { return m_node->storage_; }

    pointer operator->() const noexcept { return &m_node->storage_; }

    friend class list;

   private:
    node *m_node = nullptr;
  };

  struct ConstListIterator {
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = const T *;
    using reference = const T &;

    ConstListIterator() = default;

    explicit ConstListIterator(node *node) noexcept : m_node(node) {}

    ConstListIterator(const ConstListIterator &other) noexcept
        : m_node{other.m_node} {};

    ConstListIterator &operator=(const ConstListIterator &other) &noexcept {
      if (this != &other) m_node = other.m_node;
      return *this;
    };

    ConstListIterator &operator++() &noexcept {
      m_node = m_node->next_;
      return *this;
    }

    ConstListIterator operator++(int) noexcept {
      auto temp = *this;
      ++(*this);
      return temp;
    }

    ConstListIterator &operator--() &noexcept {
      m_node = m_node->prev_;
      return *this;
    }

    ConstListIterator operator--(int) noexcept {
      auto temp = *this;
      --(*this);
      return temp;
    }

    bool operator==(const ConstListIterator &other) const noexcept {
      return m_node == other.m_node;
    }

    bool operator!=(const ConstListIterator &other) const noexcept {
      return !(*this == other);
    }

    reference operator*() const &noexcept { return m_node->storage_; }

    pointer operator->() const noexcept { return &m_node->storage_; }

    friend class list;

   private:
    const node *m_node = nullptr;
  };

 private:
  node *head_ = nullptr, *tail_ = nullptr;
  size_type size_;
};

}  // namespace s21

#endif  // CONTAINERS_INCLUDE_LIST_H_
