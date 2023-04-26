#include "s21_decimal.h"

int s21_from_decimal_to_int(s21_decimal source, int *dst) {
  int res = 1;

  if (dst) {
    s21_decimal i_max = {{INT_MAX, 0, 0, 0}}, i_min = i_max,
                one = {{1, 0, 0, 0}};
    s21_add(i_max, one, &i_min);
    setsign(&i_min, 1);
    s21_truncate(source, &source);
    if ((!checkinf(source)) && (s21_is_greater_or_equal(source, i_min)) &&
        (s21_is_less_or_equal(source, i_max))) {
      *dst = source.bits[0];

      *dst *= getsign(source) ? -1 : 1;
      res = 0;
    }
  }
  return res;
}
