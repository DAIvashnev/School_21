#include "s21_decimal.h"

int s21_negate(s21_decimal value_1, s21_decimal *result) {
  int err = s21_is_incorrect(value_1);
  if (result && !err) {
    if (get_bit(value_1, 127) == 1)
      clear_bit(&value_1, 127);
    else
      set_bit(&value_1, 127);
    *result = value_1;
  } else {
    err = 1;
  }
  return err;
}
