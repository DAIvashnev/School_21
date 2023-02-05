#include "s21_decimal.h"

int s21_left_super_shift(s21_super_decimal *dst, int times) {
  int result = 0;
  while (times > 0) {
    times--;
    if ((unsigned)dst->bits[5] > (UINT_MAX >> 1)) result = 1;
    dst->bits[5] = dst->bits[5] << 1;
    if ((unsigned)dst->bits[4] > (UINT_MAX >> 1)) dst->bits[5] |= 1;
    dst->bits[4] = dst->bits[4] << 1;
    if ((unsigned)dst->bits[3] > (UINT_MAX >> 1)) dst->bits[4] |= 1;
    dst->bits[3] = dst->bits[3] << 1;
    if ((unsigned)dst->bits[2] > (UINT_MAX >> 1)) dst->bits[3] |= 1;
    dst->bits[2] = dst->bits[2] << 1;
    if ((unsigned)dst->bits[1] > (UINT_MAX >> 1)) dst->bits[2] |= 1;
    dst->bits[1] = dst->bits[1] << 1;
    if ((unsigned)dst->bits[0] > (UINT_MAX >> 1)) dst->bits[1] |= 1;
    dst->bits[0] = dst->bits[0] << 1;
  }
  return result;
}

int s21_left_shift(s21_decimal *dst, int times) {
  int result = 0;
  while (times > 0) {
    times--;
    if ((unsigned)dst->bits[2] > (UINT_MAX >> 1)) result = 1;
    dst->bits[2] = dst->bits[2] << 1;
    if ((unsigned)dst->bits[1] > (UINT_MAX >> 1)) dst->bits[2] |= 1;
    dst->bits[1] = dst->bits[1] << 1;
    if ((unsigned)dst->bits[0] > (UINT_MAX >> 1)) dst->bits[1] |= 1;
    dst->bits[0] = dst->bits[0] << 1;
  }
  return result;
}

void s21_right_super_shift(s21_super_decimal *dst, int times) {
  while (times > 0) {
    times--;
    dst->bits[0] = (unsigned)dst->bits[0] >> 1;
    if (dst->bits[1] & 1) dst->bits[0] |= (1 << 31);
    dst->bits[1] = (unsigned)dst->bits[1] >> 1;
    if (dst->bits[2] & 1) dst->bits[1] |= (1 << 31);
    dst->bits[2] = (unsigned)dst->bits[2] >> 1;
    if (dst->bits[3] & 1) dst->bits[2] |= (1 << 31);
    dst->bits[3] = (unsigned)dst->bits[3] >> 1;
    if (dst->bits[4] & 1) dst->bits[3] |= (1 << 31);
    dst->bits[4] = (unsigned)dst->bits[4] >> 1;
    if (dst->bits[5] & 1) dst->bits[4] |= (1 << 31);
    dst->bits[5] = (unsigned)dst->bits[5] >> 1;
  }
}

void s21_right_shift(s21_decimal *dst, int times) {
  while (times > 0) {
    times--;
    dst->bits[0] = (unsigned)dst->bits[0] >> 1;
    if (dst->bits[1] & 1) dst->bits[0] |= (1 << 31);
    dst->bits[1] = (unsigned)dst->bits[1] >> 1;
    if (dst->bits[2] & 1) dst->bits[1] |= (1 << 31);
    dst->bits[2] = (unsigned)dst->bits[2] >> 1;
  }
}
s21_decimal s21_or_dec(s21_decimal dst, s21_decimal add) {
  // NO scale!
  s21_decimal result;
  s21_init_decimal(&result);
  result.bits[0] = dst.bits[0] | add.bits[0];
  result.bits[1] = dst.bits[1] | add.bits[1];
  result.bits[2] = dst.bits[2] | add.bits[2];
  result.bits[3] = dst.bits[3];
  return result;
}

s21_decimal s21_and_dec_inverted(s21_decimal dst, s21_decimal add) {
  // NO scale!
  s21_decimal result;
  s21_init_decimal(&result);
  result.bits[0] = (~dst.bits[0]) & add.bits[0];
  result.bits[1] = (~dst.bits[1]) & add.bits[1];
  result.bits[2] = (~dst.bits[2]) & add.bits[2];

  return result;
}

s21_super_decimal s21_super_and_dec_inverted(s21_super_decimal dst,
                                             s21_super_decimal add) {
  // NO scale!
  s21_super_decimal result;
  s21_init_super_decimal(&result);
  result.bits[0] = (~dst.bits[0]) & add.bits[0];
  result.bits[1] = (~dst.bits[1]) & add.bits[1];
  result.bits[2] = (~dst.bits[2]) & add.bits[2];
  result.bits[3] = (~dst.bits[3]) & add.bits[3];
  result.bits[4] = (~dst.bits[4]) & add.bits[4];
  result.bits[5] = (~dst.bits[5]) & add.bits[5];
  return result;
}

s21_decimal s21_and_dec(s21_decimal dst, s21_decimal add) {
  // NO scale!
  s21_decimal result;
  s21_init_decimal(&result);
  result.bits[0] = dst.bits[0] & add.bits[0];
  result.bits[1] = dst.bits[1] & add.bits[1];
  result.bits[2] = dst.bits[2] & add.bits[2];

  return result;
}

s21_super_decimal s21_super_and_dec(s21_super_decimal dst,
                                    s21_super_decimal add) {
  // NO scale!
  s21_super_decimal result;
  s21_init_super_decimal(&result);
  result.bits[0] = dst.bits[0] & add.bits[0];
  result.bits[1] = dst.bits[1] & add.bits[1];
  result.bits[2] = dst.bits[2] & add.bits[2];
  result.bits[3] = dst.bits[3] & add.bits[3];
  result.bits[4] = dst.bits[4] & add.bits[4];
  result.bits[5] = dst.bits[5] & add.bits[5];

  return result;
}

s21_decimal s21_xor_dec(s21_decimal dst, s21_decimal add) {
  // NO scale!
  s21_decimal result;
  s21_init_decimal(&result);
  result.bits[0] = dst.bits[0] ^ add.bits[0];
  result.bits[1] = dst.bits[1] ^ add.bits[1];
  result.bits[2] = dst.bits[2] ^ add.bits[2];
  result.bits[3] = dst.bits[3];
  return result;
}

s21_super_decimal s21_super_xor_dec(s21_super_decimal dst,
                                    s21_super_decimal add) {
  // NO scale!
  s21_super_decimal result;
  s21_init_super_decimal(&result);
  result.bits[0] = dst.bits[0] ^ add.bits[0];
  result.bits[1] = dst.bits[1] ^ add.bits[1];
  result.bits[2] = dst.bits[2] ^ add.bits[2];
  result.bits[3] = dst.bits[3] ^ add.bits[3];
  result.bits[4] = dst.bits[4] ^ add.bits[4];
  result.bits[5] = dst.bits[5] ^ add.bits[5];
  return result;
}
