#include "s21_math.h"
#include <check.h>

#define BUFF_SIZE 1024

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
} END_TEST


Suite *s21_math_tests_create() {
  Suite *s21_math = suite_create("s21_math");
  TCase *s21_math_tests = tcase_create("S21_MATH");
  tcase_add_test(s21_math_tests, ceil_test);
  tcase_add_test(s21_math_tests, floor_test);
  tcase_add_test(s21_math_tests, exp_test);
  tcase_add_test(s21_math_tests, sin_test);
  tcase_add_test(s21_math_tests, cos_test);
  tcase_add_test(s21_math_tests, tan_test);
  tcase_add_test(s21_math_tests, abs_test);
  tcase_add_test(s21_math_tests, fabs_test);
  tcase_add_test(s21_math_tests, fmod_test);
  tcase_add_test(s21_math_tests, pow_test);
  tcase_add_test(s21_math_tests, sqrt_test);
  tcase_add_test(s21_math_tests, log_test);
  tcase_add_test(s21_math_tests, asin_test);
  tcase_add_test(s21_math_tests, acos_test);
  tcase_add_test(s21_math_tests, atan_test);
  suite_add_tcase(s21_math, s21_math_test);
  return s21_math;
}

int main() {
  Suite *s21_math = s21_math_tests_create();
  SRunner *s21_math_runner = srunner_create(s21_math);
  int number_failed;
  srunner_run_all(s21_math_runner, CK_VERBOSE);
  number_failed = srunner_ntests_failed(s21_math_runner);
  srunner_free(s21_math_runner);

  return number_failed == 0 ? 0 : 1;
}
