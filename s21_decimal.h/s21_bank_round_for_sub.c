#include "s21_decimal.h"

int s21_bank_round_for_sub(s21_super_decimal svalue_1,
                           s21_super_decimal sresult, int scale_diff,
                           s21_decimal *result) {
  /* Here svalue_1 - the result, before truncation, sresult - after truncation
   * and multiplication by 10
   */
  int err = 0;

  s21_super_decimal fraction;
  s21_super_decimal threshold;

  s21_init_super_decimal(&fraction);
  s21_init_super_decimal(&threshold);

  threshold.bits[0] = 5;
  if (s21_is_super_less(svalue_1, sresult))
    err = s21_sub_super_equal(sresult, svalue_1, &fraction);
  else
    err = s21_sub_super_equal(svalue_1, sresult, &fraction);
  if (!err) {
    while (scale_diff > 1) {
      s21_mul_10_super_dec(&threshold);
      scale_diff--;
    }
    if (s21_is_super_less(threshold, fraction) ||
        (s21_is_super_equal(threshold, fraction) && get_bit(*result, 0))) {
      s21_decimal one;
      s21_init_decimal(&one);
      one.bits[0] = 1;
      err = s21_add_equal(*result, one, result);
    }
  }
  return err;
}
