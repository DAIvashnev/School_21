#include <gtest/gtest.h>

#include "include/set_suit.h"

TEST_F(s21_set_test, Full_rb_Test) {
  srand((unsigned)time(NULL));
  for (auto i = 0; i < 7000; i++) {
    int random = rand();
    // std::cout << random << " ";
    Tree.addNode(random, false);
    s1.insert(random);
    EXPECT_EQ(1, Tree.treeCheck());
  }

  std::set<int>::iterator iter;
  std::set<int>::const_iterator citer;

  for (iter = s1.begin(); iter != s1.end(); ++iter) {
    Tree.removeNode(*iter);
    EXPECT_EQ(1, Tree.treeCheck());
  }
}

TEST_F(s21_set_test, rbTree_test_add_balance) {
  for (auto i = 0; i < 10; i++) {
    Tree.addNode(i, false);
    EXPECT_EQ(1, Tree.treeCheck());
  }

  /*
   std::cout << *Tree.begin();
 */
  Tree.removeNode(3);

  EXPECT_EQ(1, Tree.treeCheck());

  Tree.removeNode(5);

  EXPECT_EQ(1, Tree.treeCheck());

  Tree.removeNode(7);

  EXPECT_EQ(1, Tree.treeCheck());

  Tree.removeNode(4);

  EXPECT_EQ(1, Tree.treeCheck());

  Tree.removeNode(8);

  EXPECT_EQ(1, Tree.treeCheck());

  Tree.removeNode(9);

  EXPECT_EQ(1, Tree.treeCheck());

  Tree.removeNode(6);

  EXPECT_EQ(1, Tree.treeCheck());

  Tree.removeNode(1);

  EXPECT_EQ(1, Tree.treeCheck());

  Tree.removeNode(2);

  EXPECT_EQ(1, Tree.treeCheck());

  Tree.removeNode(0);

  EXPECT_EQ(1, Tree.treeCheck());
}

TEST_F(s21_set_test, rbtree_iterator_test) {
  for (auto i = 0; i < 10; i++) {
    Tree.addNode(i, false);
    s1.insert(i);
  }

  s21_utils::rbTree<int, std::less<int>>::iterator it;
  std::set<int>::iterator s_it;
  for (it = Tree.begin(), s_it = s1.begin();
       it != Tree.end() && s_it != s1.end(); ++it, ++s_it) {
    EXPECT_EQ(*it, *s_it);
  }

  s_it--;
  it--;

  for (; s_it != s1.begin() && it != Tree.begin(); --s_it, --it) {
    EXPECT_EQ(*it, *s_it);
  }

  /*
  for (auto& e : Tree) {
      std::cout << e;
  }
  */
}

TEST_F(s21_set_test, rbtree_const_iterator_test) {
  for (auto i = 0; i < 10; i++) {
    Tree.addNode(i, false);
    s1.insert(i);
  }

  s21_utils::rbTree<int, std::less<int>>::const_iterator it;
  std::set<int>::const_iterator s_it;
  for (it = Tree.cbegin(), s_it = s1.cbegin();
       it != Tree.cend() && s_it != s1.cend(); ++it, ++s_it) {
    EXPECT_EQ(*it, *s_it);
  }

  s_it--;
  it--;

  for (; s_it != s1.cbegin() && it != Tree.cbegin(); --s_it, --it) {
    EXPECT_EQ(*it, *s_it);
  }

  /*
  for (auto e : Tree) {
      std::cout << e;
  }
  */
}

TEST_F(s21_set_test, set_ins_ers_test) {
  s21::set<int> s21_set;
  for (int i = 0; i < 10; i++) {
    auto p1 = s1.insert(i);
    auto p = s21_set.insert(i);
    EXPECT_EQ(*p.first, *p1.first);
    EXPECT_EQ(p.second, p1.second);
  }

  for (auto i = 0; i < 10; i++) {
    s1.erase(i);
    s21_set.erase(i);
  }

  EXPECT_EQ(s1.empty(), s21_set.empty());
}

TEST_F(s21_set_test, set_clear_test) {
  s21::set<int> s21_set;
  for (auto i = 0; i < 10; i++) {
    auto p1 = s1.insert(i);
    auto p = s21_set.insert(i);
    EXPECT_EQ(*p.first, *p1.first);
    EXPECT_EQ(p.second, p1.second);
  }

  s1.clear();
  s21_set.clear();

  EXPECT_EQ(s1.empty(), s21_set.empty());
}

