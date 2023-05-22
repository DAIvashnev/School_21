//
// Created by ruslan on 16.05.23.
//
#include <gtest/gtest.h>

#include "include/map_suit.h"

TEST_F(MapTest, base_00) {
  std::map<std::string, int> mp;
  for (int i = 0; i < 10; ++i) {
    mp[std::string(1, char('a' + i))] = i;
  }
  EXPECT_TRUE(maps_equal(map1_, mp));
  EXPECT_EQ(map1_.size(), mp.size());
  EXPECT_EQ(map1_.max_size(), mp.max_size());
  EXPECT_TRUE(map2_.empty());
  EXPECT_FALSE(map1_.empty());
}

TEST_F(MapTest, base_01) {
  map1_.clear();
  EXPECT_TRUE(map1_.empty());
}

TEST_F(MapTest, base_02) {
  std::map<std::string, int> mp;
  for (int i = 0; i < 3; ++i) {
    typename std::map<std::string, int>::value_type obj =
        std::make_pair(std::string(1, char('A' + i)), i);
    mp.insert(obj);
    map2_.insert(obj);
  }
  EXPECT_TRUE(maps_equal(map2_, mp));
  EXPECT_EQ(map2_.size(), mp.size());

  s21::map<std::string, int> m1 = map1_, m2 = map2_;
  map1_.swap(map2_);
  EXPECT_TRUE(maps_equal(map1_, m2));
}

TEST_F(MapTest, base_03) {
  std::map<std::string, int> m2, m1;
  s21::map<std::string, int> tmp{std::make_pair("A", 0), std::make_pair("B", 1),
                                 std::make_pair("C", 2)};
  map2_ = tmp;
  for (int i = 0; i < 10; ++i) {
    m1[std::string(1, char('a' + i))] = i;
  }
  for (int i = 0; i < 4; ++i) {
    m2.insert_or_assign(std::string(1, char(i != 3 ? 'A' + i : 'a')), i);
  }
  map2_.insert_or_assign("a", 3);
  EXPECT_EQ(map2_.at("a"), 3);
  map2_.insert_or_assign("a", 10);

  EXPECT_EQ(map2_.at("a"), 10);
  EXPECT_THROW(map2_.at("asdfw"), std::exception);

  m1.merge(m2);
  map1_.merge(map2_);

  EXPECT_TRUE(maps_equal(map1_, m1));
}

TEST_F(MapTest, base_04) {
  std::map<std::string, int> m2, m1;
  for (int i = 0; i < 10; ++i) {
    m1[std::string(1, char('a' + i))] = i;
  }

  EXPECT_TRUE(map1_.contains("a"));
  EXPECT_FALSE(map1_.contains("z"));

  map1_.erase(map1_.begin());
}

TEST_F(MapTest, base_05) {
  auto ret = map2_.emplace(std::make_pair("A", 1), std::make_pair("B", 2),
                           std::make_pair("C", 3));
  s21::map<std::string, int> tmp{std::make_pair("A", 1), std::make_pair("B", 2),
                                 std::make_pair("C", 3)};

  EXPECT_TRUE(maps_equal(map2_, tmp));
}