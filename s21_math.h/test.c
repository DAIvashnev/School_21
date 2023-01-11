#include "s21_math.h"

#include <check.h>
#include <math.h>

START_TEST(abs1) {
  ck_assert_int_eq(abs(0), s21_abs(0));
  ck_assert_int_eq(abs(-0), s21_abs(-0));
  ck_assert_int_eq(abs(-1), s21_abs(-1));
  ck_assert_int_eq(abs(2147483647), s21_abs(2147483647));
  ck_assert_int_eq(abs(-2147483647), s21_abs(-2147483647));
}
END_TEST

START_TEST(fabs1) {
  ck_assert_float_eq_tol(fabs(0.), s21_fabs(0.), 1E-6);
  ck_assert_float_eq_tol(fabs(-0.), s21_fabs(-0.), 1E-6);
  ck_assert_float_eq_tol(fabs(-1.000001), s21_fabs(-1.000001), 1E-6);
  ck_assert_float_eq_tol(fabs(-1.999999999), s21_fabs(-1.999999999), 1E-6);
  ck_assert_float_eq_tol(fabs(2147483647.), s21_fabs(2147483647.), 1E-6);
  ck_assert_float_eq_tol(fabs(-2147483647.), s21_fabs(-2147483647.), 1E-6);
  ck_assert_float_eq_tol(fabs(-11111111111111111.0000000000001),
                         s21_fabs(-11111111111111111.0000000000001), 1E-6);
  ck_assert_float_eq_tol(fabs(11111111111111111.0000000000001),
                         s21_fabs(11111111111111111.0000000000001), 1E-6);
  ck_assert_float_eq_tol(fabs(-99999999999999999.99999999999999999),
                         s21_fabs(-99999999999999999.99999999999999999), 1E-6);
  ck_assert_float_eq_tol(fabs(99999999999999999.99999999999999999),
                         s21_fabs(99999999999999999.99999999999999999), 1E-6);
  ck_assert_float_eq(fabs(S21_INFINITY), s21_fabs(S21_INFINITY));
  ck_assert_float_eq(fabs(-S21_INFINITY), s21_fabs(-S21_INFINITY));
  ck_assert_double_nan(s21_fabs(S21_NAN));
}
END_TEST

START_TEST(floor1) {
  ck_assert_float_eq_tol(floor(0.), s21_floor(0.), 1E-6);
  ck_assert_float_eq_tol(floor(-0.), s21_floor(-0.), 1E-6);
  ck_assert_float_eq_tol(floor(1.000001), s21_floor(1.000001), 1E-6);
  ck_assert_float_eq_tol(floor(-1.000001), s21_floor(-1.000001), 1E-6);
  ck_assert_float_eq_tol(floor(1.999999), s21_floor(1.999999), 1E-6);
  ck_assert_float_eq_tol(floor(-1.999999), s21_floor(-1.999999), 1E-6);
  ck_assert_float_eq_tol(floor(2147483647.), s21_floor(2147483647.), 1E-6);
  ck_assert_float_eq_tol(floor(-2147483647.), s21_floor(-2147483647.), 1E-6);
  ck_assert_float_eq_tol(floor(-2147483647.123456789),
                         s21_floor(-2147483647.123456789), 1E-6);
  ck_assert_float_eq_tol(floor(-11111111111111111.0000000000001),
                         s21_floor(-11111111111111111.0000000000001), 1E-6);
  ck_assert_float_eq_tol(floor(-11111111111111111.9999999999999),
                         s21_floor(-11111111111111111.9999999999999), 1E-6);
  ck_assert_float_eq_tol(floor(11111111111111111.9999999999999),
                         s21_floor(11111111111111111.9999999999999), 1E-6);
  ck_assert_float_eq_tol(floor(11111111111111111.0000000000001),
                         s21_floor(11111111111111111.0000000000001), 1E-6);
  ck_assert_float_eq_tol(floor(-99999999999999999.9999999999999999),
                         s21_floor(-99999999999999999.9999999999999999), 1E-6);
  ck_assert_float_eq_tol(floor(99999999999999999.9999999999999999),
                         s21_floor(99999999999999999.9999999999999999), 1E-6);
  ck_assert_float_eq(floor(S21_INFINITY), s21_floor(S21_INFINITY));
  ck_assert_float_eq(floor(-S21_INFINITY), s21_floor(-S21_INFINITY));
  ck_assert_double_nan(s21_floor(S21_NAN));
}
END_TEST

START_TEST(ceil1) {
  ck_assert_float_eq_tol(ceil(0.0), s21_ceil(0.0), 1E-6);
  ck_assert_float_eq_tol(ceil(-0.0), s21_ceil(-0.0), 1E-6);
  ck_assert_float_eq_tol(ceil(1.000001), s21_ceil(1.000001), 1E-6);
  ck_assert_float_eq_tol(ceil(2.00000), s21_ceil(2.00000), 1E-6);
  ck_assert_float_eq_tol(ceil(-2.00000), s21_ceil(-2.00000), 1E-6);
  ck_assert_float_eq_tol(ceil(-1.000001), s21_ceil(-1.000001), 1E-6);
  ck_assert_float_eq_tol(ceil(1.99999), s21_ceil(1.99999), 1E-6);
  ck_assert_float_eq_tol(ceil(-1.99999), s21_ceil(-1.99999), 1E-6);
  ck_assert_float_eq_tol(ceil(111111111.999999999),
                         s21_ceil(111111111.999999999), 1E-6);
  ck_assert_float_eq_tol(ceil(111111111.00000000001),
                         s21_ceil(111111111.00000000001), 1E-6);
  ck_assert_float_eq_tol(ceil(-111111111.999999999),
                         s21_ceil(-111111111.999999999), 1E-6);
  ck_assert_float_eq_tol(ceil(-111111111.00000000001),
                         s21_ceil(-111111111.00000000001), 1E-6);
  ck_assert_float_eq_tol(ceil(-99999999999999999.9999999999999999),
                         s21_ceil(-99999999999999999.9999999999999999), 1E-6);
  ck_assert_float_eq_tol(ceil(99999999999999999.9999999999999999),
                         s21_ceil(99999999999999999.9999999999999999), 1E-6);
  ck_assert_float_eq_tol(ceil(11111111111111111.000000000000000001),
                         s21_ceil(11111111111111111.000000000000000001), 1E-6);
  ck_assert_float_eq_tol(ceil(-11111111111111111.0000000000000001),
                         s21_ceil(-11111111111111111.0000000000000001), 1E-6);
  ck_assert_float_eq(ceil(S21_INFINITY), s21_ceil(S21_INFINITY));
  ck_assert_float_eq(ceil(-S21_INFINITY), s21_ceil(-S21_INFINITY));
  ck_assert_double_nan(s21_ceil(S21_NAN));
}
END_TEST

