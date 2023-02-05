#include "s21_decimal.h"

int get_bit(s21_decimal x, int i) {
  unsigned int filter = 1u << (i % 32);
  return (x.bits[i / 32] & filter) != 0;
}

void set_bit(s21_decimal *x, int i) {
  unsigned int filter = 1u << (i % 32);
  x->bits[i / 32] = (x->bits[i / 32] | filter);
}

void clear_bit(s21_decimal *x, int i) {
  unsigned int filter = 1u << (i % 32);
  x->bits[i / 32] = (x->bits[i / 32] & ~filter);
}

void setscale(s21_decimal *src, int scale) {
  src->bits[3] &= 0x80000000;
  src->bits[3] |= ((unsigned)scale) << 16;
}

int getscale(s21_decimal src) {
  src.bits[3] &= ~0x80000000;
  return src.bits[3] >> 16;
}

void setsign(s21_decimal *value, int sign) {
  if (sign == 1) {
    value->bits[3] |= 0x80000000;
  } else {
    value->bits[3] &= ~0x80000000;
  }
}

unsigned int getsign(s21_decimal src) {
  unsigned int tmp = (unsigned)src.bits[3] & 0x80000000;
  return tmp >> 31;
}

int get_bit_super(s21_super_decimal x, int i) {
  unsigned int filter = 1u << (i % 32);
  return (x.bits[i / 32] & filter) != 0;
}

int checkinf(s21_decimal value) {
  int ret = 0;
  if ((getscale(value) == 28) && (value.bits[0] == 0) && (value.bits[1] == 0) &&
      (value.bits[2] == 0))
    ret = 1;
  return ret;  // 0 - non inf, 1 - inf
}