TEST_F(s21_set_test, set_swap) {
  s21::set<int> s21_set1({1, 7, 9, 2});
  s21::set<int> s21_set2({6, 2, 4, 3});
  std::set<int> set1({1, 7, 9, 2});
  std::set<int> set2({6, 2, 4, 3});

  s21_set1.swap(s21_set2);
  set1.swap(set2);

  s21::set<int>::iterator s21_it;
  std::set<int>::iterator it;

  for (s21_it = s21_set1.begin(), it = set1.begin();
       s21_it != s21_set1.end(), it != set1.end(); ++s21_it, ++it) {
    EXPECT_EQ(*it, *s21_it);
  }

  for (s21_it = s21_set2.begin(), it = set2.begin();
       s21_it != s21_set2.end(), it != set2.end(); ++s21_it, ++it) {
    EXPECT_EQ(*it, *s21_it);
  }
}

TEST_F(s21_set_test, set_find_contains) {
  s21::set<int> s21_set1({1, 7, 9, 2});
  std::set<int> set1({1, 7, 9, 2});

  s21::set<int>::iterator s21_it;
  std::set<int>::iterator it;

  s21_it = s21_set1.find(7);
  it = set1.find(7);

  EXPECT_EQ(*s21_it, *it);

  s21_it = s21_set1.find(6);
  it = set1.find(6);

  EXPECT_EQ(s21_it, s21_set1.end());
  EXPECT_EQ(it, set1.end());

  EXPECT_EQ(s21_set1.contains(7), true);
  EXPECT_EQ(s21_set1.contains(6), false);
}

TEST_F(s21_set_test, set_testbool) {
  s21::set<bool> s21_set;
  std::set<bool> set;

  s21_set.insert(true);
  s21_set.insert(3);
  s21_set.insert(6);
  s21_set.insert(8);
  s21_set.insert(0);

  set.insert(5);
  set.insert(9);
  set.insert(0);

  s21::set<bool>::iterator s21_it;
  std::set<bool>::iterator it;

  for (s21_it = s21_set.begin(), it = set.begin();
       s21_it != s21_set.end(), it != set.end(); ++s21_it, ++it) {
    EXPECT_EQ(*it, *s21_it);
  }
}

TEST_F(s21_set_test, set_merge) {
  s21::set<int> s21_set1;
  s21::set<int> s21_set2;
  std::set<int> set1;
  std::set<int> set2;

  s21_set1.insert(5);
  s21_set1.insert(3);
  s21_set1.insert(6);

  set1.insert(5);
  set1.insert(3);
  set1.insert(6);

  s21_set2.insert(8);
  s21_set2.insert(0);
  s21_set2.insert(3);

  set2.insert(8);
  set2.insert(0);
  set2.insert(3);

  s21_set1.merge(s21_set2);
  set1.merge(set2);

  s21::set<int>::iterator s21_it;
  std::set<int>::iterator it;

  for (s21_it = s21_set1.begin(), it = set1.begin();
       s21_it != s21_set1.end(), it != set1.end(); ++s21_it, ++it) {
    EXPECT_EQ(*it, *s21_it);
  }

  for (s21_it = s21_set2.begin(), it = set2.begin();
       s21_it != s21_set2.end(), it != set2.end(); ++s21_it, ++it) {
    EXPECT_EQ(*it, *s21_it);
  }

  std::multiset<int> mset;
  mset.insert(2);
}

TEST_F(s21_set_test, emplace) {
  s21::set<int> s21_set;
  std::set<int> set;

  set.emplace(3);
  s21_set.emplace(3, 4, 5, 6);

  EXPECT_EQ(*s21_set.begin(), *set.begin());
}

TEST_F(s21_set_test, assignment) {
  s21::set<int> s21_set({1, 2, 3, 6});
  s21::set<int> s21_set2({4, 2, 8, 6});
  std::set<int> set({1, 2, 3, 6});
  std::set<int> set2({4, 2, 8, 6});

  s21_set = s21_set2;
  set = set2;

  s21::set<int>::iterator s21_it;
  std::set<int>::iterator it;

  for (s21_it = s21_set.begin(), it = set.begin();
       s21_it != s21_set.end(), it != set.end(); ++s21_it, ++it) {
    EXPECT_EQ(*it, *s21_it);
  }
}

TEST_F(s21_set_test, move) {
  s21::set<int> s21_set2({4, 2, 8, 6});
  std::set<int> set({1, 2, 3, 6});
  std::set<int> set2({4, 2, 8, 6});

  s21::set<int> s21_set(std::move(s21_set2));
  set = set2;
  s21::set<int> s21_set1 = std::move(s21_set);

  s21::set<int>::iterator s21_it;
  std::set<int>::iterator it;

  for (s21_it = s21_set1.begin(), it = set.begin();
       s21_it != s21_set1.end(), it != set.end(); ++s21_it, ++it) {
    EXPECT_EQ(*it, *s21_it);
  }
}