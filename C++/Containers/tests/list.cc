//
// Created by ruslan on 12.05.23.
//
#include <gtest/gtest.h>

#include <list>

#include "include/list_suit.h"

TEST_F(ListTest, base_01) {
  std::list<int> org;
  for (int i = 0; i < 10; ++i) {
    org.push_back(i);
  }

  EXPECT_EQ(org.size(), lst1_.size());
  EXPECT_EQ(org.max_size(), lst1_.max_size());
  EXPECT_TRUE(lists_equal(lst1_, org));
}

TEST_F(ListTest, base_02) {
  std::list<int> org{7, 5, 2, 9};
  EXPECT_EQ(org.size(), lst2_.size());
  EXPECT_TRUE(lists_equal(lst2_, org));
}

TEST_F(ListTest, base_03) {
  EXPECT_EQ(lst1_.front(), 0);
  EXPECT_EQ(*lst1_.begin(), 0);
  EXPECT_EQ(*lst1_.cbegin(), 0);
  EXPECT_EQ(lst1_.back(), 9);
}

TEST_F(ListTest, base_04) {
  lst1_.clear();
  EXPECT_EQ(lst1_.size(), 0);
  EXPECT_TRUE(lst1_.empty());
}

TEST_F(ListTest, base_05) {
  auto ret = lst1_.insert(lst1_.begin(), -1);
  EXPECT_TRUE(ret == lst1_.begin());
  EXPECT_EQ(lst1_.size(), 11);
  EXPECT_EQ(*lst1_.begin(), -1);

  ret = lst1_.insert(lst1_.end(), 10);
  EXPECT_EQ(lst1_.size(), 12);
  EXPECT_EQ(*ret, 10);

  ret = lst1_.insert(ret, 20);
  EXPECT_EQ(lst1_.size(), 13);

  std::list<int> lst_org{-1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 20, 10};
  lists_equal(lst1_, lst_org);

  ret = lst1_.erase(ret);
  EXPECT_EQ(lst1_.size(), 12);

  ret = lst1_.erase(ret);
  EXPECT_EQ(lst1_.size(), 11);
  EXPECT_EQ(ret, lst1_.end());

  ret = lst1_.erase(lst1_.begin());
  EXPECT_EQ(lst1_.size(), 10);
  EXPECT_EQ(ret, lst1_.begin());

  lst1_.clear();
  EXPECT_TRUE(lst1_.empty());
  lst1_.push_back(1);
  lst1_.pop_back();
  EXPECT_TRUE(lst1_.empty());
  lst1_.push_back(1);
  lst1_.pop_front();
  EXPECT_TRUE(lst1_.empty());

  s21::list<int> tmp;
  tmp.insert(tmp.begin(), 1);
  EXPECT_EQ(tmp.size(), 1);
  EXPECT_EQ(*tmp.begin(), 1);
}

TEST_F(ListTest, base_06) {
  s21::list<int> l1 = lst1_, l2 = lst2_, tmp;

  lst1_.swap(lst2_);
  EXPECT_TRUE(lists_equal(lst1_, l2));
  EXPECT_TRUE(lists_equal(lst2_, l1));

  std::list<int> lst_org{9, 2, 5, 7};
  lst1_.reverse();
  EXPECT_TRUE(lists_equal(lst1_, lst_org));
  lst_org.sort();
  lst1_.sort();
  EXPECT_TRUE(lists_equal(lst1_, lst_org));

  tmp.reverse();
  EXPECT_TRUE(tmp.empty());
}

TEST_F(ListTest, base_07) {
  s21::list<int> tmp, l1 = lst1_, l2 = lst2_, lst_empty;
  lst1_.splice(lst1_.begin(), tmp);
  EXPECT_TRUE(lists_equal(l1, lst1_));

  tmp.splice(tmp.begin(), lst2_);
  EXPECT_TRUE(lists_equal(tmp, l2));

  l1.splice(l1.end(), l2);
  std::list<int> lst_org_0{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 7, 5, 2, 9};
  EXPECT_TRUE(lists_equal(l1, lst_org_0));

  lst1_.splice(lst1_.begin(), tmp);
  std::list<int> lst_org_1{7, 5, 2, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  EXPECT_TRUE(lists_equal(l1, lst_org_0));

  lst1_.sort();
  std::list<int> lst_org{0, 1, 2, 2, 3, 4, 5, 5, 6, 7, 7, 8, 9, 9};
  EXPECT_TRUE(lists_equal(lst1_, lst_org));

  lst1_.unique();
  lst_org.unique();
  EXPECT_TRUE(lists_equal(lst1_, lst_org));

  lst1_.unique();
  EXPECT_TRUE(lists_equal(lst1_, lst_org));

  lst_empty.unique();
  EXPECT_TRUE(lst_empty.empty());
}

TEST_F(ListTest, base_08) {
  lst2_.sort();
  lst1_.push_back(10);
  s21::list<int> tmp, l1 = lst1_, l2 = lst2_;

  lst1_.merge(lst1_);
  EXPECT_EQ(lst1_.size(), 11);
  EXPECT_TRUE(lists_equal(l1, lst1_));

  lst1_.merge(tmp);
  EXPECT_TRUE(tmp.empty());
  EXPECT_EQ(tmp.size(), 0);
  EXPECT_TRUE(lists_equal(l1, lst1_));

  tmp.merge(lst1_);
  EXPECT_TRUE(lst1_.empty());
  EXPECT_EQ(lst1_.size(), 0);
  EXPECT_TRUE(lists_equal(l1, tmp));

  lst2_.merge(tmp);
  EXPECT_TRUE(tmp.empty());
  EXPECT_EQ(tmp.size(), 0);
  std::list<int> lst_org{0, 1, 2, 2, 3, 4, 5, 5, 6, 7, 7, 8, 9, 9, 10};
  EXPECT_EQ(lst2_.size(), 15);
  EXPECT_TRUE(lists_equal(lst2_, lst_org));

  lst2_.merge(l2);
  EXPECT_EQ(lst2_.size(), 19);
}
