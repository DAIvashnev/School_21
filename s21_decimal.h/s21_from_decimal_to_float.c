#include "s21_decimal.h"

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int err = 0;
  if (dst) {
    double dest_buffer;
    int counter;
    int sign;
    unsigned int scale;

    dest_buffer = 0;
    counter = 95;

    sign = getsign(src);
    scale = getscale(src);
    for (int i = 2; i > -1; i--) {
      for (int k = 31; k > -1; k--) {
        unsigned int mask = 1 << k;
        if ((src.bits[i] & mask) != 0)
          dest_buffer = dest_buffer + pow(2, counter);
        counter--;
      }
    }
    dest_buffer = dest_buffer / pow(10, scale);
    if (sign == 1) dest_buffer = (-1) * dest_buffer;
    *dst = (float)dest_buffer;
  } else {
    err = 1;
  }
  return err;
}
