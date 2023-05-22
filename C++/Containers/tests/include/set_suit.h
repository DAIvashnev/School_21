#ifndef CONTAINERS_TESTS_SET_SUIT_H
#define CONTAINERS_TESTS_SET_SUIT_H

#include <gtest/gtest.h>

#include <algorithm>
#include <set>

#include "rbtree.h"
#include "set.h"

class s21_set_test : public ::testing::Test {
 public:
  s21_utils::rbTree<int, std::less<int>> Tree;
  std::set<int> s1;
};

#endif  // CONTAINERS_TESTS_SET_SUIT_H