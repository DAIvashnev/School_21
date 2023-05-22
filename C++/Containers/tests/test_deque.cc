#include <gtest/gtest.h>

#include "include/deque_suit.h"

TEST(TestDeque, initTest0) {
  s21::deque<int> TestDeq;
  ASSERT_EQ(TestDeq.size(), 0);
  ASSERT_EQ(TestDeq.GetPossibleSize(), CHANK_SIZE);
}

TEST(TestDeque, initTest1) {
  s21::deque<int> TestDeq(5);
  ASSERT_EQ(TestDeq.size(), 0);
  ASSERT_EQ(TestDeq.GetPossibleSize(), 5);
}

TEST(TestDeque, initTest2) {
  s21::deque<int> TestDeq{1, 2, 3, 4, 5};
  ASSERT_EQ(TestDeq.size(), 5);
  ASSERT_EQ(TestDeq.GetPossibleSize(), 5);
  ASSERT_EQ(TestDeq.Head(), 1);
  TestDeq.popFront();
  ASSERT_EQ(TestDeq.Head(), 2);
  TestDeq.popFront();
  ASSERT_EQ(TestDeq.Head(), 3);
  TestDeq.popFront();
  ASSERT_EQ(TestDeq.Head(), 4);
  TestDeq.popFront();
  ASSERT_EQ(TestDeq.Head(), 5);
}

TEST(TestDeque, initTestCopy) {
  s21::deque<int> TestDeq{1, 2, 3, 4, 5};
  s21::deque TestDeq2(TestDeq);
  ASSERT_EQ(TestDeq2.size(), 5);
  ASSERT_EQ(TestDeq2.GetPossibleSize(), 5);
  ASSERT_EQ(TestDeq2.Head(), 1);
  TestDeq2.popFront();
  ASSERT_EQ(TestDeq2.Head(), 2);
  TestDeq2.popFront();
  ASSERT_EQ(TestDeq2.Head(), 3);
  TestDeq2.popFront();
  ASSERT_EQ(TestDeq2.Head(), 4);
  TestDeq2.popFront();
  ASSERT_EQ(TestDeq2.Head(), 5);
}

TEST(TestDeque, initTestMove) {
  s21::deque<int> TestDeq(3);
  s21::deque TestDeq2(std::move(TestDeq));
  ASSERT_EQ(TestDeq2.size(), 0);
  ASSERT_EQ(TestDeq2.GetPossibleSize(), 3);
  TestDeq2.pushFront(3);
  ASSERT_EQ(TestDeq2.Head(), 3);
  TestDeq2.popFront();
  ASSERT_EQ(TestDeq2.size(), 0);
}

TEST(TestDeque, PushFront) {
  s21::deque<int> TestDeq(5);
  TestDeq.pushFront(0);
  TestDeq.pushFront(-1);
  ASSERT_EQ(TestDeq.size(), 2);
  ASSERT_EQ(TestDeq.GetPossibleSize(), 5);
  ASSERT_EQ(TestDeq.Head(), -1);
  TestDeq.popFront();
  ASSERT_EQ(TestDeq.Head(), 0);
}

TEST(TestDeque, PushBack) {
  s21::deque<int> TestDeq(5);
  TestDeq.pushBack(0);
  TestDeq.pushBack(1);
  ASSERT_EQ(TestDeq.size(), 2);
  ASSERT_EQ(TestDeq.GetPossibleSize(), 5);
  ASSERT_EQ(TestDeq.Tail(), 1);
  TestDeq.popBack();
  ASSERT_EQ(TestDeq.Tail(), 0);
}

TEST(TestDeque, Resize0) {
  s21::deque<int> TestDeq(3);
  TestDeq.pushBack(0);
  TestDeq.pushBack(1);
  TestDeq.pushBack(2);
  TestDeq.pushBack(3);
  TestDeq.pushBack(4);
  ASSERT_EQ(TestDeq.size(), 5);
  ASSERT_EQ(TestDeq.GetPossibleSize(), 6);
  ASSERT_EQ(TestDeq.Tail(), 4);
  TestDeq.popBack();
  ASSERT_EQ(TestDeq.Tail(), 3);
}