START_TEST(cos1) {
  // сравниваем float до 1E-6 знака
  ck_assert_float_eq_tol(cos(S21_PI), s21_cos(S21_PI), 1E-6);
  ck_assert_float_eq_tol(cos(-S21_PI), s21_cos(-S21_PI), 1E-6);
  ck_assert_float_eq_tol(cos(2 * S21_PI), s21_cos(2 * S21_PI), 1E-6);
  ck_assert_float_eq_tol(cos(-2 * S21_PI), s21_cos(-2 * S21_PI), 1E-6);
  ck_assert_float_eq_tol(cos(S21_PI / 2), s21_cos(S21_PI / 2), 1E-6);
  ck_assert_float_eq_tol(cos(-S21_PI / 2), s21_cos(-S21_PI / 2), 1E-6);
  ck_assert_float_eq_tol(cos(3 * S21_PI), s21_cos(3 * S21_PI), 1E-6);
  ck_assert_float_eq_tol(cos(-3 * S21_PI), s21_cos(-3 * S21_PI), 1E-6);
  ck_assert_float_eq_tol(cos(S21_PI / 3), s21_cos(S21_PI / 3), 1E-6);
  ck_assert_float_eq_tol(cos(-S21_PI / 3), s21_cos(-S21_PI / 3), 1E-6);
  ck_assert_float_eq_tol(cos(13 * S21_PI), s21_cos(13 * S21_PI), 1E-6);
  ck_assert_float_eq_tol(cos(-13 * S21_PI), s21_cos(-13 * S21_PI), 1E-6);
  ck_assert_float_eq_tol(cos(S21_PI / 13), s21_cos(S21_PI / 13), 1E-6);
  ck_assert_float_eq_tol(cos(-S21_PI / 13), s21_cos(-S21_PI / 13), 1E-6);
  ck_assert_float_eq_tol(cos(0.0), s21_cos(0.0), 1E-6);
  ck_assert_float_eq_tol(cos(-0.0), s21_cos(-0.0), 1E-6);
  ck_assert_float_eq_tol(cos(1.), s21_cos(1.), 1E-6);
  ck_assert_float_eq_tol(cos(-1.), s21_cos(-1.), 1E-6);
  ck_assert_float_eq_tol(cos(2.), s21_cos(2.), 1E-6);
  ck_assert_float_eq_tol(cos(100.), s21_cos(100.), 1E-6);
  ck_assert_float_eq_tol(cos(-100.), s21_cos(-100.), 1E-6);
  ck_assert_float_eq_tol(cos(-100.123456789), s21_cos(-100.123456789), 1E-6);
  ck_assert_float_eq_tol(cos(100.123456789), s21_cos(100.123456789), 1E-6);
  ck_assert_float_eq_tol(cos(9999.), s21_cos(9999.), 1E-6);
  ck_assert_float_eq_tol(cos(-9999.), s21_cos(-9999.), 1E-6);
  ck_assert_float_eq_tol(cos(99999.), s21_cos(99999.), 1E-6);
  ck_assert_float_eq_tol(cos(999999.), s21_cos(999999.), 1E-6);
  ck_assert_float_eq_tol(cos(-999999.), s21_cos(-999999.), 1E-6);
  ck_assert_float_eq_tol(cos(-999999.1111111), s21_cos(-999999.1111111), 1E-6);
  ck_assert_float_eq_tol(cos(999999.1111111), s21_cos(999999.1111111), 1E-6);
  ck_assert_float_eq_tol(cos(999999.999999999999), s21_cos(999999.999999999999),
                         1E-6);
  ck_assert_float_eq_tol(cos(-999999.999999999999),
                         s21_cos(-999999.999999999999), 1E-6);
  ck_assert_float_eq_tol(cos(123456.123456), s21_cos(123456.123456), 1E-6);
  ck_assert_float_eq_tol(cos(-123456.123456), s21_cos(-123456.123456), 1E-6);
  ck_assert_float_eq_tol(cos(9999999.), s21_cos(9999999.), 1E-6);
  ck_assert_float_eq_tol(cos(99999999999.), s21_cos(99999999999.), 1E-6);
  ck_assert_float_eq_tol(cos(-99999999999.), s21_cos(-99999999999.), 1E-6);
  ck_assert_double_nan(s21_cos(S21_NAN));
  // if S21_INFINITY nan
  ck_assert_double_nan(s21_cos(S21_INFINITY));
  ck_assert_double_nan(s21_cos(-S21_INFINITY));
}
END_TEST

