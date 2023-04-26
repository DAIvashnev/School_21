#include "s21_decimal.h"

void s21_dec_to_super(s21_decimal first, s21_super_decimal *super) {
  super->bits[0] = first.bits[0];
  super->bits[1] = first.bits[1];
  super->bits[2] = first.bits[2];
}

int from_super_to_decimal(s21_super_decimal sresult, s21_decimal *result,
                          int scale, int sign) {
  int err = 0, init_scale = scale;
  s21_super_decimal initial = sresult;
  s21_init_decimal(result);
  while (sresult.bits[3] != 0 || sresult.bits[4] != 0 || sresult.bits[5] != 0 ||
         scale > 28) {
    s21_div_10_super(&sresult);
    scale--;
  }

  if (scale < 0 && !sign) err = 1;
  if (scale < 0 && sign) err = 2;

  result->bits[0] = sresult.bits[0];
  result->bits[1] = sresult.bits[1];
  result->bits[2] = sresult.bits[2];
  setscale(result, scale);

  // result->bits[3] = scale;
  for (int i = 0; i < init_scale - scale; i++) s21_mul_10_super_dec(&sresult);
  // if (initial.bits[3] != 0 || initial.bits[4] != 0 || initial.bits[5] != 0)
  s21_bank_round_for_sub(sresult, initial, init_scale - scale, result);

  setsign(result, sign);
  if (!err && is_zero(*result) && !is_super_zero(initial)) err = 2;
  if (err || is_zero(*result)) s21_init_decimal(result);
  return err;
}
