#include "s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int res = 0;
  if (dst) {
    s21_init_decimal(dst);
    if (src < 0) {
      setsign(dst, 1);
      if (src != INT_MIN) {
        src *= -1;
      }
    }
    dst->bits[0] = src;
  } else {
    res = 1;
  }
  return res;
}