START_TEST(acos1) {
  ck_assert_float_eq_tol(acos(S21_PI / 13), s21_acos(S21_PI / 13), 1E-6);
  ck_assert_float_eq_tol(acos(-S21_PI / 13), s21_acos(-S21_PI / 13), 1E-6);
  ck_assert_float_eq_tol(acos(0.0), s21_acos(0.0), 1E-6);
  ck_assert_float_eq_tol(acos(-0.0), s21_acos(-0.0), 1E-6);
  ck_assert_float_eq_tol(acos(1.), s21_acos(1.), 1E-6);
  ck_assert_float_eq_tol(acos(0.7), s21_acos(0.7), 1E-6);
  ck_assert_float_eq_tol(acos(0.999), s21_acos(0.999), 1E-6);
  ck_assert_float_eq_tol(acos(-0.999), s21_acos(-0.999), 1E-6);
  ck_assert_float_eq_tol(acos(-0.7), s21_acos(-0.7), 1E-6);
  ck_assert_float_eq_tol(acos(-1.), s21_acos(-1.), 1E-6);

  ck_assert_double_nan(s21_acos(S21_PI));
  ck_assert_double_nan(s21_acos(-S21_PI));
  ck_assert_double_nan(s21_acos(S21_PI / 2));
  ck_assert_double_nan(s21_acos(-S21_PI / 2));
  ck_assert_double_nan(s21_acos(S21_PI / 3));
  ck_assert_double_nan(s21_acos(-S21_PI / 3));
  ck_assert_double_nan(s21_acos(2 * S21_PI));
  ck_assert_double_nan(s21_acos(-2 * S21_PI));
  ck_assert_double_nan(s21_acos(3 * S21_PI));
  ck_assert_double_nan(s21_acos(-3 * S21_PI));
  ck_assert_double_nan(s21_acos(13 * S21_PI));
  ck_assert_double_nan(s21_acos(-13 * S21_PI));
  ck_assert_double_nan(s21_acos(9999999999999999999999.9));
  ck_assert_double_nan(s21_acos(-9999999999999999999999.9));

  ck_assert_double_nan(s21_acos(S21_NAN));
  ck_assert_double_nan(s21_acos(S21_INFINITY));
  ck_assert_double_nan(s21_acos(-S21_INFINITY));
}
END_TEST

START_TEST(sin1) {
  ck_assert_float_eq_tol(sin(S21_PI), s21_sin(S21_PI), 1E-6);
  ck_assert_float_eq_tol(sin(-S21_PI), s21_sin(-S21_PI), 1E-6);
  ck_assert_float_eq_tol(sin(2 * S21_PI), s21_sin(2 * S21_PI), 1E-6);
  ck_assert_float_eq_tol(sin(-2 * S21_PI), s21_sin(-2 * S21_PI), 1E-6);
  ck_assert_float_eq_tol(sin(S21_PI / 2), s21_sin(S21_PI / 2), 1E-6);
  ck_assert_float_eq_tol(sin(-S21_PI / 2), s21_sin(-S21_PI / 2), 1E-6);
  ck_assert_float_eq_tol(sin(3 * S21_PI), s21_sin(3 * S21_PI), 1E-6);
  ck_assert_float_eq_tol(sin(-3 * S21_PI), s21_sin(-3 * S21_PI), 1E-6);
  ck_assert_float_eq_tol(sin(S21_PI / 3), s21_sin(S21_PI / 3), 1E-6);
  ck_assert_float_eq_tol(sin(-S21_PI / 3), s21_sin(-S21_PI / 3), 1E-6);
  ck_assert_float_eq_tol(sin(13 * S21_PI), s21_sin(13 * S21_PI), 1E-6);
  ck_assert_float_eq_tol(sin(-13 * S21_PI), s21_sin(-13 * S21_PI), 1E-6);
  ck_assert_float_eq_tol(sin(S21_PI / 13), s21_sin(S21_PI / 13), 1E-6);
  ck_assert_float_eq_tol(sin(-S21_PI / 13), s21_sin(-S21_PI / 13), 1E-6);
  ck_assert_float_eq_tol(sin(0.0), s21_sin(0.0), 1E-6);
  ck_assert_float_eq_tol(sin(-0.0), s21_sin(-0.0), 1E-6);
  ck_assert_float_eq_tol(sin(1.), s21_sin(1.), 1E-6);
  ck_assert_float_eq_tol(sin(-1.), s21_sin(-1.), 1E-6);
  ck_assert_float_eq_tol(sin(2.), s21_sin(2.), 1E-6);
  ck_assert_float_eq_tol(sin(100.), s21_sin(100.), 1E-6);
  ck_assert_float_eq_tol(sin(-100.), s21_sin(-100.), 1E-6);
  ck_assert_float_eq_tol(sin(-100.123456789), s21_sin(-100.123456789), 1E-6);
  ck_assert_float_eq_tol(sin(100.123456789), s21_sin(100.123456789), 1E-6);
  ck_assert_float_eq_tol(sin(9999.), s21_sin(9999.), 1E-6);
  ck_assert_float_eq_tol(sin(-9999.), s21_sin(-9999.), 1E-6);
  ck_assert_float_eq_tol(sin(99999.), s21_sin(99999.), 1E-6);
  ck_assert_float_eq_tol(sin(999999.), s21_sin(999999.), 1E-6);
  ck_assert_float_eq_tol(sin(-999999.), s21_sin(-999999.), 1E-6);
  ck_assert_float_eq_tol(sin(-999999.1111111), s21_sin(-999999.1111111), 1E-6);
  ck_assert_float_eq_tol(sin(999999.1111111), s21_sin(999999.1111111), 1E-6);
  ck_assert_float_eq_tol(sin(999999.999999999999), s21_sin(999999.999999999999),
                         1E-6);
  ck_assert_float_eq_tol(sin(-999999.999999999999),
                         s21_sin(-999999.999999999999), 1E-6);
  ck_assert_float_eq_tol(sin(123456.123456), s21_sin(123456.123456), 1E-6);
  ck_assert_float_eq_tol(sin(-123456.123456), s21_sin(-123456.123456), 1E-6);
  ck_assert_float_eq_tol(sin(9999999.), s21_sin(9999999.), 1E-6);
  ck_assert_float_eq_tol(sin(9999999999.), s21_sin(9999999999.), 1E-6);
  ck_assert_float_eq_tol(sin(-9999999999.), s21_sin(-9999999999.), 1E-6);
  ck_assert_double_nan(s21_sin(S21_NAN));
  // if S21_INFINITY nan
  ck_assert_double_nan(s21_sin(S21_INFINITY));
  ck_assert_double_nan(s21_sin(-S21_INFINITY));
}
END_TEST

