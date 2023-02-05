#include "s21_decimal.h"

int s21_add_super(s21_super_decimal value_1, s21_super_decimal value_2,
                  s21_super_decimal *result) {
  int err = 0;

  while (!is_super_zero(value_2)) {
    *result = s21_super_and_dec(value_1, value_2);
    value_1 = s21_super_xor_dec(value_1, value_2);
    s21_left_super_shift(result, 1);
    value_2 = *result;
  }

  *result = value_1;

  return err;
}

int s21_add_equal(s21_decimal value_1, s21_decimal value_2,
                  s21_decimal *result) {
  // Add scale;
  int err = 0;

  while (!is_zero(value_2)) {
    *result = s21_and_dec(value_1, value_2);
    value_1 = s21_xor_dec(value_1, value_2);
    s21_left_shift(result, 1);
    value_2 = *result;
  }
  *result = value_1;
  return err;
}

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int err = 0;
  int negative = 0;

  if (result) {
    s21_super_decimal svalue_1, svalue_2, sresult;

    s21_init_super_decimal(&svalue_1);
    s21_init_super_decimal(&svalue_2);

    s21_dec_to_super(value_1, &svalue_1);
    s21_dec_to_super(value_2, &svalue_2);

    int scale_1 = getscale(value_1);
    int scale_2 = getscale(value_2);

    s21_adjust_scale(&svalue_1, &svalue_2, &scale_1, &scale_2);

    if (is_super_zero(svalue_1) && !is_super_zero(svalue_2)) {
      *result = value_2;
    } else if (is_super_zero(svalue_2) && !is_super_zero(svalue_1)) {
      *result = value_1;
    } else if (is_super_zero(svalue_2) && is_super_zero(svalue_1)) {
      *result = value_1;
    } else {
      if (getsign(value_1) && !getsign(value_2)) {
        if (s21_is_super_less_or_equal(svalue_1, svalue_2)) {
          s21_sub_super_equal(svalue_2, svalue_1, &sresult);
        } else {
          s21_sub_super_equal(svalue_1, svalue_2, &sresult);
          negative = 1;
        }
      } else if (getsign(value_2) && !getsign(value_1)) {
        if (s21_is_super_less_or_equal(svalue_1, svalue_2)) {
          s21_sub_super_equal(svalue_2, svalue_1, &sresult);
          negative = 1;
        } else {
          s21_sub_super_equal(svalue_1, svalue_2, &sresult);
        }
      } else if (getsign(value_2) && getsign(value_1)) {
        s21_add_super(svalue_1, svalue_2, &sresult);
        negative = 1;
      } else {
        s21_add_super(svalue_1, svalue_2, &sresult);
      }
      from_super_to_decimal(sresult, result,
                            (scale_1 > scale_2) ? scale_1 : scale_2, negative);

      if (negative) setsign(result, 1);
    }
  } else {
    err = 3;
  }

  return err;
}
