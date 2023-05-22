#ifndef CONTAINERS_TESTS_MULTISET_SUIT_H
#define CONTAINERS_TESTS_MULTISET_SUIT_H

#include <gtest/gtest.h>

#include <algorithm>
#include <ctime>
#include <set>

#include "multiset.h"
#include "rbtree.h"

double doubleRand() { return double(rand()) / (double(RAND_MAX) + 1.0); }

class s21_multiset_test : public ::testing::Test {
 public:
  s21_utils::rbTree<int, std::less<int>> Tree;
  std::multiset<int> ms1;
  s21::multiset<int> s21_ms;
};

#endif  // CONTAINERS_TESTS_MULTISET_SUIT_H