START_TEST(asin1) {
  ck_assert_float_eq_tol(asin(S21_PI / 13), s21_asin(S21_PI / 13), 1E-6);
  ck_assert_float_eq_tol(asin(-S21_PI / 13), s21_asin(-S21_PI / 13), 1E-6);
  ck_assert_float_eq_tol(asin(0.0), s21_asin(0.0), 1E-6);
  ck_assert_float_eq_tol(asin(-0.0), s21_asin(-0.0), 1E-6);
  ck_assert_float_eq_tol(asin(1.), s21_asin(1.), 1E-6);
  ck_assert_float_eq_tol(asin(0.7), s21_asin(0.7), 1E-6);
  ck_assert_float_eq_tol(asin(0.999), s21_asin(0.999), 1E-6);
  ck_assert_float_eq_tol(asin(-0.999), s21_asin(-0.999), 1E-6);
  ck_assert_float_eq_tol(asin(-0.7), s21_asin(-0.7), 1E-6);
  ck_assert_float_eq_tol(asin(-1.), s21_asin(-1.), 1E-6);

  ck_assert_double_nan(s21_asin(S21_PI));
  ck_assert_double_nan(s21_asin(-S21_PI));
  ck_assert_double_nan(s21_asin(S21_PI / 2));
  ck_assert_double_nan(s21_asin(-S21_PI / 2));
  ck_assert_double_nan(s21_asin(S21_PI / 3));
  ck_assert_double_nan(s21_asin(-S21_PI / 3));
  ck_assert_double_nan(s21_asin(2 * S21_PI));
  ck_assert_double_nan(s21_asin(-2 * S21_PI));
  ck_assert_double_nan(s21_asin(3 * S21_PI));
  ck_assert_double_nan(s21_asin(-3 * S21_PI));
  ck_assert_double_nan(s21_asin(13 * S21_PI));
  ck_assert_double_nan(s21_asin(-13 * S21_PI));
  ck_assert_double_nan(s21_asin(999999999999999999999999999999.9));
  ck_assert_double_nan(s21_asin(-999999999999999999999999999999.9));

  ck_assert_double_nan(s21_asin(S21_NAN));
  ck_assert_double_nan(s21_asin(S21_INFINITY));
  ck_assert_double_nan(s21_asin(-S21_INFINITY));
}
END_TEST

START_TEST(tan1) {
  ck_assert_float_eq_tol(tan(S21_PI), s21_tan(S21_PI), 1E-6);
  ck_assert_float_eq_tol(tan(-S21_PI), s21_tan(-S21_PI), 1E-6);
  ck_assert_float_eq_tol(tan(2 * S21_PI), s21_tan(2 * S21_PI), 1E-6);
  ck_assert_float_eq_tol(tan(-2 * S21_PI), s21_tan(-2 * S21_PI), 1E-6);
  // ck_assert_float_eq_tol(tan(S21_PI/2), s21_tan(S21_PI/2), 1E-6);
  // ck_assert_float_eq_tol(tan(-S21_PI/2), s21_tan(-S21_PI/2), 1E-6);
  ck_assert_float_eq_tol(tan(3 * S21_PI), s21_tan(3 * S21_PI), 1E-6);
  ck_assert_float_eq_tol(tan(-3 * S21_PI), s21_tan(-3 * S21_PI), 1E-6);
  ck_assert_float_eq_tol(tan(S21_PI / 3), s21_tan(S21_PI / 3), 1E-6);
  ck_assert_float_eq_tol(tan(-S21_PI / 3), s21_tan(-S21_PI / 3), 1E-6);
  ck_assert_float_eq_tol(tan(13 * S21_PI), s21_tan(13 * S21_PI), 1E-6);
  ck_assert_float_eq_tol(tan(-13 * S21_PI), s21_tan(-13 * S21_PI), 1E-6);
  ck_assert_float_eq_tol(tan(S21_PI / 13), s21_tan(S21_PI / 13), 1E-6);
  ck_assert_float_eq_tol(tan(-S21_PI / 13), s21_tan(-S21_PI / 13), 1E-6);
  ck_assert_float_eq_tol(tan(0.0), s21_tan(0.0), 1E-6);
  ck_assert_float_eq_tol(tan(-0.0), s21_tan(-0.0), 1E-6);
  ck_assert_float_eq_tol(tan(1.), s21_tan(1.), 1E-6);
  ck_assert_float_eq_tol(tan(-1.), s21_tan(-1.), 1E-6);
  ck_assert_float_eq_tol(tan(2.), s21_tan(2.), 1E-6);
  ck_assert_float_eq_tol(tan(100.), s21_tan(100.), 1E-6);
  ck_assert_float_eq_tol(tan(-100.), s21_tan(-100.), 1E-6);
  ck_assert_float_eq_tol(tan(-100.123456789), s21_tan(-100.123456789), 1E-6);
  ck_assert_float_eq_tol(tan(100.123456789), s21_tan(100.123456789), 1E-6);
  ck_assert_float_eq_tol(tan(9999.), s21_tan(9999.), 1E-6);
  ck_assert_float_eq_tol(tan(-9999.), s21_tan(-9999.), 1E-6);
  ck_assert_float_eq_tol(tan(99999.), s21_tan(99999.), 1E-6);
  ck_assert_float_eq_tol(tan(999999.), s21_tan(999999.), 1E-6);
  ck_assert_float_eq_tol(tan(-999999.), s21_tan(-999999.), 1E-6);
  ck_assert_float_eq_tol(tan(-999999.1111111), s21_tan(-999999.1111111), 1E-6);
  ck_assert_float_eq_tol(tan(999999.1111111), s21_tan(999999.1111111), 1E-6);
  ck_assert_float_eq_tol(tan(999999.999999999999), s21_tan(999999.999999999999),
                         1E-6);
  ck_assert_float_eq_tol(tan(-999999.999999999999),
                         s21_tan(-999999.999999999999), 1E-6);
  ck_assert_float_eq_tol(tan(123456.123456), s21_tan(123456.123456), 1E-6);
  ck_assert_float_eq_tol(tan(-123456.123456), s21_tan(-123456.123456), 1E-6);
  ck_assert_float_eq_tol(tan(9999999.), s21_tan(9999999.), 1E-6);
  // ck_assert_float_eq_tol(tan(99999999.), s21_tan(9999999.), 1E-6);
  // ck_assert_float_eq_tol(tan(-99999999999.), s21_tan(-99999999999.), 1E-6);
  ck_assert_double_nan(s21_tan(S21_NAN));
  // if S21_INFINITY nan
  ck_assert_double_nan(s21_tan(S21_INFINITY));
  ck_assert_double_nan(s21_tan(-S21_INFINITY));
}
END_TEST

