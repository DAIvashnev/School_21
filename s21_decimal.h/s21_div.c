#include "s21_decimal.h"

int s21_div_sup(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  // value_1 - dividend
  // value_2 - divisor
  int err = 0;

  s21_decimal quotient;
  s21_init_decimal(&quotient);

  int count = 0;
  int status = 1;
  int zeroes = 0;
  int in_zero = 0;

  while (count < 28 && status) {
    setscale(&value_2, 0);
    in_zero = 0;
    while (s21_is_less(value_1, value_2)) {
      err = s21_mul_10_dec(&value_1);
      if (count == 0)
        zeroes++;
      else if (in_zero)
        count++;
      else
        in_zero = 1;
    }

    s21_decimal temp;
    s21_init_decimal(&temp);

    while (s21_is_less_or_equal(value_2, value_1)) {
      err = s21_sub(value_1, value_2, &value_1);
      temp.bits[0] += 1;
    }

    setscale(&temp, count);
    count++;

    err = s21_add(quotient, temp, &quotient);

    if (is_zero(value_1)) {
      status = 0;
    }
  }

  zeroes--;
  int scale = zeroes + count;
  setscale(&quotient, zeroes + count);
  setscale(&quotient, scale);
  *result = quotient;

  return err;
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int err = 0;
  int negative = 0;

  if (result) {
    s21_decimal one;
    int fl = 0;
    s21_init_decimal(&one);
    s21_init_decimal(result);
    one.bits[0] = 1;

    s21_decimal tre = {{-1, -1, -1, 1 << 16}};

    if (getsign(value_1) && !getsign(value_2)) {
      negative = 1;
    } else if (!getsign(value_1) && getsign(value_2)) {
      negative = 1;
    } else if (getsign(value_1) && getsign(value_2)) {
      negative = 0;
    }

    if (getsign(value_1)) setsign(&value_1, 0);
    if (getsign(value_2)) setsign(&value_2, 0);

    if (is_zero(value_2)) {
      err = 3;
    } else if (is_zero(value_1)) {
      *result = value_1;
    } else if (s21_is_equal(value_1, value_2)) {
      *result = one;
    } else {
      if (getsign(value_1)) setsign(&value_1, 0);
      if (getsign(value_2)) setsign(&value_2, 0);
      if (s21_is_greater_or_equal(value_2, tre)) {
        s21_dev_10_dec(&value_2);
        fl = 1;
      }

      s21_decimal temp;

      s21_init_decimal(&temp);

      err = s21_div_sup(one, value_2, &temp);

      err = s21_mul(value_1, temp, result);

      int max_scale = getscale(*result) - getscale(value_2);

      if (max_scale < 0) {
        for (int i = -1 * max_scale; i > 0; i--) {
          err = s21_mul_10_dec(result);
        }
      } else {
        setscale(result, max_scale);
      }

      if (negative) s21_negate(*result, result);
    }
    if (fl) s21_dev_10_dec(result);
    if (err != 0) s21_init_decimal(result);
    if (checkinf(*result)) err = 2;
  } else {
    err = 4;
  }
  return err;
}
