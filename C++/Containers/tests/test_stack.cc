#include <gtest/gtest.h>

#include "include/stack_suit.h"

TEST(TestStack, initTest0) {
  s21::stack<int> TestStack;
  ASSERT_EQ(TestStack.size(), 0);
}

TEST(TestStack, initTest1) {
  s21::stack<int> TestStack(5);
  ASSERT_EQ(TestStack.size(), 0);
}

TEST(TestStack, initTest2) {
  s21::stack<int> TestStack{1, 2, 3, 4, 5};
  ASSERT_EQ(TestStack.size(), 5);
  ASSERT_EQ(TestStack.top(), 5);
  TestStack.pop();
  ASSERT_EQ(TestStack.top(), 4);
  TestStack.pop();
  ASSERT_EQ(TestStack.top(), 3);
  TestStack.pop();
  ASSERT_EQ(TestStack.top(), 2);
  TestStack.pop();
  ASSERT_EQ(TestStack.top(), 1);
}

TEST(TestStack, initTestCopy) {
  s21::stack<int> TestStack1{1, 2, 3, 4, 5};
  s21::stack TestStack2(TestStack1);
  ASSERT_EQ(TestStack2.size(), 5);
  ASSERT_EQ(TestStack2.top(), 5);
  TestStack2.pop();
  ASSERT_EQ(TestStack2.top(), 4);
  TestStack2.pop();
  ASSERT_EQ(TestStack2.top(), 3);
  TestStack2.pop();
  ASSERT_EQ(TestStack2.top(), 2);
  TestStack2.pop();
  ASSERT_EQ(TestStack2.top(), 1);
}

TEST(TestStack, initTestMove) {
  s21::stack<int> TestStack1(3);
  s21::stack TestStack2(std::move(TestStack1));
  ASSERT_EQ(TestStack2.size(), 0);
  TestStack2.push(3);
  ASSERT_EQ(TestStack2.top(), 3);
}

TEST(TestStack, Push) {
  s21::stack<int> TestStack(5);
  TestStack.push(0);
  TestStack.push(-1);
  ASSERT_EQ(TestStack.size(), 2);
  ASSERT_EQ(TestStack.top(), -1);
  TestStack.pop();
  ASSERT_EQ(TestStack.top(), 0);
}

TEST(TestStack, EmplaceFront) {
  s21::stack<int> TestStack({1});
  ASSERT_EQ(TestStack.size(), 1);
  ASSERT_EQ(TestStack.top(), 1);
  TestStack.emplace_front(4);
  ASSERT_EQ(TestStack.size(), 2);
  ASSERT_EQ(TestStack.top(), 4);
  TestStack.emplace_front(1, 2);
  ASSERT_EQ(TestStack.top(), 2);
  TestStack.pop();
  ASSERT_EQ(TestStack.top(), 1);
}

TEST(TestStack, Resize) {
  s21::stack<int> TestStack(3);
  TestStack.push(0);
  TestStack.push(1);
  TestStack.push(2);
  TestStack.push(3);
  TestStack.push(4);
  ASSERT_EQ(TestStack.size(), 5);
  ASSERT_EQ(TestStack.top(), 4);
  TestStack.pop();
  ASSERT_EQ(TestStack.top(), 3);
}

TEST(TestStack, EqOperator) {
  s21::stack<int> TestStack1{1, 2, 3, 4, 5};
  s21::stack<int> TestStack2;
  TestStack2 = TestStack1;
  ASSERT_EQ(TestStack2.size(), 5);
  ASSERT_EQ(TestStack2.top(), 5);
  ASSERT_EQ(TestStack2.top(), 5);
  TestStack2.pop();
  ASSERT_EQ(TestStack2.top(), 4);
}

TEST(TestStack, Swap) {
  s21::stack<int> TestStack1{1, 2, 3, 4, 5};
  s21::stack<int> TestStack2{5, 6, 7};
  TestStack1.swap(TestStack2);
  ASSERT_EQ(TestStack1.size(), 3);
  ASSERT_EQ(TestStack1.top(), 7);
  ASSERT_EQ(TestStack1.top(), 7);
  TestStack1.pop();
  ASSERT_EQ(TestStack1.top(), 6);
  ASSERT_EQ(TestStack2.size(), 5);
  ASSERT_EQ(TestStack2.top(), 5);
  ASSERT_EQ(TestStack2.top(), 5);
  TestStack2.pop();
  ASSERT_EQ(TestStack2.top(), 4);
}

