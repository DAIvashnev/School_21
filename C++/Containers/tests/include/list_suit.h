//
// Created by ruslan on 12.05.23.
//

#ifndef CONTAINERS_TESTS_LIST_SUIT_H_
#define CONTAINERS_TESTS_LIST_SUIT_H_

#include <gtest/gtest.h>

#include "list.h"

class ListTest : public ::testing::Test {
 protected:
  s21::list<int> lst1_, lst2_;

  void SetUp() override {
    for (int i = 0; i < 10; ++i) {
      lst1_.push_back(i);
    }

    lst2_.push_front(9);
    lst2_.push_front(2);
    lst2_.push_front(5);
    lst2_.push_front(7);
  }

  void TearDown() override {}
};

class ListCtor : public ::testing::Test {
 protected:
  void SetUp() override {}

  void TearDown() override {}
};

template <class T>
bool lists_equal(s21::list<T> &first, const std::list<T> &second) {
  if (first.size() != second.size()) return false;
  auto it = first.begin(), ite = first.end();
  auto it2 = second.begin();
  for (; it != ite; ++it, ++it2) {
    if (*it != *it2) return false;
  }
  return true;
}

template <class T>
bool lists_equal(s21::list<T> &first, s21::list<T> &second) {
  if (first.size() != second.size()) return false;
  auto it = first.begin(), ite = first.end(), it2 = second.begin();
  for (; it != ite; ++it, ++it2) {
    if (*it != *it2) return false;
  }
  return true;
}

#endif  // CONTAINERS_TESTS_LIST_SUIT_H_