TEST(TestDeque, Resize1) {
  s21::deque<int> TestDeq(3);
  TestDeq.pushFront(0);
  TestDeq.pushFront(1);
  TestDeq.pushFront(2);
  TestDeq.pushFront(3);
  TestDeq.pushFront(4);
  ASSERT_EQ(TestDeq.size(), 5);
  ASSERT_EQ(TestDeq.GetPossibleSize(), 6);
  ASSERT_EQ(TestDeq.Tail(), 0);
  TestDeq.popBack();
  ASSERT_EQ(TestDeq.Tail(), 1);
}

TEST(TestDeque, EqOperator) {
  s21::deque<int> TestDeq{1, 2, 3, 4, 5};
  s21::deque<int> TestDeq1;
  TestDeq1 = TestDeq;
  ASSERT_EQ(TestDeq1.size(), 5);
  ASSERT_EQ(TestDeq1.GetPossibleSize(), 5);
  ASSERT_EQ(TestDeq1.Tail(), 5);
  TestDeq1.popBack();
  ASSERT_EQ(TestDeq1.Tail(), 4);
}

TEST(TestDeque, Swap) {
  s21::deque<int> TestDeq1{1, 2, 3, 4, 5};
  s21::deque<int> TestDeq2{5, 6, 7};
  TestDeq1.swap(TestDeq2);
  ASSERT_EQ(TestDeq1.size(), 3);
  ASSERT_EQ(TestDeq1.GetPossibleSize(), 3);
  ASSERT_EQ(TestDeq1.Tail(), 7);
  TestDeq1.popBack();
  ASSERT_EQ(TestDeq1.Head(), 5);
  ASSERT_EQ(TestDeq2.size(), 5);
  ASSERT_EQ(TestDeq2.GetPossibleSize(), 5);
  ASSERT_EQ(TestDeq2.Tail(), 5);
  TestDeq2.popBack();
  ASSERT_EQ(TestDeq2.Head(), 1);
}

TEST(TestDeque, popEmpty0) {
  s21::deque<int> TestDeq1(0);
  EXPECT_THROW(
      {
        try {
          TestDeq1.popBack();
        } catch (std::exception &err) {
          EXPECT_STREQ("The object is empty", err.what());
          throw;
        }
      },
      std::out_of_range);
}

TEST(TestDeque, popEmpty1) {
  s21::deque<int> TestDeq1(0);
  EXPECT_THROW(
      {
        try {
          TestDeq1.popFront();
        } catch (std::exception &err) {
          EXPECT_STREQ("The object is empty", err.what());
          throw;
        }
      },
      std::out_of_range);
}

TEST(TestDeque, seeEmpty0) {
  s21::deque<int> TestDeq1(0);
  EXPECT_THROW(
      {
        try {
          TestDeq1.Tail();
        } catch (std::exception &err) {
          EXPECT_STREQ("The object is empty", err.what());
          throw;
        }
      },
      std::out_of_range);
}

TEST(TestDeque, seeEmpty1) {
  s21::deque<int> TestDeq1(0);
  EXPECT_THROW(
      {
        try {
          TestDeq1.Head();
        } catch (std::exception &err) {
          EXPECT_STREQ("The object is empty", err.what());
          throw;
        }
      },
      std::out_of_range);
}

TEST(TestDeque, initTestBool0) {
  s21::deque<bool> TestDeq;
  ASSERT_EQ(TestDeq.size(), 0);
  ASSERT_EQ(TestDeq.GetPossibleSize(), CHANK_SIZE);
}

TEST(TestDeque, initTestBool1) {
  s21::deque<bool> TestDeq(5);
  ASSERT_EQ(TestDeq.size(), 0);
  ASSERT_EQ(TestDeq.GetPossibleSize(), 5);
}

TEST(TestDeque, initTestBool2) {
  s21::deque<bool> TestDeq{true, false, false, true, false};
  ASSERT_EQ(TestDeq.size(), 5);
  ASSERT_EQ(TestDeq.GetPossibleSize(), 5);
  ASSERT_EQ(TestDeq.Head(), true);
  TestDeq.popFront();
  ASSERT_EQ(TestDeq.Head(), false);
  TestDeq.popFront();
  ASSERT_EQ(TestDeq.Head(), false);
  TestDeq.popFront();
  ASSERT_EQ(TestDeq.Head(), true);
  TestDeq.popFront();
  ASSERT_EQ(TestDeq.Head(), false);
}

