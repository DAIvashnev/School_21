#include "s21_decimal.h"

int s21_is_incorrect(s21_decimal check) {
  int mask = 0x7F00FFFF;
  int res = 0;
  int scale = getscale(check);
  if (mask & check.bits[3]) res = 1;
  if (scale > 28) res = 1;
  return res;
}
