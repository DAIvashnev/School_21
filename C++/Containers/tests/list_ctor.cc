//
// Created by ruslan on 14.05.23.
//

#include <gtest/gtest.h>

#include <list>

#include "include/list_suit.h"

TEST_F(ListCtor, ctor_01) {
  s21::list<int> lst;
  EXPECT_EQ(lst.size(), 0);
  EXPECT_EQ(lst.begin(), lst.end());
  EXPECT_TRUE(lst.empty());
}

TEST_F(ListCtor, ctor_02) {
  s21::list<int> lst(3);
  std::list<int> lst_stl{int{}, int{}, int{}};
  EXPECT_EQ(lst.size(), 3);
  EXPECT_TRUE(lists_equal(lst, lst_stl));
}

TEST_F(ListCtor, ctor_03) {
  s21::list<int> lst{1, 2, 3};
  std::list<int> lst_stl{1, 2, 3};
  EXPECT_EQ(lst.size(), 3);
  EXPECT_TRUE(lists_equal(lst, lst_stl));
}

TEST_F(ListCtor, ctor_04) {
  s21::list<int> tmp{1, 2, 3};
  s21::list<int> lst = tmp;
  std::list<int> lst_stl{1, 2, 3};
  EXPECT_EQ(lst.size(), 3);
  EXPECT_TRUE(lists_equal(lst, lst_stl));
}

TEST_F(ListCtor, ctor_05) {
  s21::list<int> tmp{1, 2, 3};
  s21::list<int> lst = std::move(tmp);
  std::list<int> lst_stl{1, 2, 3};
  EXPECT_EQ(lst.size(), 3);
  EXPECT_TRUE(lists_equal(lst, lst_stl));
}

TEST_F(ListCtor, ctor_06) {
  s21::list<int> tmp{1, 2, 3};
  s21::list<int> lst;
  lst = tmp;
  std::list<int> lst_stl{1, 2, 3};
  EXPECT_EQ(lst.size(), 3);
  EXPECT_TRUE(lists_equal(lst, lst_stl));
}

TEST_F(ListCtor, ctor_07) {
  s21::list<int> tmp{1, 2, 3};
  s21::list<int> lst;
  lst = std::move(tmp);
  std::list<int> lst_stl{1, 2, 3};
  EXPECT_EQ(lst.size(), 3);
  EXPECT_TRUE(lists_equal(lst, lst_stl));
}

TEST_F(ListCtor, ctor_08) {
  s21::list<int> lst{1, 2, 3};
  lst = lst;
  std::list<int> lst_stl{1, 2, 3};
  EXPECT_EQ(lst.size(), 3);
  EXPECT_TRUE(lists_equal(lst, lst_stl));
}

TEST_F(ListCtor, ctor_09) {
  s21::list<int> lst{1, 2, 3};
  lst = std::move(lst);
  std::list<int> lst_stl{1, 2, 3};
  EXPECT_EQ(lst.size(), 3);
  EXPECT_TRUE(lists_equal(lst, lst_stl));
}