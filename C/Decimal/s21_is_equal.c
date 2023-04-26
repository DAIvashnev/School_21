#include "s21_decimal.h"

int s21_is_equal(s21_decimal first, s21_decimal second) {
  int result = 0;
  if (is_zero(first) && is_zero(second))
    result = 1;
  else if (!s21_is_less(first, second) && !s21_is_greater(first, second))
    result = 1;
  return result;
}

int s21_is_super_equal(s21_super_decimal first, s21_super_decimal second) {
  int result = 1;
  for (int i = 0; (i < 6) && (result != 0); i++) {
    if (first.bits[i] != second.bits[i]) result = 0;
  }
  return result;
}
