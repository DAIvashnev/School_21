//
// Created by ruslan on 17.05.23.
//

#ifndef CONTAINERS_TESTS_MAP_SUIT_H
#define CONTAINERS_TESTS_MAP_SUIT_H

#include <gtest/gtest.h>

#include "map.h"

class MapTest : public ::testing::Test {
 protected:
  s21::map<std::string, int> map1_, map2_;

  void SetUp() override {
    for (int i = 0; i < 10; ++i) {
      map1_[std::string(1, char('a' + i))] = i;
    }
  }

  void TearDown() override {}
};

template <class K, class T>
bool maps_equal(s21::map<K, T> &first, const std::map<K, T> &second) {
  if (first.size() != second.size()) return false;
  auto it = first.begin(), ite = first.end();
  auto it2 = second.begin();
  for (; it != ite; ++it, ++it2) {
    if (it->first != it2->first || it->second != it->second) return false;
  }
  return true;
}

template <class K, class T>
bool maps_equal(s21::map<K, T> &first, s21::map<K, T> &second) {
  if (first.size() != second.size()) return false;
  auto it = first.begin(), ite = first.end(), it2 = second.begin();
  for (; it != ite; ++it, ++it2) {
    if (it->first != it2->first || it->second != it->second) return false;
  }
  return true;
}

#endif  // CONTAINERS_TESTS_MAP_SUIT_H
