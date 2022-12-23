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


Suite *suite_insert(void) {
    Suite *s = suite_create("suite_insert");
    TCase *tc = tcase_create("insert_tc");

    // 12
    tcase_add_test(tc, pow_test);

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

  //srunner_run_all(sr, CK_VERBOSE);
  srunner_run_all(sr, CK_NORMAL);

  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_free(sr);
  return fail == 0 ? 0 : 1;
}
