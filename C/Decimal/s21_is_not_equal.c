#include "s21_decimal.h"

int s21_is_not_equal(s21_decimal first, s21_decimal second) {
  int res = 0;
  if (s21_is_less(first, second) || s21_is_less(second, first)) res = 1;
  return res;
}