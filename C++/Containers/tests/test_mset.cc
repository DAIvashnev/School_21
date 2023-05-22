#include "gtest/gtest.h"
#include "include/mset_suit.h"

TEST_F(s21_multiset_test, rb_tree_inserteq) {
  Tree.addNode(2, true);
  Tree.addNode(3, true);
  Tree.addNode(4, true);
  Tree.addNode(6, true);
  Tree.addNode(9, true);

  Tree.addNode(3, true);
  Tree.addNode(3, true);
  Tree.addNode(3, true);

  EXPECT_EQ(1, Tree.treeCheck());

  ms1.insert(2);
  ms1.insert(3);
  ms1.insert(4);
  ms1.insert(6);
  ms1.insert(9);

  ms1.insert(3);
  ms1.insert(3);
  ms1.insert(3);

  s21_utils::rbTree<int, std::less<int>>::iterator s21_it;
  std::multiset<int>::iterator it;

  for (s21_it = Tree.begin(), it = ms1.begin();
       s21_it != Tree.end(), it != ms1.end(); ++s21_it, ++it) {
    EXPECT_EQ(*it, *s21_it);
  }
}

TEST_F(s21_multiset_test, multiset_insert) {
  s21_ms.insert(2);
  s21_ms.insert(3);
  s21_ms.insert(4);
  s21_ms.insert(6);
  s21_ms.insert(9);

  s21_ms.insert(3);
  s21_ms.insert(3);
  s21_ms.insert(3);

  ms1.insert(2);
  ms1.insert(3);
  ms1.insert(4);
  ms1.insert(6);
  ms1.insert(9);

  ms1.insert(3);
  ms1.insert(3);
  ms1.insert(3);

  s21::multiset<int>::iterator s21_it;
  std::multiset<int>::iterator it;

  for (s21_it = s21_ms.begin(), it = ms1.begin();
       s21_it != s21_ms.end(), it != ms1.end(); ++s21_it, ++it) {
    EXPECT_EQ(*it, *s21_it);
  }
}

TEST_F(s21_multiset_test, one_number) {
  std::multiset<double> ms;
  s21::multiset<double> s21ms;
  s21_utils::rbTree<double, std::less<double>> Tree;

  srand(static_cast<unsigned int>(clock()));
  double t = doubleRand();
  for (int i = 0; i < 100; i++) {
    ms.insert(t);
    s21ms.insert(t);
    Tree.addNode(t, true);
    EXPECT_EQ(Tree.treeCheck(), 1);
  }

  s21::multiset<double>::iterator s21_it;
  std::multiset<double>::iterator it;

  for (s21_it = s21ms.begin(), it = ms.begin();
       s21_it != s21ms.end(), it != ms.end(); ++s21_it, ++it) {
    EXPECT_EQ(*it, *s21_it);
  }

  EXPECT_EQ(s21ms.size(), ms.size());
}

TEST_F(s21_multiset_test, random_doubl) {
  std::multiset<double> ms;
  s21::multiset<double> s21ms;

  srand(static_cast<unsigned int>(clock()));
  for (int i = 0; i < 100; i++) {
    double t = doubleRand();
    ms.insert(t);
    s21ms.insert(t);
  }

  s21::multiset<double>::iterator s21_it;
  std::multiset<double>::iterator it;

  for (s21_it = s21ms.begin(), it = ms.begin();
       s21_it != s21ms.end(), it != ms.end(); ++s21_it, ++it) {
    EXPECT_EQ(*it, *s21_it);
  }
}

TEST_F(s21_multiset_test, multiset_erase) {
  s21_ms.insert(2);
  s21_ms.insert(3);
  s21_ms.insert(4);
  s21_ms.insert(6);
  s21_ms.insert(9);
  s21_ms.insert(3);
  s21_ms.insert(3);
  s21_ms.insert(3);

  ms1.insert(2);
  ms1.insert(3);
  ms1.insert(4);
  ms1.insert(6);
  ms1.insert(9);
  ms1.insert(3);
  ms1.insert(3);
  ms1.insert(3);

  s21::multiset<int>::iterator s21_it;
  std::multiset<int>::iterator it;

  for (s21_it = s21_ms.begin(), it = ms1.begin();
       s21_it != s21_ms.end(), it != ms1.end();) {
    s21_ms.erase(s21_it++);
    ms1.erase(it++);
  }

  EXPECT_EQ(ms1.empty(), s21_ms.empty());
}

TEST_F(s21_multiset_test, clear) {
  std::multiset<double> ms;
  s21::multiset<double> s21ms;

  srand(static_cast<unsigned int>(clock()));
  for (int i = 0; i < 100; i++) {
    double t = doubleRand();
    ms.insert(t);
    s21ms.insert(t);
  }

  ms.clear();
  s21ms.clear();

  EXPECT_EQ(ms1.empty(), s21_ms.empty());
}

