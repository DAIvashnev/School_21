#include "s21_decimal.h"

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int err;
  if (result) {
    int scale1 = getscale(value_1);
    int scale2 = getscale(value_2);
    int sign1 = getsign(value_1);
    int sign2 = getsign(value_2);

    s21_super_decimal first, second, sresult;
    s21_init_super_decimal(&first);
    s21_init_super_decimal(&second);
    s21_init_super_decimal(&sresult);
    s21_dec_to_super(value_1, &first);
    s21_dec_to_super(value_2, &second);

    err = s21_mul_super(first, second, &sresult);
    if (!err)
      err = from_super_to_decimal(sresult, result, scale1 + scale2,
                                  (sign1 + sign2) % 2);
    if (err || is_zero(*result)) s21_init_decimal(result);
  } else {
    err = 3;
  }
  return err;
}

int s21_mul_super(s21_super_decimal value_1, s21_super_decimal value_2,
                  s21_super_decimal *result) {
  s21_super_decimal new, cur;
  int err = 0;
  s21_init_super_decimal(result);
  for (int i = 0; i < 192; i++) {
    s21_init_super_decimal(&cur);
    s21_init_super_decimal(&new);
    new.bits[0] |= UINT_MAX *get_bit_super(value_2, i);
    new.bits[1] |= UINT_MAX *get_bit_super(value_2, i);
    new.bits[2] |= UINT_MAX *get_bit_super(value_2, i);
    new.bits[3] |= UINT_MAX *get_bit_super(value_2, i);
    new.bits[4] |= UINT_MAX *get_bit_super(value_2, i);
    new.bits[5] |= UINT_MAX *get_bit_super(value_2, i);
    new = s21_super_and_dec(value_1, new);
    err |= s21_left_super_shift(&new, i);
    cur = *result;
    err |= s21_add_super(cur, new, result);
  }
  return err;
}
