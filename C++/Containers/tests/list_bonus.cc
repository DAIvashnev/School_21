//
// Created by ruslan on 14.05.23.
//

#include <gtest/gtest.h>

#include <list>

#include "include/list_suit.h"

TEST_F(ListCtor, bonus_01) {
  s21::list<int> lst, check{1, 2, 3};
  lst.emplace_front(1, 2, 3);
  EXPECT_EQ(lst.size(), 3);
  EXPECT_TRUE(lists_equal(lst, check));
}

TEST_F(ListCtor, bonus_02) {
  s21::list<int> lst, check{1, 2, 3};
  lst.emplace_back(1, 2, 3);
  EXPECT_EQ(lst.size(), 3);
  EXPECT_TRUE(lists_equal(lst, check));
}

TEST_F(ListCtor, bonus_03) {
  s21::list<int> lst{4, 5, 6}, check{4, 1, 2, 3, 5, 6};
  auto it = lst.cbegin();
  ++it;

  auto itt = lst.emplace(it, 1, 2, 3);
  EXPECT_EQ(lst.size(), 6);
  EXPECT_TRUE(lists_equal(lst, check));
  EXPECT_EQ(*itt, 3);
}

TEST_F(ListCtor, bonus_05) {
  s21::list<int> lst{4, 5, 6}, check{1, 2, 3, 4, 5, 6};
  auto it = lst.cbegin();

  auto itt = lst.emplace(it, 1, 2, 3);
  EXPECT_EQ(lst.size(), 6);
  EXPECT_TRUE(lists_equal(lst, check));
  EXPECT_EQ(*itt, 3);
}

TEST_F(ListCtor, bonus_06) {
  s21::list<int> lst{4, 5, 6}, check{4, 5, 6, 1, 2, 3};
  auto it = lst.cend();

  auto itt = lst.emplace(it, 1, 2, 3);
  EXPECT_EQ(lst.size(), 6);
  EXPECT_TRUE(lists_equal(lst, check));
  EXPECT_EQ(*itt, 3);
}

TEST_F(ListCtor, bonus_07) {
  s21::list<int> lst, check{1, 2, 3};
  auto it = lst.cbegin();

  auto itt = lst.emplace(it, 1, 2, 3);
  EXPECT_EQ(lst.size(), 3);
  EXPECT_TRUE(lists_equal(lst, check));
  EXPECT_EQ(*itt, 3);
}