START_TEST(atan1) {
  ck_assert_float_eq_tol(atan(S21_PI), s21_atan(S21_PI), 1E-6);
  ck_assert_float_eq_tol(atan(-S21_PI), s21_atan(-S21_PI), 1E-6);
  ck_assert_float_eq_tol(atan(2 * S21_PI), s21_atan(2 * S21_PI), 1E-6);
  ck_assert_float_eq_tol(atan(-2 * S21_PI), s21_atan(-2 * S21_PI), 1E-6);
  ck_assert_float_eq_tol(atan(S21_PI / 2), s21_atan(S21_PI / 2), 1E-6);
  ck_assert_float_eq_tol(atan(-S21_PI / 2), s21_atan(-S21_PI / 2), 1E-6);
  ck_assert_float_eq_tol(atan(3 * S21_PI), s21_atan(3 * S21_PI), 1E-6);
  ck_assert_float_eq_tol(atan(-3 * S21_PI), s21_atan(-3 * S21_PI), 1E-6);
  ck_assert_float_eq_tol(atan(S21_PI / 3), s21_atan(S21_PI / 3), 1E-6);
  ck_assert_float_eq_tol(atan(-S21_PI / 3), s21_atan(-S21_PI / 3), 1E-6);
  ck_assert_float_eq_tol(atan(13 * S21_PI), s21_atan(13 * S21_PI), 1E-6);
  ck_assert_float_eq_tol(atan(-13 * S21_PI), s21_atan(-13 * S21_PI), 1E-6);
  ck_assert_float_eq_tol(atan(S21_PI / 13), s21_atan(S21_PI / 13), 1E-6);
  ck_assert_float_eq_tol(atan(-S21_PI / 13), s21_atan(-S21_PI / 13), 1E-6);
  ck_assert_float_eq_tol(atan(0.0), s21_atan(0.0), 1E-6);
  ck_assert_float_eq_tol(atan(-0.0), s21_atan(-0.0), 1E-6);
  ck_assert_float_eq_tol(atan(1.), s21_atan(1.), 1E-6);
  ck_assert_float_eq_tol(atan(-1.), s21_atan(-1.), 1E-6);
  ck_assert_float_eq_tol(atan(2.), s21_atan(2.), 1E-6);
  ck_assert_float_eq_tol(atan(100.), s21_atan(100.), 1E-6);
  ck_assert_float_eq_tol(atan(-100.), s21_atan(-100.), 1E-6);
  ck_assert_float_eq_tol(atan(-100.123456789), s21_atan(-100.123456789), 1E-6);
  ck_assert_float_eq_tol(atan(100.123456789), s21_atan(100.123456789), 1E-6);
  // ck_assert_float_eq_tol(atan(99999999999.), s21_atan(99999999999.), 1E-6);
  // ck_assert_float_eq_tol(atan(-99999999999.), s21_atan(-99999999999.), 1E-6);

  ck_assert_float_eq(atan(S21_INFINITY), s21_atan(S21_INFINITY));
  ck_assert_float_eq(atan(-S21_INFINITY), s21_atan(-S21_INFINITY));
  ck_assert_double_nan(s21_atan(S21_NAN));
}
END_TEST

START_TEST(exp1) {
  ck_assert_float_eq_tol(exp(0.), s21_exp(0.), 1E-6);
  ck_assert_float_eq_tol(exp(-0.), s21_exp(-0.), 1E-6);
  ck_assert_float_eq_tol(exp(-1.000001), s21_exp(-1.000001), 1E-6);
  ck_assert_float_eq_tol(exp(-1.999999999), s21_exp(-1.999999999), 1E-6);
  ck_assert_float_eq_tol(exp(10.), s21_exp(10.), 1E-6);
  ck_assert_float_eq(exp(500), s21_exp(500));
  ck_assert_float_eq(exp(1000), s21_exp(1000));
  ck_assert_float_eq(exp(99999999), s21_exp(99999999));
  ck_assert_float_eq(exp(999999999999999.999), s21_exp(999999999999999.999));
  ck_assert_float_eq_tol(exp(-99999999999999999.99999999999999999),
                         s21_exp(-99999999999999999.99999999999999999), 1E-6);
  ck_assert_double_nan(s21_exp(S21_NAN));
  ck_assert_float_eq(exp(S21_INFINITY), s21_exp(S21_INFINITY));
  ck_assert_float_eq(exp(-S21_INFINITY), s21_exp(-S21_INFINITY));
}
END_TEST

START_TEST(log1) {
  ck_assert_float_eq(log(0.), s21_log(0.));
  ck_assert_float_eq(log(-0.), s21_log(-0.));
  ck_assert_float_nan(s21_log(-1.000001));
  ck_assert_float_nan(s21_log(-999999999.999));
  ck_assert_float_eq_tol(log(999999.999), s21_log(999999.999), 1E-6);
  ck_assert_double_nan(s21_log(S21_NAN));
  ck_assert_double_nan(s21_log(-S21_INFINITY));
  ck_assert_float_eq(log(S21_INFINITY), s21_log(S21_INFINITY));
}
END_TEST

