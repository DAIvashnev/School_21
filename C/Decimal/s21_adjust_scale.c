#include "s21_decimal.h"

void s21_adjust_scale(s21_super_decimal *first, s21_super_decimal *second,
                      int *scale_1, int *scale_2) {
  /*
  int mask = INT_MAX >> 1;

  *scale_1 = *scale_1 & mask >> 15;
  *scale_2 = *scale_2 & mask >> 15;
  10 / 10^6 = 0.00001 = 10^-5
  10 / 10^5 = 0.001 = 10^-3

  */

  if (*scale_1 != *scale_2) {
    if (*scale_1 < *scale_2) {
      int diff = *scale_2 - *scale_1;
      while (diff > 0) {
        s21_mul_10_super_dec(first);
        diff--;
        *scale_1 += 1;
      }
    } else if (*scale_2 < *scale_1) {
      int diff = *scale_1 - *scale_2;
      while (diff > 0) {
        s21_mul_10_super_dec(second);
        diff--;
        *scale_2 += 1;
      }
    }
  }
  // first->bits[3] << 15;
  // second->bits[3] << 15;
}