TEST_F(s21_multiset_test, bounds) {
  std::multiset<int> ms({3, 7, 8, 9, 2, 2, 2, 2});
  s21::multiset<int> s21ms({3, 7, 8, 9, 2, 2, 2, 2});

  s21::multiset<int>::iterator s21_it = s21ms.upper_bound(2);
  std::multiset<int>::iterator it = ms.upper_bound(2);

  ms.lower_bound(2);

  s21ms.erase(s21_it);
  ms.erase(it);

  /*
  for ( auto e : s21ms) {
    std::cout << e << " ";
  }

  std::cout << std::endl;

  for ( auto e : ms) {
    std::cout << e << " ";
  }
  */

  int n = s21ms.count(2);
  int n2 = ms.count(2);

  EXPECT_EQ(n, n2);
}

TEST_F(s21_multiset_test, find_contains) {
  s21::multiset<int> s21ms({1, 7, 9, 2, 2, 2});
  std::multiset<int> ms({1, 7, 9, 2, 2, 2});

  s21::multiset<int>::iterator s21_it;
  std::multiset<int>::iterator it;

  s21_it = s21ms.find(2);
  it = ms.find(2);

  EXPECT_EQ(*s21_it, *it);

  s21_it = s21ms.find(6);
  it = ms.find(6);

  EXPECT_EQ(s21_it, s21ms.end());
  EXPECT_EQ(it, ms.end());

  EXPECT_EQ(s21ms.contains(7), true);
  EXPECT_EQ(s21ms.contains(6), false);
}

TEST_F(s21_multiset_test, eq_range) {
  s21::multiset<int> s21ms({1, 7, 9, 2, 2, 2, 2});
  std::multiset<int> ms({1, 7, 9, 2, 2, 2, 2});

  std::pair<s21::multiset<int>::iterator, s21::multiset<int>::iterator> p1;
  std::pair<std::multiset<int>::iterator, std::multiset<int>::iterator> p2;

  p1 = s21ms.equal_range(2);
  p2 = ms.equal_range(2);

  EXPECT_EQ(*p1.first, *p2.first);
  EXPECT_EQ(*p1.second, *p2.second);
}

TEST_F(s21_multiset_test, merge) {
  s21::multiset<int> s21ms({1, 7, 9, 2, 2, 2, 2});
  s21::multiset<int> s21ms2({1, 6, 8, 2, 2, 2, 2});
  std::multiset<int> ms({1, 7, 9, 2, 2, 2, 2});
  std::multiset<int> ms2({1, 6, 8, 2, 2, 2, 2});

  s21ms.merge(s21ms2);
  ms.merge(ms2);

  s21::multiset<int>::iterator s21_it;
  std::multiset<int>::iterator it;

  for (s21_it = s21ms.begin(), it = ms.begin();
       s21_it != s21ms.end(), it != ms.end(); ++s21_it, ++it) {
    EXPECT_EQ(*it, *s21_it);
  }
}

TEST_F(s21_multiset_test, assignment) {
  s21::multiset<int> s21ms({1, 7, 9, 2, 2, 2, 2});
  s21::multiset<int> s21ms2({1, 6, 8, 2, 2, 2, 2});
  std::multiset<int> ms({1, 7, 9, 2, 2, 2, 2});
  std::multiset<int> ms2({1, 6, 8, 2, 2, 2, 2});

  s21ms = s21ms2;
  ms = ms2;

  s21::multiset<int>::iterator s21_it;
  std::multiset<int>::iterator it;

  for (s21_it = s21ms.begin(), it = ms.begin();
       s21_it != s21ms.end(), it != ms.end(); ++s21_it, ++it) {
    EXPECT_EQ(*it, *s21_it);
  }
}

TEST_F(s21_multiset_test, move) {
  // s21::multiset<int> s21ms({1, 7, 9, 2, 2, 2, 2});
  s21::multiset<int> s21ms2({1, 6, 8, 2, 2, 2, 2});
  std::multiset<int> ms({1, 7, 9, 2, 2, 2, 2});
  std::multiset<int> ms2({1, 6, 8, 2, 2, 2, 2});

  s21::multiset<int> s21ms1(std::move(s21ms2));
  s21::multiset<int> s21ms = std::move(s21ms1);

  ms = ms2;

  s21::multiset<int>::iterator s21_it;
  std::multiset<int>::iterator it;

  for (s21_it = s21ms.begin(), it = ms.begin();
       s21_it != s21ms.end(), it != ms.end(); ++s21_it, ++it) {
    EXPECT_EQ(*it, *s21_it);
  }
}

TEST_F(s21_multiset_test, emplace) {
  s21::multiset<int> s21_mset;
  std::multiset<int> mset;

  mset.emplace(3);
  s21_mset.emplace(3, 3, 3, 3);

  EXPECT_EQ(*s21_mset.begin(), *mset.begin());

  std::map<int, int> map;
  std::map<int, int>::iterator it;

  *it;
}
