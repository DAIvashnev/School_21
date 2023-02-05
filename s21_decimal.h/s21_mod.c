#include "s21_decimal.h"

int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int ret = 0;

  if (result) {
    s21_decimal tmp, zero;

    s21_init_decimal(&tmp);
    s21_init_decimal(&zero);

    s21_div(value_1, value_2, &tmp);

    if (checkinf(tmp)) {
      *result = zero;
    } else {
      s21_truncate(tmp, &tmp);

      s21_mul(tmp, value_2, &tmp);

      s21_sub(value_1, tmp, result);
    }
    if (checkinf(value_2)) {
      ret = 0;
      *result = value_1;
    }
  } else {
    ret = 3;
  }

  return ret;
}