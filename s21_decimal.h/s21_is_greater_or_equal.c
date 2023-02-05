#include "s21_decimal.h"

int s21_is_greater_or_equal(s21_decimal first, s21_decimal second) {
  int res;
  res = s21_is_less(first, second);
  return (res == 1) ? 0 : 1;
}