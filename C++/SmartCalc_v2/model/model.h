#ifndef SRC_MODEL_H_
#define SRC_MODEL_H_

#include <cmath>
#include <cstring>
#include <iostream>
#include <map>
#include <stack>

using namespace std;

namespace s21 {
class Model {
 public:
  string tmp;
  int unarFlag = 0;

  Model() { ; }
  void InputNewExpression(const string expression) noexcept;
  ~Model() { ; }
  void validation() noexcept;
  double parser(string expression_, double x);
  bool getStatus() const noexcept;

 private:
  string expression_;
  double x_;
  int lenExp_;
  bool status_;

  bool vLen() const noexcept;
  bool vData() noexcept;
  bool vBrackets() noexcept;
  bool vOperation() noexcept;
  bool vNumber() noexcept;
  bool vMod() noexcept;
  bool vFunc() noexcept;
  bool IsDigit(char ch) const noexcept;

  struct Stack {
    stack<double> Stack_n;
    stack<char> Stack_o;
  };

  map<char, int> const operation = {{'^', 3},  {'/', 2},  {'*', 2}, {'m', 1},
                                    {'(', -1}, {')', -1}, {'+', 0}, {'-', 0}};
  map<std::string, char> const func = {
      {"cos", 'c'},  {"sin", 's'},  {"tan", 't'}, {"acos", 'C'}, {"asin", 'S'},
      {"atan", 'T'}, {"sqrt", 'q'}, {"ln", 'l'},  {"log", 'L'}};

  int getRang(char c) noexcept;
  char getFunc() noexcept;
  void calculate(stack<double> &Stack_n, stack<char> &Stack_o);
  void calculateFunc(stack<double> &Stack_n, stack<char> &Stack_o);

};  // class Model
}  // namespace s21

#endif  // SRC_MODEL_H_