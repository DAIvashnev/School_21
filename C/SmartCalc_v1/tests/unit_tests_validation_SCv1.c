#include "unit.h"

START_TEST(validation_sum_sub) {
  ck_assert_int_eq(isValidation("5--4"), 1);
  ck_assert_int_eq(isValidation("1+9-5+3"), 1);
  ck_assert_int_eq(isValidation("+1+9-5+3"), 1);
  ck_assert_int_eq(isValidation("-1+9-5+3"), 1);
  ck_assert_int_eq(isValidation("--1+9-5+3"), 1);
  ck_assert_int_eq(isValidation("5++4"), 0);
  ck_assert_int_eq(isValidation("1+9-5+3-"), 0);
  ck_assert_int_eq(isValidation("1+9-5+3+"), 0);
  ck_assert_int_eq(isValidation("1+++9-5+3"), 0);
  ck_assert_int_eq(isValidation("1+9---5+3"), 0);
  ck_assert_int_eq(isValidation("++1+9-5+3"), 0);
}

START_TEST(validation_point) {
  ck_assert_int_eq(isValidation("1+9.5-5+3"), 1);
  ck_assert_int_eq(isValidation("1+9.-5+3"), 0);
  ck_assert_int_eq(isValidation("1+9..5-5+3"), 0);
  ck_assert_int_eq(isValidation("1+9.5-5+3."), 0);
  ck_assert_int_eq(isValidation(".1+9.5-5+3"), 0);
  ck_assert_int_eq(isValidation("..1+9.5-5+3"), 0);
  ck_assert_int_eq(isValidation("1+9.5-5+3.."), 0);
  ck_assert_int_eq(isValidation("1+9...5-5+3"), 0);
  ck_assert_int_eq(isValidation("1+9.5543.432-5+3"), 0);
  ck_assert_int_eq(isValidation("1+9.5543432-5+.3"), 0);
}

START_TEST(validation_bracket) {
  ck_assert_int_eq(isValidation("1+(1)^2"), 1);
  ck_assert_int_eq(isValidation("(1+(9.5-5)+(-3))"), 1);
  ck_assert_int_eq(isValidation("(1+(9.5-5)+(--3))"), 1);
  ck_assert_int_eq(isValidation("((1+(9.5)))-(((5+3)))"), 1);
  ck_assert_int_eq(isValidation("()5+6"), 0);
  ck_assert_int_eq(isValidation("5+6()"), 0);
  ck_assert_int_eq(isValidation("5+6-)(5"), 0);
  ck_assert_int_eq(isValidation("()1+9-5+3"), 0);
  ck_assert_int_eq(isValidation(")1+9.5-5+3"), 0);
  ck_assert_int_eq(isValidation("(1+9.5-5+3"), 0);
  ck_assert_int_eq(isValidation("1+9.5-5+3("), 0);
  ck_assert_int_eq(isValidation("1+9.5-5+3)"), 0);
  ck_assert_int_eq(isValidation("(1+(9(.5)-5)+(-3))"), 0);
}

START_TEST(validation_un) {
  ck_assert_int_eq(isValidation("-5"), 1);
  ck_assert_int_eq(isValidation("5+(-1)"), 1);
  ck_assert_int_eq(isValidation("--5+2"), 1);
  ck_assert_int_eq(isValidation("-5-(-4)"), 1);
  ck_assert_int_eq(isValidation("+5+(+3)"), 1);
  ck_assert_int_eq(isValidation("5-"), 0);
  ck_assert_int_eq(isValidation("5+"), 0);
  ck_assert_int_eq(isValidation("++5"), 0);
  ck_assert_int_eq(isValidation("-5(+3)"), 0);
  ck_assert_int_eq(isValidation("-5-(-)"), 0);
}

