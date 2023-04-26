#include "s21_decimal.h"

int s21_is_less(s21_decimal first, s21_decimal second) {
  int result = 0;
  int sign1 = getsign(first), sign2 = getsign(second);
  if (is_zero(first) && is_zero(second)) {
    result = 0;
  } else if (sign1 == 0 && sign2 == 1) {
    result = 0;
    ;
  } else if (sign1 == 1 && sign2 == 0) {
    result = 1;
  } else {
    s21_super_decimal sfirst, ssecond;
    s21_init_super_decimal(&sfirst);
    s21_init_super_decimal(&ssecond);
    s21_dec_to_super(first, &sfirst);
    s21_dec_to_super(second, &ssecond);
    int scale1 = getscale(first), scale2 = getscale(second);
    s21_adjust_scale(&sfirst, &ssecond, &scale1, &scale2);
    result = s21_is_super_less(sfirst, ssecond);
    if (sign1 == 1 && sign2 == 1) {
      if (!s21_is_super_equal(sfirst, ssecond)) {
        result = (result + 1) % 2;
      }
    }
  }
  return result;
}

int s21_is_super_less(s21_super_decimal first, s21_super_decimal second) {
  int result = -1;
  for (int i = 5; i >= 0 && result == -1; i--) {
    if ((unsigned)first.bits[i] != (unsigned)second.bits[i]) {
      if ((unsigned)first.bits[i] < (unsigned)second.bits[i])
        result = 1;
      else
        result = 0;
    }
  }
  if (result == -1) result = 0;
  return result;
}