TEST(TestStack, initTestBool0) {
  s21::stack<bool> TestStack;
  ASSERT_EQ(TestStack.size(), 0);
}

TEST(TestStack, initTestBool1) {
  s21::stack<bool> TestStack(5);
  ASSERT_EQ(TestStack.size(), 0);
}

TEST(TestStack, initTestBool2) {
  s21::stack<bool> TestStack{true, false, false, true, false};
  ASSERT_EQ(TestStack.size(), 5);

  ASSERT_EQ(TestStack.top(), false);
  TestStack.pop();
  ASSERT_EQ(TestStack.top(), true);
  ASSERT_EQ(TestStack.size(), 4);
}

TEST(TestStack, initTestBoolCopy) {
  s21::stack<bool> TestStack1{true, false, false, true, false};
  s21::stack TestStack2(TestStack1);
  ASSERT_EQ(TestStack2.size(), 5);
  ASSERT_EQ(TestStack2.top(), false);
  TestStack2.pop();
  ASSERT_EQ(TestStack2.top(), true);
  TestStack2.pop();
  ASSERT_EQ(TestStack2.top(), false);
  TestStack2.pop();
  ASSERT_EQ(TestStack2.top(), false);
  TestStack2.pop();
  ASSERT_EQ(TestStack2.top(), true);
  TestStack2.pop();
  ASSERT_EQ(TestStack2.empty(), true);
}

TEST(TestStack, initTestBoolMove) {
  s21::stack<bool> TestStack1(3);
  s21::stack TestStack2(std::move(TestStack1));
  ASSERT_EQ(TestStack2.size(), 0);
  TestStack2.push(true);
  ASSERT_EQ(TestStack2.top(), true);
  TestStack2.pop();
  ASSERT_EQ(TestStack2.empty(), true);
}

TEST(TestStack, PushFrontBool) {
  s21::stack<bool> TestStack(5);
  TestStack.push(false);
  TestStack.push(true);
  ASSERT_EQ(TestStack.size(), 2);

  ASSERT_EQ(TestStack.top(), true);
  TestStack.pop();
  ASSERT_EQ(TestStack.top(), false);
}

TEST(TestStack, PushBackBool) {
  s21::stack<bool> TestStack(5);
  TestStack.push(false);
  TestStack.push(true);
  ASSERT_EQ(TestStack.size(), 2);
  ASSERT_EQ(TestStack.top(), true);
  TestStack.pop();
  ASSERT_EQ(TestStack.top(), false);
}

TEST(TestStack, EmplaceFrontBool) {
  s21::stack<bool> TestStack({true, false});
  ASSERT_EQ(TestStack.size(), 2);
  ASSERT_EQ(TestStack.top(), false);
  TestStack.emplace_front(true);
  ASSERT_EQ(TestStack.size(), 3);
  ASSERT_EQ(TestStack.top(), true);
  TestStack.emplace_front(false, false);
  ASSERT_EQ(TestStack.top(), false);
  TestStack.pop();
  ASSERT_EQ(TestStack.top(), false);
}

TEST(TestStack, ResizeBool) {
  s21::stack<bool> TestStack(3);
  TestStack.push(true);
  TestStack.push(true);
  TestStack.push(true);
  TestStack.push(false);
  TestStack.push(true);
  ASSERT_EQ(TestStack.size(), 5);
  ASSERT_EQ(TestStack.top(), true);
  TestStack.pop();
  ASSERT_EQ(TestStack.top(), false);
}

TEST(TestStack, EqOperatorBool) {
  s21::stack<bool> TestStack1{true, false, false, true, false};
  s21::stack<bool> TestStack2;
  TestStack2 = TestStack1;
  ASSERT_EQ(TestStack2.size(), 5);
  ASSERT_EQ(TestStack2.top(), false);
  TestStack2.pop();
  ASSERT_EQ(TestStack2.top(), true);
}

TEST(TestStack, SwapBool) {
  s21::stack<bool> TestStack1{true, false, false, false, false};
  s21::stack<bool> TestStack2{false, true, true};
  TestStack1.swap(TestStack2);
  ASSERT_EQ(TestStack1.size(), 3);
  ASSERT_EQ(TestStack1.top(), true);
  TestStack1.pop();
  ASSERT_EQ(TestStack1.top(), true);
  ASSERT_EQ(TestStack2.size(), 5);
  ASSERT_EQ(TestStack2.top(), false);
  TestStack2.pop();
  ASSERT_EQ(TestStack2.top(), false);
}
