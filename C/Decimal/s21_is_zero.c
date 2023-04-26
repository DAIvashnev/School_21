#include "s21_decimal.h"

int is_zero(s21_decimal value) {
  int result = 1;
  if (value.bits[0] != 0) result = 0;
  if (value.bits[1] != 0) result = 0;
  if (value.bits[2] != 0) result = 0;
  return result;
}

int is_super_zero(s21_super_decimal value) {
  int result = 1;
  if (value.bits[0] != 0) result = 0;
  if (value.bits[1] != 0) result = 0;
  if (value.bits[2] != 0) result = 0;
  if (value.bits[3] != 0) result = 0;
  if (value.bits[4] != 0) result = 0;
  if (value.bits[5] != 0) result = 0;
  return result;
}
