#include "s21_decimal.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
  int err = s21_is_incorrect(value);
  if (result) {
    s21_init_decimal(result);
    if (!err) {
      int scale = getscale(value);
      // int sign = getsign(value);
      *result = value;
      if (scale != 0) {
        for (int i = 0; i < scale; i++) {
          s21_dev_10_dec(result);
        }
        setscale(result, 0);
      }
    }
  } else {
    err = 1;
  }
  return err;
}