START_TEST(sqrt1) {
  ck_assert_float_eq_tol(sqrt(0.), s21_sqrt(0.), 1E-6);
  ck_assert_float_eq_tol(sqrt(-0.), s21_sqrt(-0.), 1E-6);
  ck_assert_float_eq_tol(sqrt(4.), s21_sqrt(4.), 1E-6);
  ck_assert_float_eq_tol(sqrt(16.), s21_sqrt(16.), 1E-6);
  ck_assert_double_nan(s21_sqrt(-1.00001));
  ck_assert_double_nan(s21_sqrt(-1.999999999));
  ck_assert_float_eq_tol(sqrt(2147483647.), s21_sqrt(2147483647.), 1E-6);
  ck_assert_double_nan(s21_sqrt(-2147483647.));
  ck_assert_double_nan(s21_sqrt(-9999999999.9999999));
  ck_assert_double_nan(s21_sqrt(-99999999999.9999999));
  ck_assert_float_eq_tol(sqrt(999999999999), s21_sqrt(999999999999), 1E-6);
  ck_assert_float_eq_tol(sqrt(9999999999999), s21_sqrt(9999999999999), 1E-6);
  ck_assert_float_eq_tol(sqrt(999999999999.999), s21_sqrt(999999999999.999),
                         1E-6);
  ck_assert_float_eq_tol(sqrt(9999999999999.999), s21_sqrt(9999999999999.999),
                         1E-6);
  ck_assert_double_nan(s21_sqrt(S21_NAN));
  ck_assert_float_eq(sqrt(S21_INFINITY), s21_sqrt(S21_INFINITY));
  ck_assert_double_nan(s21_sqrt(-S21_INFINITY));
}
END_TEST

START_TEST(fmod1) {
  ck_assert_double_nan(s21_fmod(0., 0.));
  ck_assert_double_nan(s21_fmod(-0., 0.));
  ck_assert_double_nan(s21_fmod(0., -0.));
  ck_assert_double_nan(s21_fmod(-0., -0.));

  ck_assert_double_nan(s21_fmod(-1., -0.));
  ck_assert_double_nan(s21_fmod(1., 0.));
  ck_assert_double_nan(s21_fmod(-1., 0.));
  ck_assert_double_nan(s21_fmod(1., -0.));

  ck_assert_double_nan(s21_fmod(-1.22, -0.));
  ck_assert_double_nan(s21_fmod(1.22, 0.));
  ck_assert_double_nan(s21_fmod(-1.22, 0.));
  ck_assert_double_nan(s21_fmod(1.22, -0.));

  ck_assert_float_eq_tol(fmod(0., S21_INFINITY), s21_fmod(0., S21_INFINITY),
                         1E-6);
  ck_assert_float_eq_tol(fmod(0., -S21_INFINITY), s21_fmod(0., -S21_INFINITY),
                         1E-6);
  ck_assert_float_eq_tol(fmod(1.0000001, S21_INFINITY),
                         s21_fmod(1.0000001, S21_INFINITY), 1E-6);
  ck_assert_float_eq_tol(fmod(1.0000001, -S21_INFINITY),
                         s21_fmod(1.0000001, -S21_INFINITY), 1E-6);
  ck_assert_float_eq_tol(fmod(-1.0000001, S21_INFINITY),
                         s21_fmod(-1.0000001, S21_INFINITY), 1E-6);
  ck_assert_float_eq_tol(fmod(-1.0000001, -S21_INFINITY),
                         s21_fmod(-1.0000001, -S21_INFINITY), 1E-6);

  ck_assert_float_eq_tol(fmod(1.22, 0.22), s21_fmod(1.22, 0.22), 1E-6);
  ck_assert_float_eq_tol(fmod(-1.22, 0.22), s21_fmod(-1.22, 0.22), 1E-6);
  ck_assert_float_eq_tol(fmod(1.22, -0.22), s21_fmod(1.22, -0.22), 1E-6);

  ck_assert_float_eq_tol(fmod(0., 0.22), s21_fmod(0., 0.22), 1E-6);
  ck_assert_float_eq_tol(fmod(-0., 0.22), s21_fmod(-0., 0.22), 1E-6);
  ck_assert_float_eq_tol(fmod(0., -0.22), s21_fmod(0., -0.22), 1E-6);
  ck_assert_float_eq_tol(fmod(-0., -0.22), s21_fmod(-0., -0.22), 1E-6);

  ck_assert_float_eq_tol(fmod(0., 5.9999), s21_fmod(0., 5.9999), 1E-6);
  ck_assert_float_eq_tol(fmod(-0., 5.9999), s21_fmod(-0., 5.9999), 1E-6);
  ck_assert_float_eq_tol(fmod(0., -5.9999), s21_fmod(0., -5.9999), 1E-6);
  ck_assert_float_eq_tol(fmod(-0., -5.9999), s21_fmod(-0., -5.9999), 1E-6);

  ck_assert_float_eq_tol(fmod(123456789.123456789, 5.9999),
                         s21_fmod(123456789.123456789, 5.9999), 1E-6);
  ck_assert_float_eq_tol(fmod(-123456789.123456789, 5.9999),
                         s21_fmod(-123456789.123456789, 5.9999), 1E-6);
  ck_assert_float_eq_tol(fmod(123456789.123456789, -5.9999),
                         s21_fmod(123456789.123456789, -5.9999), 1E-6);
  ck_assert_float_eq_tol(fmod(-123456789.123456789, -5.9999),
                         s21_fmod(-123456789.123456789, -5.9999), 1E-6);

  ck_assert_float_eq_tol(fmod(123456789.123456789, 98.111),
                         s21_fmod(123456789.123456789, 98.111), 1E-6);
  ck_assert_float_eq_tol(fmod(-123456789.123456789, 98.111),
                         s21_fmod(-123456789.123456789, 98.111), 1E-6);
  ck_assert_float_eq_tol(fmod(123456789.123456789, -98.111),
                         s21_fmod(123456789.123456789, -98.111), 1E-6);
  ck_assert_float_eq_tol(fmod(-123456789.123456789, -98.111),
                         s21_fmod(-123456789.123456789, -98.111), 1E-6);

  ck_assert_double_nan(s21_fmod(S21_INFINITY, S21_NAN));
  ck_assert_double_nan(s21_fmod(S21_INFINITY, -S21_NAN));
  ck_assert_double_nan(s21_fmod(S21_INFINITY, 0));
  ck_assert_double_nan(s21_fmod(S21_INFINITY, -0));
  ck_assert_double_nan(s21_fmod(S21_INFINITY, 1));
  ck_assert_double_nan(s21_fmod(S21_INFINITY, -5.9999));

  ck_assert_double_nan(s21_fmod(-S21_INFINITY, S21_NAN));
  ck_assert_double_nan(s21_fmod(-S21_INFINITY, -S21_NAN));
  ck_assert_double_nan(s21_fmod(-S21_INFINITY, 0));
  ck_assert_double_nan(s21_fmod(-S21_INFINITY, -0));
  ck_assert_double_nan(s21_fmod(-S21_INFINITY, 1));
  ck_assert_double_nan(s21_fmod(-S21_INFINITY, -5.9999));

  ck_assert_double_nan(s21_fmod(S21_NAN, S21_INFINITY));
  ck_assert_double_nan(s21_fmod(S21_NAN, -S21_INFINITY));
  ck_assert_double_nan(s21_fmod(S21_NAN, 0));
  ck_assert_double_nan(s21_fmod(S21_NAN, -0));
  ck_assert_double_nan(s21_fmod(S21_NAN, 1));
  ck_assert_double_nan(s21_fmod(S21_NAN, -5.9999));

  ck_assert_double_nan(s21_fmod(-S21_NAN, -S21_INFINITY));
  ck_assert_double_nan(s21_fmod(-S21_NAN, S21_INFINITY));
  ck_assert_double_nan(s21_fmod(-S21_NAN, 0));
  ck_assert_double_nan(s21_fmod(-S21_NAN, -0));
  ck_assert_double_nan(s21_fmod(-S21_NAN, 1));
  ck_assert_double_nan(s21_fmod(-S21_NAN, -5.9999));
}
END_TEST

