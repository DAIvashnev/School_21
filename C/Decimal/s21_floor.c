#include "s21_decimal.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
  int err = s21_is_incorrect(value);
  if (result) {
    s21_init_decimal(result);
    if (!err) {
      int scale = getscale(value);
      *result = value;
      if (scale != 0) {
        s21_truncate(value, result);
        setscale(result, 0);
        if (s21_is_less(value, *result)) {
          s21_decimal one;
          s21_init_decimal(&one);
          one.bits[0] = 1;
          err |= s21_add_equal(*result, one, result);
        }
        setscale(result, 0);
      }
    }
  } else {
    err = 1;
  }
  return err;
}
