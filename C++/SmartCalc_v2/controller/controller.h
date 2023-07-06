#ifndef SRC_CONTROLLER_H_
#define SRC_CONTROLLER_H_

#include <iostream>

#include "../model/model.h"

using namespace std;

namespace s21 {
class Controller {
 public:
  Controller() { ; };
  ~Controller() { ; }
  bool InputNewExpression(const string expression) noexcept;
  double GetResult(const string expression, double x);

 private:
  Model model_;
};  // class Controller
}  // namespace s21

#endif  // SRC_CONTROLLER_H_