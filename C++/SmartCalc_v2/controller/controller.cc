#include "controller.h"

namespace s21 {

bool Controller::InputNewExpression(const string expression) noexcept {
  model_.InputNewExpression(expression);
  model_.validation();
  return model_.getStatus();
}

double Controller::GetResult(string expression, double x) {
  return model_.parser(expression, x);
}

};  // namespace s21