TEST(TestDeque, initTestBoolCopy) {
  s21::deque<bool> TestDeq{true, false, false, true, false};
  s21::deque TestDeq2(TestDeq);
  ASSERT_EQ(TestDeq2.size(), 5);
  ASSERT_EQ(TestDeq2.GetPossibleSize(), 5);
  ASSERT_EQ(TestDeq2.Head(), true);
  TestDeq2.popFront();
  ASSERT_EQ(TestDeq2.Head(), false);
  TestDeq2.popFront();
  ASSERT_EQ(TestDeq2.Head(), false);
  TestDeq2.popFront();
  ASSERT_EQ(TestDeq2.Head(), true);
  TestDeq2.popFront();
  ASSERT_EQ(TestDeq2.Head(), false);
}

TEST(TestDeque, initTestBoolMove) {
  s21::deque<bool> TestDeq(3);
  s21::deque TestDeq2(std::move(TestDeq));
  ASSERT_EQ(TestDeq2.size(), 0);
  ASSERT_EQ(TestDeq2.GetPossibleSize(), 3);
  TestDeq2.pushFront(true);
  ASSERT_EQ(TestDeq2.Head(), true);
}

TEST(TestDeque, PushFrontBool) {
  s21::deque<bool> TestDeq(5);
  TestDeq.pushFront(false);
  TestDeq.pushFront(true);
  ASSERT_EQ(TestDeq.size(), 2);
  ASSERT_EQ(TestDeq.GetPossibleSize(), 5);
  ASSERT_EQ(TestDeq.Head(), true);
  TestDeq.popFront();
  ASSERT_EQ(TestDeq.Head(), false);
}

TEST(TestDeque, PushBackBool) {
  s21::deque<bool> TestDeq(5);
  TestDeq.pushBack(false);
  TestDeq.pushBack(true);
  ASSERT_EQ(TestDeq.size(), 2);
  ASSERT_EQ(TestDeq.GetPossibleSize(), 5);
  ASSERT_EQ(TestDeq.Tail(), true);
  TestDeq.popBack();
  ASSERT_EQ(TestDeq.Tail(), false);
}

TEST(TestDeque, ResizeBool) {
  s21::deque<bool> TestDeq(3);
  TestDeq.pushBack(true);
  TestDeq.pushBack(true);
  TestDeq.pushBack(true);
  TestDeq.pushBack(false);
  TestDeq.pushBack(true);
  ASSERT_EQ(TestDeq.size(), 5);
  ASSERT_EQ(TestDeq.GetPossibleSize(), 6);
  ASSERT_EQ(TestDeq.Tail(), true);
  TestDeq.popBack();
  ASSERT_EQ(TestDeq.Tail(), false);
}

TEST(TestDeque, EqOperatorBool) {
  s21::deque<bool> TestDeq{true, false, false, true, false};
  s21::deque<bool> TestDeq1;
  TestDeq1 = TestDeq;
  ASSERT_EQ(TestDeq1.size(), 5);
  ASSERT_EQ(TestDeq1.GetPossibleSize(), 5);
  ASSERT_EQ(TestDeq1.Tail(), false);
  TestDeq1.popBack();
  ASSERT_EQ(TestDeq1.Tail(), true);
}

TEST(TestDeque, SwapBool) {
  s21::deque<bool> TestDeq1{true, false, false, true, false};
  s21::deque<bool> TestDeq2{false, true, true};
  TestDeq1.swap(TestDeq2);
  ASSERT_EQ(TestDeq1.size(), 3);
  ASSERT_EQ(TestDeq1.GetPossibleSize(), 3);

  ASSERT_EQ(TestDeq1.Tail(), true);
  ASSERT_EQ(TestDeq1.Head(), false);
  ASSERT_EQ(TestDeq2.size(), 5);
  ASSERT_EQ(TestDeq2.GetPossibleSize(), 5);
  ASSERT_EQ(TestDeq2.Tail(), false);
  ASSERT_EQ(TestDeq2.Head(), true);
}
