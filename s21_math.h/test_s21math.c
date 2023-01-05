#include "s21_math.h"

#include <check.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFF_SIZE 1024

// 1 - int s21_abs(int x);
START_TEST(abs_test) {
  ck_assert_int_eq(abs(13), s21_abs(13));
  ck_assert_int_eq(abs(-13), s21_abs(-13));
  ck_assert_int_eq(abs(-645345), s21_abs(-645345));
  ck_assert_int_eq(abs(645345), s21_abs(645345));
}
END_TEST

// 2 - long double s21_acos(double x);
START_TEST(acos_test) {
  ck_assert_int_eq(acos(-13.54), s21_acos(-13.54));
  ck_assert_int_eq(acos(13.54), s21_acos(13.54));
  ck_assert_int_eq(acos(2.2343), s21_acos(2.2343));
  ck_assert_float_eq(acos(0.1234), s21_acos(0.1234));
  ck_assert_float_eq(acos(0), s21_acos(0));
  ck_assert_float_eq(acos(1), s21_acos(1));
  ck_assert_float_eq(acos(-1), s21_acos(-1));
  ck_assert_float_eq(acos(0.5), s21_acos(0.5));
  ck_assert_float_eq(acos(-0.5), s21_acos(-0.5));
}
END_TEST

// 3 - long double s21_asin(double x);
START_TEST(asin_test) {
  ck_assert_int_eq(asin(-13.54), s21_asin(-13.54));
  ck_assert_int_eq(asin(13.54), s21_asin(13.54));
  ck_assert_int_eq(asin(6.28), s21_asin(6.28));
  ck_assert_float_eq(asin(s21_E), s21_asin(s21_E));
  ck_assert_float_eq(asin(0.1234), s21_asin(0.1234));
  ck_assert_float_eq(asin(0), s21_asin(0));
  ck_assert_float_eq(asin(1), s21_asin(1));
  ck_assert_float_eq(asin(-1), s21_asin(-1));
  ck_assert_float_eq(asin(0.5), s21_asin(0.5));
  ck_assert_float_eq(asin(-0.5), s21_asin(-0.5));
}
END_TEST

// 4 - long double s21_atan(double x);
START_TEST(atan_test) {
  ck_assert_int_eq(atan(-13.54), s21_atan(-13.54));
  ck_assert_float_eq(atan(13.54), s21_atan(13.54));
  ck_assert_float_eq(atan(3.14), s21_atan(3.14));
  ck_assert_float_eq(atan(6.28), s21_atan(6.28));
  ck_assert_float_eq(atan(2.2343), s21_atan(2.2343));
  ck_assert_float_eq(atan(0.1234), s21_atan(0.1234));
  ck_assert_float_eq(atan(0), s21_atan(0));
  ck_assert_float_eq(atan(1), s21_atan(1));
  ck_assert_float_eq(atan(-1), s21_atan(-1));
  ck_assert_float_eq(atan(3.5), s21_atan(3.5));
  ck_assert_float_eq(atan(-3.5), s21_atan(-3.5));
}
END_TEST

// 5 - long double s21_cos(double x);
START_TEST(cos_test) {
  ck_assert_float_eq(cos(-13.54), s21_cos(-13.54));
  ck_assert_float_eq(cos(13.54), s21_cos(13.54));
  ck_assert_float_eq(cos(0.0), s21_cos(0.0));
  ck_assert_float_eq(cos(1.0), s21_cos(1.0));
  ck_assert_float_eq(cos(3.14), s21_cos(3.14));
  ck_assert_float_eq(cos(6.28), s21_cos(6.28));
  ck_assert_float_eq(cos(2.2343), s21_cos(2.2343));
  ck_assert_float_eq(cos(0.1234), s21_cos(0.1234));
}
END_TEST

// 6 - long double s21_ceil(double a);
START_TEST(ceil_test) {
  ck_assert_ldouble_eq(ceil(13), s21_ceil(13));
  ck_assert_ldouble_eq(ceil(-13), s21_ceil(-13));
  ck_assert_ldouble_eq(ceil(1000.000001), s21_ceil(1000.000001));
  ck_assert_ldouble_eq(ceil(-1000.000001), s21_ceil(-1000.000001));
  ck_assert_ldouble_eq(ceil(-1000.000001), s21_ceil(-1000.000001));
  ck_assert_ldouble_eq(ceil(-0.5), s21_ceil(-0.5));
}
END_TEST

