#include "s21_decimal.h"

int s21_round(s21_decimal value, s21_decimal *result) {
  s21_init_decimal(result);
  int err = s21_is_incorrect(value);

  if (result) {
    if (!err) {
      int scale = getscale(value);

      *result = value;
      if (scale != 0) {
        s21_decimal tmp;
        s21_init_decimal(&tmp);
        tmp.bits[0] = 5;
        setscale(&tmp, 1);

        int sign = getsign(value);
        setsign(&value, 0);

        s21_add(value, tmp, &value);
        setscale(&value, scale);

        tmp = value;
        s21_truncate(value, result);
        if (s21_is_equal(*result, tmp) && get_bit(*result, 0)) {
          s21_init_decimal(&tmp);
          tmp.bits[0] = 1;
          s21_sub_equal(*result, tmp, result);
        }

        setsign(result, sign);
      }
    }
  } else {
    err = 1;
  }
  return err;
}