START_TEST(pow1) {
  ck_assert_float_eq_tol(pow(-0., -0.), s21_pow(-0., -0.), 1E-6);
  ck_assert_float_eq_tol(pow(0., 0.), s21_pow(0., 0.), 1E-6);
  ck_assert_float_eq_tol(pow(-0., 0.), s21_pow(-0., 0.), 1E-6);
  ck_assert_float_eq_tol(pow(0., -0.), s21_pow(0., -0.), 1E-6);

  ck_assert_float_eq_tol(pow(-1., -0.), s21_pow(-1., -0.), 1E-6);
  ck_assert_float_eq_tol(pow(1., 0.), s21_pow(1., 0.), 1E-6);
  ck_assert_float_eq_tol(pow(-1., 0.), s21_pow(-1., 0.), 1E-6);
  ck_assert_float_eq_tol(pow(1., -0.), s21_pow(1., -0.), 1E-6);

  ck_assert_float_eq_tol(pow(-1.22, -0.), s21_pow(-1.22, -0.), 1E-6);
  ck_assert_float_eq_tol(pow(1.22, 0.), s21_pow(1.22, 0.), 1E-6);
  ck_assert_float_eq_tol(pow(-1.22, 0.), s21_pow(-1.22, 0.), 1E-6);
  ck_assert_float_eq_tol(pow(1.22, -0.), s21_pow(1.22, -0.), 1E-6);

  // nan
  // ck_assert_float_eq_tol(pow(-1.22, -0.22), s21_pow(-1.22, -0.22), 1E-6);
  // ck_assert_float_eq_tol(pow(-1.22, 0.22), s21_pow(-1.22, 0.22), 1E-6);
  ck_assert_double_nan(s21_pow(-1.22, -0.22));
  ck_assert_double_nan(s21_pow(-1.22, 0.22));

  ck_assert_float_eq_tol(pow(1.22, 0.22), s21_pow(1.22, 0.22), 1E-6);
  ck_assert_float_eq_tol(pow(1.22, -0.22), s21_pow(1.22, -0.22), 1E-6);

  ck_assert_float_eq_tol(pow(0., 0.22), s21_pow(0., 0.22), 1E-6);
  ck_assert_float_eq_tol(pow(-0., 0.22), s21_pow(-0., 0.22), 1E-6);
  ck_assert_float_eq(pow(0., -0.22), s21_pow(0., -0.22));
  ck_assert_float_eq(pow(-0., -0.22), s21_pow(-0., -0.22));

  ck_assert_float_eq_tol(pow(0., 5.9999), s21_pow(0., 5.9999), 1E-6);
  ck_assert_float_eq_tol(pow(-0., 5.9999), s21_pow(-0., 5.9999), 1E-6);
  ck_assert_float_eq(pow(0., -5.9999), s21_pow(0., -5.9999));
  ck_assert_float_eq(pow(-0., -5.9999), s21_pow(-0., -5.9999));

  ck_assert_float_eq_tol(pow(12345.123456789, 5.9999),
                         s21_pow(12345.123456789, 5.9999), 1E-6);
  ck_assert_float_eq_tol(pow(12345.123456789, -5.9999),
                         s21_pow(12345.123456789, -5.9999), 1E-6);

  // ck_assert_float_eq_tol(pow(-12345.123456789, 5.9999),
  // s21_pow(-12345.123456789, 5.9999), 1E-6);
  ck_assert_double_nan(s21_pow(-12345.123456789, 5.9999));

  // ck_assert_float_eq_tol(pow(-12345.123456789, -5.9999),
  // s21_pow(-12345.123456789, -5.9999), 1E-6);
  ck_assert_double_nan(s21_pow(-12345.123456789, 5.9999));

  ck_assert_float_eq(pow(100., 100), s21_pow(100., 100));
  ck_assert_float_eq(pow(1000., 100), s21_pow(1000., 100));
  ck_assert_float_eq(pow(99000., 100), s21_pow(99000., 100));
  ck_assert_float_eq(pow(99999.999, 100), s21_pow(99999.999, 100));
  // ck_assert_float_eq(pow(99999.999, 999.123), s21_pow(99999.999, 999.123));
  // ck_assert_float_eq(pow(9999999.999, 999999.123), s21_pow(9999999.999,
  // 999999.123));

  ck_assert_float_eq(pow(-100., 100), s21_pow(-100., 100));
  ck_assert_float_eq(pow(-1000., 100), s21_pow(-1000., 100));
  ck_assert_float_eq(pow(-99000., 100), s21_pow(-99000., 100));
  ck_assert_float_eq(pow(-99999.999, 100), s21_pow(-99999.999, 100));
  // ck_assert_float_eq(pow(-9999999.999, 999999.123), s21_pow(-9999999.999,
  // 999999.123)); ck_assert_double_nan( s21_pow(-9999999.999, 999999.123));

  // INF
  ck_assert_float_eq(pow(S21_INFINITY, 5.9999), s21_pow(S21_INFINITY, 5.9999));
  ck_assert_float_eq(pow(-S21_INFINITY, 5.9999),
                     s21_pow(-S21_INFINITY, 5.9999));
  ck_assert_float_eq(pow(S21_INFINITY, -5.9999),
                     s21_pow(S21_INFINITY, -5.9999));
  ck_assert_float_eq(pow(-S21_INFINITY, -5.9999),
                     s21_pow(-S21_INFINITY, -5.9999));

  // ck_assert_float_eq(pow(-S21_INFINITY, S21_NAN), s21_pow(-S21_INFINITY,
  // S21_NAN));
  ck_assert_float_eq(pow(-S21_INFINITY, S21_INFINITY),
                     s21_pow(-S21_INFINITY, S21_INFINITY));
  ck_assert_float_eq(pow(-S21_INFINITY, -S21_INFINITY),
                     s21_pow(-S21_INFINITY, -S21_INFINITY));
  ck_assert_float_eq(pow(-S21_INFINITY, 0), s21_pow(-S21_INFINITY, 0));
  ck_assert_float_eq(pow(-S21_INFINITY, 1), s21_pow(-S21_INFINITY, 1));
  ck_assert_float_eq(pow(-S21_INFINITY, -1), s21_pow(-S21_INFINITY, -1));

  // ck_assert_float_eq(pow(S21_INFINITY, S21_NAN), s21_pow(S21_INFINITY,
  // S21_NAN));
  ck_assert_float_eq(pow(S21_INFINITY, S21_INFINITY),
                     s21_pow(S21_INFINITY, S21_INFINITY));
  ck_assert_float_eq(pow(S21_INFINITY, -S21_INFINITY),
                     s21_pow(S21_INFINITY, -S21_INFINITY));
  ck_assert_float_eq(pow(S21_INFINITY, 0), s21_pow(S21_INFINITY, 0));
  ck_assert_float_eq(pow(S21_INFINITY, 1), s21_pow(S21_INFINITY, 1));
  ck_assert_float_eq(pow(S21_INFINITY, -1), s21_pow(S21_INFINITY, -1));

  // ck_assert_float_eq(pow(S21_NAN, S21_NAN), s21_pow(S21_NAN, S21_NAN));
  // ck_assert_float_eq(pow(S21_NAN, S21_INFINITY), s21_pow(S21_NAN,
  // S21_INFINITY)); ck_assert_float_eq(pow(S21_NAN, -S21_INFINITY),
  // s21_pow(S21_NAN, -S21_INFINITY));
  ck_assert_float_eq(pow(S21_NAN, 0), s21_pow(S21_NAN, 0));

  ck_assert_double_nan(s21_pow(S21_INFINITY, S21_NAN));
  ck_assert_double_nan(s21_pow(S21_NAN, S21_NAN));
  ck_assert_double_nan(s21_pow(-S21_INFINITY, S21_NAN));
  ck_assert_double_nan(s21_pow(S21_NAN, S21_INFINITY));
  ck_assert_double_nan(s21_pow(S21_NAN, -S21_INFINITY));
  ck_assert_double_nan(s21_pow(S21_NAN, 1));
  ck_assert_double_nan(s21_pow(S21_NAN, -1));
}
END_TEST

Suite *suite_insert(void) {
  Suite *s = suite_create("suite_insert");
  TCase *tc = tcase_create("insert_tc");

  tcase_add_test(tc, abs1);
  tcase_add_test(tc, fabs1);
  tcase_add_test(tc, floor1);
  tcase_add_test(tc, ceil1);
  tcase_add_test(tc, exp1);
  tcase_add_test(tc, log1);
  tcase_add_test(tc, sqrt1);
  tcase_add_test(tc, sin1);
  tcase_add_test(tc, asin1);
  tcase_add_test(tc, cos1);
  tcase_add_test(tc, acos1);
  tcase_add_test(tc, tan1);
  tcase_add_test(tc, atan1);
  tcase_add_test(tc, fmod1);
  tcase_add_test(tc, pow1);

  suite_add_tcase(s, tc);
  return s;
}

int main(void) {
  int fail;
  Suite *s;
  SRunner *sr;
  s = suite_insert();
  sr = srunner_create(s);
  fail = srunner_ntests_failed(sr);

  srunner_run_all(sr, CK_VERBOSE);
  // srunner_run_all(sr, CK_NORMAL);
  // srunner_run_all(sr, CK_ENV);

  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_free(sr);
  return fail == 0 ? 0 : 1;
}
