#include <gtest/gtest.h>

#include "include/queue_suit.h"

TEST(TestQueue, initTest0) {
  s21::queue<int> TestQueue;
  ASSERT_EQ(TestQueue.size(), 0);
}

TEST(TestQueue, initTest1) {
  s21::queue<int> TestQueue(5);
  ASSERT_EQ(TestQueue.size(), 0);
}

TEST(TestQueue, initTest2) {
  s21::queue<int> TestQueue{1, 2, 3, 4, 5};
  ASSERT_EQ(TestQueue.size(), 5);
  ASSERT_EQ(TestQueue.front(), 1);
  TestQueue.pop();
  ASSERT_EQ(TestQueue.front(), 2);
  TestQueue.pop();
  ASSERT_EQ(TestQueue.front(), 3);
  TestQueue.pop();
  ASSERT_EQ(TestQueue.front(), 4);
  TestQueue.pop();
  ASSERT_EQ(TestQueue.front(), 5);
}

TEST(TestQueue, initTestCopy) {
  s21::queue<int> TestQueue1{1, 2, 3, 4, 5};
  s21::queue TestQueue2(TestQueue1);
  ASSERT_EQ(TestQueue2.size(), 5);
  ASSERT_EQ(TestQueue2.front(), 1);
  TestQueue2.pop();
  ASSERT_EQ(TestQueue2.front(), 2);
  TestQueue2.pop();
  ASSERT_EQ(TestQueue2.front(), 3);
  TestQueue2.pop();
  ASSERT_EQ(TestQueue2.front(), 4);
  TestQueue2.pop();
  ASSERT_EQ(TestQueue2.front(), 5);
}

TEST(TestQueue, initTestMove) {
  s21::queue<int> TestQueue1(3);
  s21::queue TestQueue2(std::move(TestQueue1));
  ASSERT_EQ(TestQueue2.size(), 0);
  TestQueue2.push(3);
  ASSERT_EQ(TestQueue2.front(), 3);
  ASSERT_EQ(TestQueue2.back(), 3);
}

TEST(TestQueue, Push) {
  s21::queue<int> TestQueue(5);
  TestQueue.push(0);
  TestQueue.push(-1);
  ASSERT_EQ(TestQueue.size(), 2);
  ASSERT_EQ(TestQueue.front(), 0);
  ASSERT_EQ(TestQueue.back(), -1);
}

TEST(TestQueue, EmplaceBack) {
  s21::queue<int> TestQueue({1, 4});
  ASSERT_EQ(TestQueue.size(), 2);
  ASSERT_EQ(TestQueue.front(), 1);
  TestQueue.emplace_back(3);
  ASSERT_EQ(TestQueue.size(), 3);
  ASSERT_EQ(TestQueue.back(), 3);
  TestQueue.emplace_back(1, 2);
  ASSERT_EQ(TestQueue.back(), 2);
  ASSERT_EQ(TestQueue.size(), 5);
}

TEST(TestQueue, Resize) {
  s21::queue<int> TestQueue(3);
  TestQueue.push(0);
  TestQueue.push(1);
  TestQueue.push(2);
  TestQueue.push(3);
  TestQueue.push(4);
  ASSERT_EQ(TestQueue.size(), 5);
  ASSERT_EQ(TestQueue.front(), 0);
  TestQueue.pop();
  ASSERT_EQ(TestQueue.front(), 1);
}

TEST(TestQueue, EqOperator) {
  s21::queue<int> TestQueue1{1, 2, 3, 4, 5};
  s21::queue<int> TestQueue2;
  TestQueue2 = TestQueue1;
  ASSERT_EQ(TestQueue2.size(), 5);
  ASSERT_EQ(TestQueue2.front(), 1);
  ASSERT_EQ(TestQueue2.back(), 5);
  ASSERT_EQ(TestQueue2.front(), 1);
  TestQueue2.pop();
  ASSERT_EQ(TestQueue2.front(), 2);
}

TEST(TestQueue, Swap) {
  s21::queue<int> TestQueue1{1, 2, 3, 4, 5};
  s21::queue<int> TestQueue2{5, 6, 7};
  TestQueue1.swap(TestQueue2);
  ASSERT_EQ(TestQueue1.size(), 3);
  ASSERT_EQ(TestQueue1.front(), 5);
  TestQueue1.pop();
  ASSERT_EQ(TestQueue1.front(), 6);
  ASSERT_EQ(TestQueue2.size(), 5);
  ASSERT_EQ(TestQueue2.front(), 1);
  TestQueue2.pop();
  ASSERT_EQ(TestQueue2.front(), 2);
}

TEST(TestQueue, initTestBool0) {
  s21::queue<bool> TestQueue;
  ASSERT_EQ(TestQueue.size(), 0);
}

TEST(TestQueue, initTestBool1) {
  s21::queue<bool> TestQueue(5);
  ASSERT_EQ(TestQueue.size(), 0);
}