START_TEST(validation_pow) {
  ck_assert_int_eq(isValidation("5^4"), 1);
  ck_assert_int_eq(isValidation("5^4+5-3^4"), 1);
  ck_assert_int_eq(isValidation("5^4+5^(4-4)"), 1);
  ck_assert_int_eq(isValidation("(5^4)^2+2+4^2-2"), 1);
  ck_assert_int_eq(isValidation("(5^(+4))^2+2+4^2-2"), 1);
  ck_assert_int_eq(isValidation("5^^4"), 0);
  ck_assert_int_eq(isValidation("5^+5-3^4"), 0);
  ck_assert_int_eq(isValidation("^5^4+5-3^4"), 0);
  ck_assert_int_eq(isValidation("(5^4)^2+2+4^2-2^"), 0);
  ck_assert_int_eq(isValidation("(5^(4)^2+2+4^2-2"), 0);
  ck_assert_int_eq(isValidation("(5^4)+(^2+2)+4^2-2"), 0);
}

START_TEST(validation_mult) {
  ck_assert_int_eq(isValidation("5*4"), 1);
  ck_assert_int_eq(isValidation("5*+4"), 1);
  ck_assert_int_eq(isValidation("5*-4"), 1);
  ck_assert_int_eq(isValidation("5*--4"), 1);
  ck_assert_int_eq(isValidation("5*-(-4)"), 1);
  ck_assert_int_eq(isValidation("5*-(--4)"), 1);
  ck_assert_int_eq(isValidation("5*4+5*3^4"), 1);
  ck_assert_int_eq(isValidation("(5*4)*(5*3)^4"), 1);
  ck_assert_int_eq(isValidation("(5*4)^3*(5*3)^4"), 1);
  ck_assert_int_eq(isValidation("*5*4"), 0);
  ck_assert_int_eq(isValidation("5*4*"), 0);
  ck_assert_int_eq(isValidation("5*++4"), 0);
  ck_assert_int_eq(isValidation("5*---4"), 0);
  ck_assert_int_eq(isValidation("5+*(+4)"), 0);
  ck_assert_int_eq(isValidation("5*+(+4)"), 0);
  ck_assert_int_eq(isValidation("5+*+(+4)"), 0);
  ck_assert_int_eq(isValidation("(5*4)^3*(5*3*)^4"), 0);
}

START_TEST(validation_div) {
  ck_assert_int_eq(isValidation("5/4"), 1);
  ck_assert_int_eq(isValidation("5/+4"), 1);
  ck_assert_int_eq(isValidation("5/-4"), 1);
  ck_assert_int_eq(isValidation("5/--4"), 1);
  ck_assert_int_eq(isValidation("5/-(-4)"), 1);
  ck_assert_int_eq(isValidation("5/-(--4)"), 1);
  ck_assert_int_eq(isValidation("5/4+5/3^4"), 1);
  ck_assert_int_eq(isValidation("(5/4)/(5/3)^4"), 1);
  ck_assert_int_eq(isValidation("(5/4)^3/(5/3)^4"), 1);
  ck_assert_int_eq(isValidation("5/0"), 0);
  ck_assert_int_eq(isValidation("5//5"), 0);
  ck_assert_int_eq(isValidation("/5/4"), 0);
  ck_assert_int_eq(isValidation("5/4/"), 0);
  ck_assert_int_eq(isValidation("5/++4"), 0);
  ck_assert_int_eq(isValidation("5/---4"), 0);
  ck_assert_int_eq(isValidation("5+/(+4)"), 0);
  ck_assert_int_eq(isValidation("5/+(+4)"), 0);
  ck_assert_int_eq(isValidation("5+/+(+4)"), 0);
  ck_assert_int_eq(isValidation("(5/4)^3/(5/0)^4"), 0);
  ck_assert_int_eq(isValidation("(5/4)^3/(5/3/)^4"), 0);
}

