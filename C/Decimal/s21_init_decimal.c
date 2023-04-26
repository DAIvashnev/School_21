#include "s21_decimal.h"

void s21_init_decimal(s21_decimal *dst) {
  dst->bits[0] = 0;
  dst->bits[1] = 0;
  dst->bits[2] = 0;
  dst->bits[3] = 0;
}

void s21_init_super_decimal(s21_super_decimal *dst) {
  for (int i = 0; i < 6; i++) {
    dst->bits[i] = 0;
  }
}