// 7 - long double s21_exp(double a);
START_TEST(exp_test) {
  ck_assert_float_eq(exp(-13.54), s21_exp(-13.54));
  ck_assert_float_eq(exp(13.54), s21_exp(13.54));
  ck_assert_float_eq(exp(-0.54), s21_exp(-0.54));
  ck_assert_float_eq(exp(1000), s21_exp(1000));
  ck_assert_float_eq(exp(1), s21_exp(1));
  ck_assert_float_eq(exp(2), s21_exp(2));
  ck_assert_double_eq(exp(100), s21_exp(100));
  ck_assert_float_eq(exp(-1), s21_exp(-1));
  ck_assert_float_eq(exp(0), s21_exp(0));
  ck_assert_int_eq(exp(s21_NAN), s21_exp(s21_NAN));
  ck_assert_float_eq(exp(710), s21_exp(710));
  ck_assert_float_eq(exp(1.2345), s21_exp(1.2345));
  ck_assert_float_eq(exp(1.23454656768), s21_exp(1.23454656768));
}
END_TEST

// 8 - long double s21_fabs(double x);
START_TEST(fabs_test) {
  ck_assert_int_eq(fabs(13.0), s21_fabs(13.0));
  ck_assert_int_eq(fabs(-13.0), s21_fabs(-13.0));
  ck_assert_ldouble_eq(fabs(1000.000001), s21_fabs(1000.000001));
  ck_assert_ldouble_eq(fabs(-1000.000001), s21_fabs(-1000.000001));
  ck_assert_ldouble_eq(fabs(-1000.000001), s21_fabs(-1000.000001));
  ck_assert_ldouble_eq(fabs(-0.5), s21_fabs(-0.5));
  ck_assert_int_eq(fabs(0.0), s21_fabs(0.0));
}
END_TEST

// 9 - long double s21_floor(double x);
START_TEST(floor_test) {
  ck_assert_ldouble_eq(floor(13), s21_floor(13));
  ck_assert_ldouble_eq(floor(-13), s21_floor(-13));
  ck_assert_ldouble_eq(floor(1000.000001), s21_floor(1000.000001));
  ck_assert_ldouble_eq(floor(-1000.000001), s21_floor(-1000.000001));
  ck_assert_ldouble_eq(floor(-1000.000001), s21_floor(-1000.000001));
  ck_assert_ldouble_eq(floor(-0.5), s21_floor(-0.5));
}
END_TEST

// 10 - long double s21_fmod(double x, double y);
START_TEST(fmod_test) {
  ck_assert_ldouble_eq(fmod(-13.21313, 2.5), s21_fmod(-13.21313, 2.5));
  ck_assert_ldouble_eq(fmod(13.21313, 2.5), s21_fmod(13.21313, 2.5));
  ck_assert_ldouble_eq(fmod(-1000.21313, 2.5), s21_fmod(-1000.21313, 2.5));
  ck_assert_ldouble_eq(fmod(32346234.21313, 2.5),
                       s21_fmod(32346234.21313, 2.5));
  ck_assert_ldouble_eq(fmod(0, 2.5), s21_fmod(0, 2.5));
  ck_assert_ldouble_eq(fmod(2.5, 2.5), s21_fmod(2.5, 2.5));
}
END_TEST

// 11 - long double s21_log(double a);
START_TEST(log_test) {
  ck_assert_int_eq(log(-13.54), s21_log(-13.54));
  ck_assert_float_eq(log(13.54), s21_log(13.54));
  ck_assert_float_eq(log(0.0), s21_log(0.0));
  ck_assert_int_eq(log(1.0), s21_log(1.0));
  ck_assert_float_eq(log(3.14), s21_log(3.14));
  ck_assert_float_eq(log(6.28), s21_log(6.28));
  ck_assert_float_eq(log(2.2343), s21_log(2.2343));
  ck_assert_float_eq(log(0.1234), s21_log(0.1234));
}
END_TEST

