#include "s21_decimal.h"

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int err = 0;
  if (dst) {
    s21_init_decimal(dst);
    int scale = 0, point = 0, scale_tmp = 0, sign = 0, i = 0;
    char buffer[80];
    memset(buffer, '\0', 80);
    if ((fabs(src) < 1e-28 && fabs(src) > 1e-38) || isinf(src) || isnan(src) ||
        fabs(src) > 7922816e22) {
      err = 1;
    } else {
      sprintf(buffer, "%.7g", src);
      if (buffer[0] == '-') {
        setsign(dst, 1);
        i = 1;
      }
      while (buffer[i] && buffer[i] != 'e') {
        if (buffer[i] == '.') {
          point += 1;
        } else {
          if (point) scale++;
          err |= s21_mul_10_dec(dst);
          dst->bits[0] += buffer[i] - '0';
        }
        i++;
      }
      if (buffer[i] == 'e') {
        i++;
        sign = 0;
        if (buffer[i] == '-') {
          sign = 1;
          i++;
        } else if (buffer[i] == '+') {
          i++;
        }
        while (buffer[i] != '\0') {
          scale_tmp *= 10;
          scale_tmp += buffer[i] - '0';
          i++;
        }
        if (sign)
          scale += scale_tmp;
        else
          scale -= scale_tmp;
        while (scale < 0) {
          err |= s21_mul_10_dec(dst);
          scale++;
        }
      }

      setscale(dst, scale);
    }
    if (err) s21_init_decimal(dst);
  } else {
    err = 1;
  }
  return err;
}
