#include "unit.h"

START_TEST(calc) {
  ck_assert_double_eq(isParsing("2^(3+3)^2", 0), 68719476736);
  ck_assert_double_eq(isParsing("2+2*2^3", 0), 18);
  ck_assert_double_eq(isParsing("1-3*-1+2/-2^3", 0), 3.75);
  ck_assert_double_eq(isParsing("1+2*(3+4/2-1)", 0), 9);
  ck_assert_float_eq(isParsing("6-2*3+(-5-2)", 0), -7);
  ck_assert_double_eq(isParsing("1+2*(3+4/2-(1+2))*2+1", 0), 10);
  ck_assert_float_eq(isParsing("2+2*-2-(4/7)", 0), -2.571428571);
  ck_assert_float_eq(isParsing("2+2*-2-(4/7)+10*2/2-(55+-25)-(33+17)", 0),
                     -72.571428571);
  ck_assert_double_eq(isParsing("2+2*2+-2555", 0), -2549);
  ck_assert_double_eq(isParsing("1+2*(3+4/2-(1+2))*2+1*-1", 0), 8);
  ck_assert_float_eq(isParsing("15/(7-(1+1))*3-(2+(1+1))*15/(7-(200+1))", 0),
                     9.309278351);
  ck_assert_double_eq(isParsing("2+(2)*2^(3)", 0), 18);
  ck_assert_float_eq(isParsing("(5.43/4.0)^3*(+4)*(5/3)^4-5/2^4*(--4)*4", 0),
                     72.210169271);
  ck_assert_float_eq(
      isParsing("(5.43/4.023)^3*(5/3)^4-5/2^4.432*(-4)*4.5435", 0),
      23.183109259);
  ck_assert_float_eq(isParsing("1*10^-5", 0), 0.00001);
  ck_assert_float_eq(
      isParsing("1111111111111111111111111111111111111111111+1", 0),
      1.1111111111111111e+42);
  ck_assert_float_eq(
      isParsing("1111111111111111111111111+1111111111111111111111111", 0),
      2.2222222222222222e+24);
}
START_TEST(calc_unar) {
  ck_assert_double_eq(isParsing("2^(-3+3)^2", 0), 1);
  ck_assert_double_eq(isParsing("2^(-3+-3)^2", 0), 68719476736);
  ck_assert_double_eq(isParsing("2^(-3-+3)^2", 0), 68719476736);
  ck_assert_double_eq(isParsing("2^(+3+3)^2", 0), 68719476736);
  ck_assert_double_eq(isParsing("2+2*+2^3", 0), 18);
  ck_assert_double_eq(isParsing("1-3*-1+2/-2^+3", 0), 3.75);
  ck_assert_double_eq(isParsing("+1+2*(3+4/2-1)", 0), 9);
  ck_assert_float_eq(isParsing("5-4*(-4+2)", 0), 13);
  ck_assert_float_eq(isParsing("4*(+6+2)", 0), 32);
  ck_assert_float_eq(isParsing("4*(--4)*4", 0), 64);
}
START_TEST(calc_mod) {
  ck_assert_float_eq(isParsing("5mod4", 0), 1);
  ck_assert_float_eq(isParsing("-5mod4", 0), 3);
  ck_assert_float_eq(isParsing("5mod-4", 0), -3);
  ck_assert_float_eq(isParsing("-5mod-4", 0), -1);
  ck_assert_float_eq(isParsing("545+63-1*5+(-5mod2)", 0), 604);
  ck_assert_float_eq(isParsing("545+63-1*5+(5mod-2)", 0), 602);
  ck_assert_float_eq(isParsing("545+63-1*5+(5mod2)", 0), 604);
  ck_assert_float_eq(isParsing("545+63-1*5+(-5mod-2)", 0), 602);
  ck_assert_float_eq(isParsing("(-5mod-2)*2^(3+3)^2", 0), -68719476736);
  ck_assert_float_eq(isParsing("(-5mod-2)*4^2+2-4^(2-2)", 0), -15);
  ck_assert_float_eq(isParsing("(+5mod-2)*4^2+2-4^(2-2)", 0), -15);
  ck_assert_float_eq(isParsing("(--5mod-2)*4^2+2-4^(2-2)", 0), -15);
  ck_assert_float_eq(isParsing("(+5mod--2)*4^2+2-4^(2-2)", 0), 17);
}
START_TEST(calc_func) {
  ck_assert_float_eq(isParsing("-(4.01^-tan(81))", 0), -3.08422972265);
  ck_assert_float_eq(isParsing("545+63-1*tan(5)-sin(5+-4^2/2)-3/cos(2-1)", 0),
                     605.407900816);
  ck_assert_float_eq(isParsing("-(3*(6000-(223.12/(2^(1+sqrt(16))))))", 0),
                     -17979.0825);
  ck_assert_float_eq(isParsing("(3*(6000-(223.12/(2^(1+sqrt(16))))))", 0),
                     17979.0825);
  ck_assert_float_eq(isParsing("-1+cos(1)^-sqrt(1)/2.032", 0), -0.08916549326);
  ck_assert_float_eq(isParsing("2+(1+2)^-2", 0), 2.11111111111);
  ck_assert_float_eq(isParsing("(55+66^8)/(5mod4)", 0), 3.6004061e+14);
  ck_assert_float_eq(isParsing("(55+66^8)/5mod4", 0), 2.203125);
  ck_assert_float_eq(isParsing("(55+66^8)/(55/(5mod4))", 0), 6.5461928e+12);
  ck_assert_float_eq(isParsing("5^2mod7", 0), 4);
  ck_assert_float_eq(isParsing("5^(2mod7)", 0), 25);
}

Suite *suite_parsing() {
  Suite *s = suite_create("parsing_calc");
  TCase *tc = tcase_create("tests");
  suite_add_tcase(s, tc);

  tcase_add_test(tc, calc);
  tcase_add_test(tc, calc_unar);
  tcase_add_test(tc, calc_mod);
  tcase_add_test(tc, calc_func);

  return s;
}