START_TEST(validation_set) {
  ck_assert_int_eq(isValidation("(5.43/4.0)^3*(5/3)^4-5/2^4*(--4)*4"), 1);
  ck_assert_int_eq(isValidation("(5.43/4.0)^3*(+4)*(5/3)^4-5/2^4*(--4)*4"), 1);
  ck_assert_int_eq(isValidation("(5.43/4.0)^3*(5/3)^4-5./2^4*(--4)*4.5"), 0);
  ck_assert_int_eq(isValidation("(5.43/4.0)^3*(5/3)^4-5/2^4*(--4)*4.5/0"), 0);
}

START_TEST(validation_mod) {
  ck_assert_int_eq(isValidation("5mod4"), 1);
  ck_assert_int_eq(isValidation("5mod4*4"), 1);
  ck_assert_int_eq(isValidation("100mod4*4+2^2/4mod2"), 1);
  ck_assert_int_eq(isValidation("mod"), 0);
  ck_assert_int_eq(isValidation("5mod"), 0);
  ck_assert_int_eq(isValidation("mod4"), 0);
  ck_assert_int_eq(isValidation("*mod4"), 0);
  ck_assert_int_eq(isValidation("+mod4"), 0);
  ck_assert_int_eq(isValidation("5mod4(4)"), 0);
  ck_assert_int_eq(isValidation("5^2(mod7)"), 0);
  ck_assert_int_eq(isValidation("5mod4(4+5)"), 0);
  ck_assert_int_eq(isValidation("55+66^8)/(5mod4)"), 0);
}

START_TEST(validation_func) {
  ck_assert_int_eq(isValidation("tan(4)/atan(4)+cos(4)"), 1);
  ck_assert_int_eq(isValidation("tan(4/atan(4))+cos(4)"), 1);
  ck_assert_int_eq(
      isValidation("5mod4*5+(sin(4)/sqrt(3))+sin(4)*(atan(4)+4*cos(4))"), 1);
  ck_assert_int_eq(isValidation("tan4/atan(4)+4cos4"), 0);
  ck_assert_int_eq(isValidation("sin(4+4^2-(2+4)^2)/sqrt3+sin4"), 0);
  ck_assert_int_eq(isValidation("5mod4*5sin4/sqrt3+sin4*tan/atan4+4cos4"), 0);
  ck_assert_int_eq(isValidation("5mod4*5sin4/sqrt3+sin4*tan4/atan4+4cos4"), 0);
  ck_assert_int_eq(isValidation("5cos(x)"), 0);
}

START_TEST(validation_x) {
  ck_assert_int_eq(isValidation("3^x"), 1);
  ck_assert_int_eq(isValidation("3/x"), 1);
  ck_assert_int_eq(isValidation("3+x"), 1);
  ck_assert_int_eq(isValidation("x+(-1)"), 1);
  ck_assert_int_eq(isValidation("x+(x)^x"), 1);
  ck_assert_int_eq(isValidation("5^-sqrt(10)"), 1);
  ck_assert_int_eq(isValidation("5-x*x+2-tan(4)/atan(x)+cos(4)+x/2"), 1);
  ck_assert_int_eq(isValidation("xx*6"), 0);
  ck_assert_int_eq(isValidation("5-x*x+2-tan4/atan(x)+4cos4+x/2"), 0);
  ck_assert_int_eq(isValidation("5mod5*5sinx/sqrt3+sinx*tan4/atan4+4cos4"), 0);
}

Suite *suite_validation() {
  Suite *s = suite_create("valid_calc");
  TCase *tc = tcase_create("tests");
  suite_add_tcase(s, tc);

  tcase_add_test(tc, validation_sum_sub);
  tcase_add_test(tc, validation_point);
  tcase_add_test(tc, validation_bracket);
  tcase_add_test(tc, validation_un);
  tcase_add_test(tc, validation_pow);
  tcase_add_test(tc, validation_mult);
  tcase_add_test(tc, validation_div);
  tcase_add_test(tc, validation_set);
  tcase_add_test(tc, validation_mod);
  tcase_add_test(tc, validation_func);
  tcase_add_test(tc, validation_x);

  return s;
}