TEST(TestQueue, initTestBool2) {
  s21::queue<bool> TestQueue{true, false, false, true, false};
  ASSERT_EQ(TestQueue.size(), 5);

  ASSERT_EQ(TestQueue.front(), true);
  TestQueue.pop();
  ASSERT_EQ(TestQueue.front(), false);
  TestQueue.pop();
  ASSERT_EQ(TestQueue.front(), false);
  ASSERT_EQ(TestQueue.size(), 3);
}

TEST(TestQueue, initTestBoolCopy) {
  s21::queue<bool> TestQueue1{true, false, false, true, false};
  s21::queue TestQueue2(TestQueue1);
  ASSERT_EQ(TestQueue2.size(), 5);
  ASSERT_EQ(TestQueue2.front(), true);
  ASSERT_EQ(TestQueue2.back(), false);
  TestQueue2.pop();
  ASSERT_EQ(TestQueue2.front(), false);
  ASSERT_EQ(TestQueue2.back(), false);
  TestQueue2.pop();
  ASSERT_EQ(TestQueue2.front(), false);
  ASSERT_EQ(TestQueue2.back(), false);
  TestQueue2.pop();
  ASSERT_EQ(TestQueue2.front(), true);
  ASSERT_EQ(TestQueue2.back(), false);
  TestQueue2.pop();
  ASSERT_EQ(TestQueue2.front(), false);
  ASSERT_EQ(TestQueue2.back(), false);
  TestQueue2.pop();
  ASSERT_EQ(TestQueue2.empty(), true);
}

TEST(TestQueue, initTestBoolMove) {
  s21::queue<bool> TestQueue1(3);
  s21::queue TestQueue2(std::move(TestQueue1));
  ASSERT_EQ(TestQueue2.size(), 0);
  TestQueue2.push(true);
  ASSERT_EQ(TestQueue2.front(), true);
  ASSERT_EQ(TestQueue2.back(), true);
  TestQueue2.pop();
  ASSERT_EQ(TestQueue2.empty(), true);
}

TEST(TestQueue, PushFrontBool) {
  s21::queue<bool> TestQueue(5);
  TestQueue.push(false);
  TestQueue.push(true);
  ASSERT_EQ(TestQueue.size(), 2);

  ASSERT_EQ(TestQueue.front(), false);
  TestQueue.pop();
  ASSERT_EQ(TestQueue.front(), true);
}

TEST(TestQueue, PushBackBool) {
  s21::queue<bool> TestQueue(5);
  TestQueue.push(false);
  TestQueue.push(true);
  ASSERT_EQ(TestQueue.size(), 2);
  ASSERT_EQ(TestQueue.front(), false);
  TestQueue.pop();
  ASSERT_EQ(TestQueue.front(), true);
}

TEST(TestQueue, EmplaceBacktBool) {
  s21::queue<bool> TestQueue({true, false});
  ASSERT_EQ(TestQueue.size(), 2);
  ASSERT_EQ(TestQueue.front(), true);
  TestQueue.emplace_back(false);
  ASSERT_EQ(TestQueue.size(), 3);
  ASSERT_EQ(TestQueue.back(), false);
  TestQueue.emplace_back(true, true);
  ASSERT_EQ(TestQueue.back(), true);
  TestQueue.pop();
  ASSERT_EQ(TestQueue.back(), true);
}

TEST(TestQueue, ResizeBool) {
  s21::queue<bool> TestQueue(3);
  TestQueue.push(true);
  TestQueue.push(true);
  TestQueue.push(true);
  TestQueue.push(false);
  TestQueue.push(true);
  ASSERT_EQ(TestQueue.size(), 5);
  ASSERT_EQ(TestQueue.front(), true);
  TestQueue.pop();
  ASSERT_EQ(TestQueue.front(), true);
}

TEST(TestQueue, EqOperatorBool) {
  s21::queue<bool> TestQueue1{true, false, false, true, false};
  s21::queue<bool> TestQueue2;
  TestQueue2 = TestQueue1;
  ASSERT_EQ(TestQueue2.size(), 5);
  ASSERT_EQ(TestQueue2.front(), true);
  TestQueue2.pop();
  ASSERT_EQ(TestQueue2.front(), false);
}

TEST(TestQueue, SwapBool) {
  s21::queue<bool> TestQueue1{true, false, false, false, false};
  s21::queue<bool> TestQueue2{false, true, true};
  TestQueue1.swap(TestQueue2);
  ASSERT_EQ(TestQueue1.size(), 3);
  ASSERT_EQ(TestQueue1.front(), false);
  TestQueue1.pop();
  ASSERT_EQ(TestQueue1.front(), true);
  ASSERT_EQ(TestQueue2.size(), 5);
  ASSERT_EQ(TestQueue2.front(), true);
  TestQueue2.pop();
  ASSERT_EQ(TestQueue2.front(), false);
}
