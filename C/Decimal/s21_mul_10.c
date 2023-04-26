#include "s21_decimal.h"

int s21_mul_10_super_dec(s21_super_decimal *dst) {
  s21_super_decimal cpy;
  s21_init_super_decimal(&cpy);
  int err = s21_left_super_shift(dst, 1);
  if (!err) {
    cpy = *dst;
    err |= s21_left_super_shift(&cpy, 2);
    if (!err) err |= s21_add_super(*dst, cpy, dst);
  }
  return err;
}

int s21_mul_10_dec(s21_decimal *dst) {
  s21_decimal cpy;
  int err = s21_left_shift(dst, 1);
  if (!err) {
    cpy = *dst;
    err |= s21_left_shift(&cpy, 2);
    if (!err) err |= s21_add_equal(*dst, cpy, dst);
  }
  return err;
}