// 12 - long double s21_pow(double base, double exp);
START_TEST(pow_test) {
  ck_assert_int_eq(pow(13, 2), s21_pow(13, 2));
  ck_assert_int_eq(pow(-13, 2.5), s21_pow(-13, 2.5));
  ck_assert_int_eq(pow(13, 2.5), s21_pow(13, 2.5));
  ck_assert_int_eq(pow(-13.21313, 2.5), s21_pow(-13.21313, 2.5));
  ck_assert_float_eq(pow(13.21313, 2.5), s21_pow(13.21313, 2.5));
  ck_assert_int_eq(pow(-1000.21313, 2.5), s21_pow(-1000.21313, 2.5));
  ck_assert_float_eq(pow(0, 2.5), s21_pow(0, 2.5));
  ck_assert_float_eq(pow(123, -2), s21_pow(123, -2));
  ck_assert_float_eq(pow(123, 0), s21_pow(123, 0));
}
END_TEST

// 13 - long double s21_sin(double a);
START_TEST(sin_test) {
  ck_assert_float_eq(sin(-13.54), s21_sin(-13.54));
  ck_assert_float_eq(sin(13.54), s21_sin(13.54));
  ck_assert_float_eq(sin(0.0), s21_sin(0.0));
  ck_assert_float_eq(sin(1.0), s21_sin(1.0));
  ck_assert_float_eq(sin(3.14), s21_sin(3.14));
  ck_assert_float_eq(sin(6.28), s21_sin(6.28));
  ck_assert_float_eq(sin(2.2343), s21_sin(2.2343));
  ck_assert_float_eq(sin(-1234), s21_sin(-1234));
}
END_TEST

// 14 - long double s21_sqrt(double a);
START_TEST(sqrt_test) {
  ck_assert_float_eq(sqrt(0.0), s21_sqrt(0.0));
  ck_assert_float_eq(sqrt(1.0), s21_sqrt(1.0));
  ck_assert_float_eq(sqrt(3.14), s21_sqrt(3.14));
  ck_assert_float_eq(sqrt(6.28), s21_sqrt(6.28));
  ck_assert_float_eq(sqrt(2.2343), s21_sqrt(2.2343));
  ck_assert_int_eq(sqrt(-123), s21_sqrt(-123));
}
END_TEST

// 15 - long double s21_tan(double x);
START_TEST(tan_test) {
  ck_assert_float_eq(tan(-13.54), s21_tan(-13.54));
  ck_assert_float_eq(tan(13.54), s21_tan(13.54));
  ck_assert_float_eq(tan(0), s21_tan(0));
  ck_assert_float_eq(tan(1), s21_tan(1));
  ck_assert_float_eq(tan(3.14), s21_tan(3.14));
  ck_assert_float_eq(tan(6.28), s21_tan(6.28));
  ck_assert_float_eq(tan(2.2343), s21_tan(2.2343));
  ck_assert_float_eq(tan(0.1234), s21_tan(0.1234));
}
END_TEST

Suite *suite_insert(void) {
  Suite *s = suite_create("suite_insert");
  TCase *tc = tcase_create("insert_tc");

  tcase_add_test(tc, abs_test);
  tcase_add_test(tc, acos_test);
  tcase_add_test(tc, asin_test);
  tcase_add_test(tc, atan_test);
  tcase_add_test(tc, ceil_test);
  tcase_add_test(tc, cos_test);
  tcase_add_test(tc, exp_test);
  tcase_add_test(tc, fabs_test);
  tcase_add_test(tc, floor_test);
  tcase_add_test(tc, fmod_test);
  tcase_add_test(tc, log_test);
  tcase_add_test(tc, pow_test);
  tcase_add_test(tc, sin_test);
  tcase_add_test(tc, sqrt_test);
  tcase_add_test(tc, tan_test);

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

  // srunner_run_all(sr, CK_VERBOSE);
  srunner_run_all(sr, CK_NORMAL);

  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_free(sr);
  return fail == 0 ? 0 : 1;
}