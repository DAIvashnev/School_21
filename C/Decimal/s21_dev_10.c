#include "s21_decimal.h"

int s21_div_10_super(s21_super_decimal *dst) {
  s21_super_decimal value_1, value_2, res, tmp;
  value_1 = *dst;
  value_2 = *dst;

  s21_right_super_shift(&value_1, 1);
  s21_right_super_shift(&value_2, 2);
  int err = s21_add_super(value_1, value_2, &res);

  value_1 = res;
  s21_right_super_shift(&value_1, 4);
  err = s21_add_super(res, value_1, &res);

  value_1 = res;
  s21_right_super_shift(&value_1, 8);
  err = s21_add_super(res, value_1, &res);

  value_1 = res;
  s21_right_super_shift(&value_1, 16);
  err = s21_add_super(res, value_1, &res);

  value_1 = res;
  s21_right_super_shift(&value_1, 32);
  err = s21_add_super(res, value_1, &res);

  value_1 = res;
  s21_right_super_shift(&value_1, 64);
  err = s21_add_super(res, value_1, &res);

  value_1 = res;
  s21_right_super_shift(&value_1, 128);
  err = s21_add_super(res, value_1, &res);

  s21_right_super_shift(&res, 3);

  //*dst = res;

  tmp = res;
  value_2 = res;

  s21_left_super_shift(&value_2, 2);
  s21_add_super(value_2, tmp, &tmp);
  s21_left_super_shift(&tmp, 1);
  s21_sub_super_equal(*dst, tmp, &value_2);

  s21_init_super_decimal(&tmp);
  if (value_2.bits[0] > 9) tmp.bits[0] = 1;
  s21_add_super(res, tmp, dst);

  return err;
}

void s21_dev_10_dec(s21_decimal *n) {
  int sign = getsign(*n);
  int scale = getscale(*n);
  setsign(n, 0);
  setscale(n, 0);
  s21_decimal q = *n, r = *n, res = *n;

  // q = (n >> 1) + (n >> 2);
  s21_right_shift(&q, 1);
  s21_right_shift(&r, 2);
  s21_add_equal(q, r, &q);

  // q = q + (q >> 4);
  r = q;
  s21_right_shift(&r, 4);
  s21_add_equal(q, r, &q);

  // q = q + (q >> 8);
  r = q;
  s21_right_shift(&r, 8);
  s21_add_equal(q, r, &q);

  // q = q + (q >> 16);
  r = q;
  s21_right_shift(&r, 16);
  s21_add_equal(q, r, &q);

  // q = q + (q >> 32);
  r = q;
  s21_right_shift(&r, 32);
  s21_add_equal(q, r, &q);

  // q = q + (q >> 64);
  r = q;
  s21_right_shift(&r, 64);
  s21_add_equal(q, r, &q);

  // q = q >> 3;
  s21_right_shift(&q, 3);
  res = q;

  // r = n - (((q << 2) + q) << 1);

  s21_decimal nine;
  s21_init_decimal(&nine);
  nine.bits[0] = 9;

  r = q;
  s21_mul_10_dec(&q);

  s21_init_decimal(&r);
  s21_sub_equal(*n, q, &r);
  s21_init_decimal(&q);

  if (s21_is_greater(r, nine)) q.bits[0] = 1;
  s21_add_equal(res, q, n);
  setsign(n, sign);
  setscale(n, scale);
}
