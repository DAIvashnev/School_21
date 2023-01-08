#include "unit.h"
#define BUFF_SIZE 1024

// %[флаги][ширина][.точность][длина]спецификатор

// -s
START_TEST(sscanf1) {
  char s1[BUFF_SIZE] = {'\0'};
  char s2[BUFF_SIZE] = {'\0'};
  char s3[BUFF_SIZE] = {'\0'};
  char s4[BUFF_SIZE] = {'\0'};
  char s5[BUFF_SIZE] = {'\0'};
  char s6[BUFF_SIZE] = {'\0'};
  char s7[BUFF_SIZE] = {'\0'};
  char s8[BUFF_SIZE] = {'\0'};

  const char str[1096] = "Hello, mom\t I 森我爱";
  const char format[] = "%s%s%s%s";

  int16_t res1 = s21_sscanf(str, format, s1, s2, s3, s4);
  int16_t res2 = sscanf(str, format, s5, s6, s7, s8);

  ck_assert_int_eq(res1, res2);
}
END_TEST

// strings_mixed1
START_TEST(sscanf2) {
    unsigned long long int a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0;
    long long d1 = 0, d2 = 0;
    long double e1 = 0, e2 = 0;

    const char str[1096] = "4444444"
                       "eeeeeee\teeeeeee";
    const char fstr[1096] = "%5s %1s %*s %*s %llu %s %llu %llu %lld %Lf %33s";

    char s1[BUFF_SIZE] = {'\0'};
    char s2[BUFF_SIZE] = {'\0'};
    char s3[BUFF_SIZE] = {'\0'};
    char s4[BUFF_SIZE] = {'\0'};
    char s5[BUFF_SIZE] = {'\0'};
    char s6[BUFF_SIZE] = {'\0'};
    char s7[BUFF_SIZE] = {'\0'};
    char s8[BUFF_SIZE] = {'\0'};
    char s9[BUFF_SIZE] = {'\0'};
    char s10[BUFF_SIZE] = {'\0'};

    int16_t res1 =
        s21_sscanf(str, fstr, s7, s9, &a1, s5, &b1, &c1, &d1, &e1, s1);
    int16_t res2 = sscanf(str, fstr, s8, s10, &a2, s6, &b2, &c2, &d2, &e2, s2);

    ck_assert_int_eq(res1, res2);
    ck_assert_str_eq(s1, s2);
    ck_assert_str_eq(s3, s4);
    ck_assert_str_eq(s5, s6);
    ck_assert_int_eq(a1, a2);
    ck_assert_int_eq(b1, b2);
    ck_assert_int_eq(c1, c2);
    ck_assert_int_eq(d1, d2);
} END_TEST

START_TEST(sscanf3) {
    int d1 = 0, d2 = 0, b1 = 0, b2 = 0, a1 = 0, a2 = 0;
    long long v1, v2;

    const char str[1096] = "1 1 1 1 1 -1";
    const char fstr[1096] = "%1s %5d %1s %1s %d %lld %d";

    char s1[BUFF_SIZE] = {'\0'};
    char s2[BUFF_SIZE] = {'\0'};
    char s3[BUFF_SIZE] = {'\0'};
    char s4[BUFF_SIZE] = {'\0'};
    char s5[BUFF_SIZE] = {'\0'};
    char s6[BUFF_SIZE] = {'\0'};

    int16_t res1 = s21_sscanf(str, fstr, s1, &a1, s2, s3, &b1, &v1, &d1);
    int16_t res2 = sscanf(str, fstr, s4, &a2, s5, s6, &b2, &v2, &d2);

    ck_assert_int_eq(res1, res2);
    ck_assert_str_eq(s1, s2);
    ck_assert_str_eq(s3, s4);
    ck_assert_str_eq(s5, s6);
    ck_assert_int_eq(a1, a2);
    ck_assert_int_eq(b1, b2);
    ck_assert_int_eq(d1, d2);
} END_TEST


// =========== INT ===============
START_TEST(sscanf4) {
    long long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
    const char str[1096] = "1337 21 5008 300004";
    const char fstr[1096] = "%lld %lld %lld %lld";

    int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
    int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

    ck_assert_int_eq(res1, res2);
    ck_assert_int_eq(a1, a2);
    ck_assert_int_eq(b1, b2);
    ck_assert_int_eq(c1, c2);
    ck_assert_int_eq(d1, d2);
} END_TEST

START_TEST(sscanf5) {
    long long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
    const char str[1096] = "1337 21 5008 300004";
    const char fstr[1096] = "%1lld %3lld %1lld %4lld";

    int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
    int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

    ck_assert_int_eq(res1, res2);
    ck_assert_int_eq(a1, a2);
    ck_assert_int_eq(b1, b2);
    ck_assert_int_eq(c1, c2);
    ck_assert_int_eq(d1, d2);
} END_TEST

START_TEST(sscanf6) {
    long long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
    const char str[1096] = "1337";
    const char fstr[1096] = "%1lld %1lld %1lld %1lld";

    int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
    int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

    ck_assert_int_eq(res1, res2);
    ck_assert_int_eq(a1, a2);
    ck_assert_int_eq(b1, b2);
    ck_assert_int_eq(c1, c2);
    ck_assert_int_eq(d1, d2);
} END_TEST

START_TEST(sscanf7) {
    long long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
    const char str[1096] = "100000000000000005";
    const char fstr[1096] = "%3lld%lld%1lld%5lld";

    int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
    int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

    ck_assert_int_eq(res1, res2);
    ck_assert_int_eq(a1, a2);
    ck_assert_int_eq(b1, b2);
    ck_assert_int_eq(c1, c2);
    ck_assert_int_eq(d1, d2);
} END_TEST

START_TEST(sscanf8) {
    long long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
    const char str[1096] = "1337";
    const char fstr[1096] = "%15lld %1lld %1lld %1lld";

    int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
    int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

    ck_assert_int_eq(res1, res2);
    ck_assert_int_eq(a1, a2);
    ck_assert_int_eq(b1, b2);
    ck_assert_int_eq(c1, c2);
    ck_assert_int_eq(d1, d2);
} END_TEST

START_TEST(sscanf9) {
    long long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0;
    const char str[1096] = "1337123123 1 123412341234 1 999999 0";
    const char fstr[1096] = "%*d %lld %*d %lld %*d %lld";

    int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1);
    int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2);

    ck_assert_int_eq(res1, res2);
    ck_assert_int_eq(a1, a2);
    ck_assert_int_eq(b1, b2);
    ck_assert_int_eq(c1, c2);
} END_TEST

START_TEST(sscanf10) {
    long long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
    const char str[1096] = "1337";
    const char fstr[1096] = "%15lld %1lld %1lld %1lld";

    int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
    int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

    ck_assert_int_eq(res1, res2);
    ck_assert_int_eq(a1, a2);
    ck_assert_int_eq(b1, b2);
    ck_assert_int_eq(c1, c2);
    ck_assert_int_eq(d1, d2);
} END_TEST

START_TEST(sscanf11) {
    long long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
    const char str[1096] = "1337";
    const char fstr[1096] = "%15lld %1lld %1lld %1lld";

    int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
    int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

    ck_assert_int_eq(res1, res2);
    ck_assert_int_eq(a1, a2);
    ck_assert_int_eq(b1, b2);
    ck_assert_int_eq(c1, c2);
    ck_assert_int_eq(d1, d2);
} END_TEST

START_TEST(sscanf12) {
    long long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
    const char str[1096] = "1337";
    const char fstr[1096] = "%15lld %1lld %1lld %1lld";

    int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
    int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

    ck_assert_int_eq(res1, res2);
    ck_assert_int_eq(a1, a2);
    ck_assert_int_eq(b1, b2);
    ck_assert_int_eq(c1, c2);
    ck_assert_int_eq(d1, d2);
} END_TEST

START_TEST(sscanf13) {
    long long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
    const char str[1096] = "11337 ++3 -5 ------4";
    const char fstr[1096] = "%lld %lld %lld %lld";

    int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
    int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

    ck_assert_int_eq(res1, res2);
    ck_assert_int_eq(a1, a2);
    ck_assert_int_eq(b1, b2);
    ck_assert_int_eq(c1, c2);
    ck_assert_int_eq(d1, d2);
} END_TEST

START_TEST(sscanf14) {
    long long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
    const char str[1096] = "-1337 +1 -1 -1";
    const char fstr[1096] = "%15lld %1lld %1lld %5lld";

    int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
    int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

    ck_assert_int_eq(res1, res2);
    ck_assert_int_eq(a1, a2);
    ck_assert_int_eq(b1, b2);
    ck_assert_int_eq(c1, c2);
    ck_assert_int_eq(d1, d2);
} END_TEST

START_TEST(sscanf15) {
    long long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
    const char str[1096] = "-0 +0 +0 -0";
    const char fstr[1096] = "%2lld %1lld %1lld %1lld";

    int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
    int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

    ck_assert_int_eq(res1, res2);
    ck_assert_int_eq(a1, a2);
    ck_assert_int_eq(b1, b2);
    ck_assert_int_eq(c1, c2);
    ck_assert_int_eq(d1, d2);
} END_TEST

START_TEST(sscanf16) {
    long long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
    const char str[1096] = "1 01 10 0";
    const char fstr[1096] = "%lld %lld %lld %lld";

    int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
    int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

    ck_assert_int_eq(res1, res2);
    ck_assert_int_eq(a1, a2);
    ck_assert_int_eq(b1, b2);
    ck_assert_int_eq(c1, c2);
    ck_assert_int_eq(d1, d2);
} END_TEST









// ================== FLOAT ===================

START_TEST(sscanf17) {
    double a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;

    const char str[1096] = "0.00001 -4123123 4. .";
    const char fstr[1096] = "%lf %lf %lf %lf";

    int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
    int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

    ck_assert_int_eq(res1, res2);
    ck_assert_double_eq(a1, a2);
    ck_assert_double_eq(b1, b2);
    ck_assert_double_eq(c1, c2);
    ck_assert_double_eq(d1, d2);
} END_TEST

START_TEST(sscanf18) {
    float a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;

    const char str[1096] = ". . . .";
    const char fstr[1096] = "%f %f %f %f";

    int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
    int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

    ck_assert_int_eq(res1, res2);
    ck_assert_double_eq(a1, a2);
    ck_assert_double_eq(b1, b2);
    ck_assert_double_eq(c1, c2);
    ck_assert_double_eq(d1, d2);
} END_TEST

START_TEST(sscanf19) {
    float a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;

    const char str[1096] = "1.4441 1.31e+4 -3.31e-4 0.444e-5";
    const char fstr[1096] = "%G %G %G %G";

    int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
    int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

    ck_assert_int_eq(res1, res2);
    ck_assert_double_eq(a1, a2);
    ck_assert_double_eq(b1, b2);
    ck_assert_double_eq(c1, c2);
    ck_assert_double_eq(d1, d2);
} END_TEST

START_TEST(sscanf20) {
    float a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;

    const char str[1096] = "inf 1.31e+4 NaN 0.444e-5";
    const char fstr[1096] = "%G %G %G %G";

    int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
    int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

    ck_assert_int_eq(res1, res2);
    ck_assert_ldouble_eq(a1, a2);
    // Unfortunately, assertions for inf do not work correctly in libcheck
    // ck_assert_ldouble_infinite(a1);
    // ck_assert_ldouble_infinite(a2);
    ck_assert_double_eq(b1, b2);
    ck_assert_float_nan(c1);
    ck_assert_float_nan(c2);
    ck_assert_double_eq(d1, d2);
} END_TEST

START_TEST(sscanf21) {
    float a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;

    const char str[1096] = "inF InF inF INF";
    const char fstr[1096] = "%G %G %G %G";

    int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
    int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

    ck_assert_int_eq(res1, res2);
    ck_assert_ldouble_eq(a1, a2);
    ck_assert_double_eq(b1, b2);
    ck_assert_double_eq(c1, c2);
    ck_assert_double_eq(d1, d2);
} END_TEST

START_TEST(sscanf22) {
    float a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;

    const char str[1096] = "Nan NAN 0.0000 0";
    const char fstr[1096] = "%G %G %G %G";

    int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
    int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

    ck_assert_int_eq(res1, res2);
    ck_assert_float_nan(a1);
    ck_assert_float_nan(a2);
    ck_assert_float_nan(b1);
    ck_assert_float_nan(b2);
    ck_assert_ldouble_eq(c1, c2);
    ck_assert_ldouble_eq(d1, d2);
} END_TEST

START_TEST(sscanf23) {
    float a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;

    const char str[1096] =
        "nAN           INF                   -0.1111         1e-10";
    const char fstr[1096] = "%G %G %G %G";

    int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
    int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

    ck_assert_int_eq(res1, res2);
    ck_assert_float_nan(a1);
    ck_assert_float_nan(a2);
    ck_assert_ldouble_eq(b1, b2);
    ck_assert_ldouble_eq(c1, c2);
    ck_assert_ldouble_eq(d1, d2);
} END_TEST

START_TEST(sscanf24) {
    int a1 = 0, a2 = 5, a3 = 3, a4 = 9;
    int32_t n1 = 500, n2 = 10000;

    const char str[1096] = "123123SkipMePlease!!!!123";
    const char fstr[1096] = "%dSkipMePlease!!!!%d %n";

    int16_t res1 = s21_sscanf(str, fstr, &a1, &a3, &n1);
    int16_t res2 = sscanf(str, fstr, &a2, &a4, &n2);

    ck_assert_int_eq(res1, res2);
    ck_assert_int_eq(n1, n2);
    ck_assert_int_eq(a3, a4);
    ck_assert_int_eq(n1, n2);
} END_TEST








// =======================================================
START_TEST(sscanf25) {
    int32_t a1, a2;
    int32_t b1 = 0, b2 = 0;
    const char str[1096] = "12keppa12";
    const char fstr[1096] = "%dkeppapos%d";
    int32_t res1 = s21_sscanf(str, fstr, &a1, &b1);
    int32_t res2 = sscanf(str, fstr, &a2, &b2);

    ck_assert_int_eq(res1, res2);
    ck_assert_int_eq(a1, a2);
    ck_assert_int_eq(b1, b2);
} END_TEST




START_TEST(sscanf_EOF1) {
    char fstr[1096] = "%d";
    char str[1096] = "        ";

    int16_t res1 = s21_sscanf(str, fstr, 0);
    int16_t res2 = sscanf(str, fstr, 100);
    ck_assert_int_eq(res1, res2);
} END_TEST

START_TEST(sscanf_EOF2) {
    char fstr[1096] = "%d ";
    char str[1096] = "               ";
    int16_t a1 = 0, a2 = 0;

    int16_t res1 = s21_sscanf(str, fstr, &a1);
    int16_t res2 = sscanf(str, fstr, &a2);
    ck_assert_int_eq(res1, res2);
} END_TEST

START_TEST(sscanf_EOF3) {
    char fstr[1096] = "%d ";
    char str[1096] = "  ";
    int16_t a1 = 0, a2 = 0;

    int16_t res1 = s21_sscanf(str, fstr, &a1);
    int16_t res2 = sscanf(str, fstr, &a2);
    ck_assert_int_eq(res1, res2);
} END_TEST

START_TEST(sscanf_only_chars1) {
    char fstr[1096] = "%c %c %c %c";
    char str[1096] = "   a     b c d";
    int16_t a1 = 0, a2 = 5, b1 = 0, b2 = 5, c1 = 0, c2 = 5, d1 = 0, d2 = 5;

    int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);

    int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

    ck_assert_int_eq(res1, res2);
    ck_assert_int_eq(a1, a2);
    ck_assert_int_eq(b1, b2);
    ck_assert_int_eq(c1, c2);
    ck_assert_int_eq(d1, d2);
} END_TEST

START_TEST(sscanf_only_chars2) {
    char fstr[1096] = "%c%c%c%c";
    char str[1096] = "abcd";
    int16_t a1 = 0, a2 = 5, b1 = 0, b2 = 5, c1 = 0, c2 = 5, d1 = 0, d2 = 5;

    int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);

    int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

    ck_assert_int_eq(res1, res2);
    ck_assert_int_eq(a1, a2);
    ck_assert_int_eq(b1, b2);
    ck_assert_int_eq(c1, c2);
    ck_assert_int_eq(d1, d2);
} END_TEST

START_TEST(sscanf_only_chars3) {
    char fstr[1096] = "%c %c %c      %c";
    char str[1096] = "1 a 3   c           ";
    int16_t a1 = 0, a2 = 5, b1 = 0, b2 = 5, c1 = 0, c2 = 5, d1 = 0, d2 = 5;

    int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
    int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

    ck_assert_int_eq(res1, res2);
    ck_assert_int_eq(a1, a2);
    ck_assert_int_eq(b1, b2);
    ck_assert_int_eq(c1, c2);
    ck_assert_int_eq(d1, d2);
} END_TEST

START_TEST(sscanf_only_chars4) {
    char fstr[1096] = "%c %c %c %c";
    char str[1096] = "   000 0    ";
    int16_t a1 = 0, a2 = 5, b1 = 0, b2 = 5, c1 = 0, c2 = 5, d1 = 0, d2 = 5;

    int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);

    int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

    ck_assert_int_eq(res1, res2);
    ck_assert_int_eq(a1, a2);
    ck_assert_int_eq(b1, b2);
    ck_assert_int_eq(c1, c2);
    ck_assert_int_eq(d1, d2);
} END_TEST

START_TEST(sscanf_only_chars5) {
    char fstr[1096] = "%c %c %c %c";
    char str[1096] = "tttt";
    int16_t a1 = 0, a2 = 5, b1 = 0, b2 = 5, c1 = 0, c2 = 5, d1 = 0, d2 = 5;

    int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);

    int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

    ck_assert_int_eq(res1, res2);
    ck_assert_int_eq(a1, a2);
    ck_assert_int_eq(b1, b2);
    ck_assert_int_eq(c1, c2);
    ck_assert_int_eq(d1, d2);
} END_TEST

START_TEST(sscanf_special_symbols_as_chars1) {
    char fstr[1096] = "%c%c%c%c";
    char str[1096] = "\\\n\t\t\t";
    int16_t a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;

    int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
    int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

    ck_assert_int_eq(res1, res2);
    ck_assert_int_eq(a1, a2);
    ck_assert_int_eq(b1, b2);
    ck_assert_int_eq(c1, c2);
    ck_assert_int_eq(d1, d2);
} END_TEST

START_TEST(sscanf_special_symbols_as_chars2) {
    char fstr[1096] = "%c %c %c %c";
    char str[1096] = "z ' ' /";
    int16_t a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;

    int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
    int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

    ck_assert_int_eq(res1, res2);
    ck_assert_int_eq(a1, a2);
    ck_assert_int_eq(b1, b2);
    ck_assert_int_eq(c1, c2);
    ck_assert_int_eq(d1, d2);
} END_TEST

START_TEST(sscanf_special_symbols_as_chars3) {
    char fstr[1096] = "%c%*c%c%c";
    char str[1096] = "ABCD";
    int16_t a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0;

    int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1);

    int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2);

    ck_assert_int_eq(res1, res2);
    ck_assert_int_eq(a1, a2);
    ck_assert_int_eq(b1, b2);
    ck_assert_int_eq(c1, c2);
} END_TEST

START_TEST(sscanf_chars_flags1) {
    char fstr[1096] = "%c %c %c %c";
    char str[1096] = "z *'@";
    int16_t a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;

    int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
    int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

    ck_assert_int_eq(res1, res2);
    ck_assert_int_eq(a1, a2);
    ck_assert_int_eq(b1, b2);
    ck_assert_int_eq(c1, c2);
    ck_assert_int_eq(d1, d2);
} END_TEST

START_TEST(sscanf_chars_flags2) {
    char fstr[1096] = "%1c %c %c %0c";
    char str[1096] = "z *'@";
    int16_t a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;

    int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
    int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

    ck_assert_int_eq(res1, res2);
    ck_assert_int_eq(a1, a2);
    ck_assert_int_eq(b1, b2);
    ck_assert_int_eq(c1, c2);
    ck_assert_int_eq(d1, d2);
} END_TEST

START_TEST(sscanf_chars_flags3) {
    char fstr[1096] = "%c %c %c %c";
    char str[1096] = "z *'@";
    int16_t a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;

    int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
    int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

    ck_assert_int_eq(res1, res2);
    ck_assert_int_eq(a1, a2);
    ck_assert_int_eq(b1, b2);
    ck_assert_int_eq(c1, c2);
    ck_assert_int_eq(d1, d2);
} END_TEST

START_TEST(sscanf_chars_flags4) {
    char fstr[1096] = "%c %c %c %c";
    char str[1096] = "z *'@";
    int16_t a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;

    int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
    int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

    ck_assert_int_eq(res1, res2);
    ck_assert_int_eq(a1, a2);
    ck_assert_int_eq(b1, b2);
    ck_assert_int_eq(c1, c2);
    ck_assert_int_eq(d1, d2);
} END_TEST

START_TEST(sscanf_chars_flags5) {
    char fstr[1096] = "%*c%*c%*c%c";
    char str[1096] = "abcde";
    int16_t a1 = 0, a2 = 0;

    int16_t res1 = s21_sscanf(str, fstr, &a1);
    int16_t res2 = sscanf(str, fstr, &a2);

    ck_assert_int_eq(res1, res2);
    ck_assert_int_eq(a1, a2);
} END_TEST

START_TEST(sscanf_chars_aster1) {
    char fstr[1096] = "%*c%*c%*c%*c";
    char str[1096] = "   c ";
    int16_t a1 = 0, a2 = 0;

    int16_t res1 = s21_sscanf(str, fstr, &a1);
    int16_t res2 = sscanf(str, fstr, &a2);

    ck_assert_int_eq(res1, res2);
    ck_assert_int_eq(a1, a2);
} END_TEST

START_TEST(sscanf_chars_aster2) {
    char fstr[1096] = "%*c%*c%*c%c";
    char str[1096] = "abcd ";
    int16_t a1 = 0, a2 = 0;

    int16_t res1 = s21_sscanf(str, fstr, &a1);
    int16_t res2 = sscanf(str, fstr, &a2);

    ck_assert_int_eq(res1, res2);
    ck_assert_int_eq(a1, a2);
} END_TEST

START_TEST(sscanf_only_ints1) {
    long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
    const char fstr[1096] = "%ld %ld %ld %ld";
    const char str[1096] = "555 666 777 888";

    int32_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
    int32_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

    ck_assert_int_eq(res1, res2);
    ck_assert_int_eq(a1, a2);
    ck_assert_int_eq(b1, b2);
    ck_assert_int_eq(c1, c2);
    ck_assert_int_eq(d1, d2);
} END_TEST

START_TEST(sscanf_only_ints2) {
    int16_t a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
    const char str[1096] = "1337 21 5008 3000";
    const char fstr[1096] = "%hd %hd %hd %hd";

    int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
    int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

    ck_assert_int_eq(res1, res2);
    ck_assert_int_eq(a1, a2);
    ck_assert_int_eq(b1, b2);
    ck_assert_int_eq(c1, c2);
    ck_assert_int_eq(d1, d2);
} END_TEST

START_TEST(sscanf_only_ints3) {
    long long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
    const char str[1096] = "1337 21 5008 300004";
    const char fstr[1096] = "%lld %lld %lld %lld";

    int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
    int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

    ck_assert_int_eq(res1, res2);
    ck_assert_int_eq(a1, a2);
    ck_assert_int_eq(b1, b2);
    ck_assert_int_eq(c1, c2);
    ck_assert_int_eq(d1, d2);
} END_TEST

START_TEST(sscanf_ints_nwidth1) {
    long long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
    const char str[1096] = "1337 21 5008 300004";
    const char fstr[1096] = "%1lld %3lld %1lld %4lld";

    int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
    int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

    ck_assert_int_eq(res1, res2);
    ck_assert_int_eq(a1, a2);
    ck_assert_int_eq(b1, b2);
    ck_assert_int_eq(c1, c2);
    ck_assert_int_eq(d1, d2);
} END_TEST

START_TEST(sscanf_ints_nwidth2) {
    long long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
    const char str[1096] = "1337";
    const char fstr[1096] = "%1lld %1lld %1lld %1lld";

    int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
    int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

    ck_assert_int_eq(res1, res2);
    ck_assert_int_eq(a1, a2);
    ck_assert_int_eq(b1, b2);
    ck_assert_int_eq(c1, c2);
    ck_assert_int_eq(d1, d2);
} END_TEST

START_TEST(sscanf_ints_nwidth3) {
    long long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
    const char str[1096] = "100000000000000005";
    const char fstr[1096] = "%3lld%lld%1lld%5lld";

    int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
    int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

    ck_assert_int_eq(res1, res2);
    ck_assert_int_eq(a1, a2);
    ck_assert_int_eq(b1, b2);
    ck_assert_int_eq(c1, c2);
    ck_assert_int_eq(d1, d2);
} END_TEST

START_TEST(sscanf_ints_nwidth4) {
    long long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
    const char str[1096] = "1337";
    const char fstr[1096] = "%15lld %1lld %1lld %1lld";

    int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
    int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

    ck_assert_int_eq(res1, res2);
    ck_assert_int_eq(a1, a2);
    ck_assert_int_eq(b1, b2);
    ck_assert_int_eq(c1, c2);
    ck_assert_int_eq(d1, d2);
} END_TEST

START_TEST(sscanf_ints_astwidth1) {
    long long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0;
    const char str[1096] = "1337123123 1 123412341234 1 999999 0";
    const char fstr[1096] = "%*d %lld %*d %lld %*d %lld";

    int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1);
    int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2);

    ck_assert_int_eq(res1, res2);
    ck_assert_int_eq(a1, a2);
    ck_assert_int_eq(b1, b2);
    ck_assert_int_eq(c1, c2);
} END_TEST

START_TEST(sscanf_ints_astwidth2) {
    long long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
    const char str[1096] = "1337";
    const char fstr[1096] = "%15lld %1lld %1lld %1lld";

    int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
    int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

    ck_assert_int_eq(res1, res2);
    ck_assert_int_eq(a1, a2);
    ck_assert_int_eq(b1, b2);
    ck_assert_int_eq(c1, c2);
    ck_assert_int_eq(d1, d2);
} END_TEST

START_TEST(sscanf_ints_astwidth3) {
    long long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
    const char str[1096] = "1337";
    const char fstr[1096] = "%15lld %1lld %1lld %1lld";

    int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
    int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

    ck_assert_int_eq(res1, res2);
    ck_assert_int_eq(a1, a2);
    ck_assert_int_eq(b1, b2);
    ck_assert_int_eq(c1, c2);
    ck_assert_int_eq(d1, d2);
} END_TEST

START_TEST(sscanf_ints_astwidth4) {
    long long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
    const char str[1096] = "1337";
    const char fstr[1096] = "%15lld %1lld %1lld %1lld";

    int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
    int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

    ck_assert_int_eq(res1, res2);
    ck_assert_int_eq(a1, a2);
    ck_assert_int_eq(b1, b2);
    ck_assert_int_eq(c1, c2);
    ck_assert_int_eq(d1, d2);
} END_TEST

START_TEST(sscanf_signed_ints1) {
    long long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
    const char str[1096] = "11337 ++3 -5 ------4";
    const char fstr[1096] = "%lld %lld %lld %lld";

    int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
    int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

    ck_assert_int_eq(res1, res2);
    ck_assert_int_eq(a1, a2);
    ck_assert_int_eq(b1, b2);
    ck_assert_int_eq(c1, c2);
    ck_assert_int_eq(d1, d2);
} END_TEST

START_TEST(sscanf_signed_ints2) {
    long long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
    const char str[1096] = "-1337 +1 -1 -1";
    const char fstr[1096] = "%15lld %1lld %1lld %5lld";

    int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
    int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

    ck_assert_int_eq(res1, res2);
    ck_assert_int_eq(a1, a2);
    ck_assert_int_eq(b1, b2);
    ck_assert_int_eq(c1, c2);
    ck_assert_int_eq(d1, d2);
} END_TEST

START_TEST(sscanf_signed_ints3) {
    long long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
    const char str[1096] = "-0 +0 +0 -0";
    const char fstr[1096] = "%2lld %1lld %1lld %1lld";

    int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
    int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

    ck_assert_int_eq(res1, res2);
    ck_assert_int_eq(a1, a2);
    ck_assert_int_eq(b1, b2);
    ck_assert_int_eq(c1, c2);
    ck_assert_int_eq(d1, d2);
} END_TEST

START_TEST(sscanf_signed_ints4) {
    long long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
    const char str[1096] = "1 01 10 0";
    const char fstr[1096] = "%lld %lld %lld %lld";

    int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
    int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

    ck_assert_int_eq(res1, res2);
    ck_assert_int_eq(a1, a2);
    ck_assert_int_eq(b1, b2);
    ck_assert_int_eq(c1, c2);
    ck_assert_int_eq(d1, d2);
} END_TEST

START_TEST(sscanf_spec_i_int1) {
    long long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
    const char str[1096] = "300 500 -600 +700";
    const char fstr[1096] = "%lli %lli %lli %lli";

    int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
    int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

    ck_assert_int_eq(res1, res2);
    ck_assert_int_eq(a1, a2);
    ck_assert_int_eq(b1, b2);
    ck_assert_int_eq(c1, c2);
    ck_assert_int_eq(d1, d2);
} END_TEST

START_TEST(sscanf_spec_i_int2) {
    long long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
    const char str[1096] = "300500-600+700 111";
    const char fstr[1096] = "%lli %lld %lld %lli";

    int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
    int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

    ck_assert_int_eq(res1, res2);
    ck_assert_int_eq(a1, a2);
    ck_assert_int_eq(b1, b2);
    ck_assert_int_eq(c1, c2);
    ck_assert_int_eq(d1, d2);
} END_TEST

START_TEST(sscanf_spec_i_int3) {
    long long a1 = 0, a2 = 0, c1 = 0, c2 = 0;
    char b1 = 0, b2 = 0, d1 = 0, d2 = 0;
    const char str[1096] = "300500-600+700+400";
    const char fstr[1096] = "%lli%c%lli%c";

    int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
    int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

    ck_assert_int_eq(res1, res2);
    ck_assert_int_eq(a1, a2);
    ck_assert_int_eq(b1, b2);
    ck_assert_int_eq(c1, c2);
    ck_assert_int_eq(d1, d2);
} END_TEST

START_TEST(sscanf_spec_i_int4) {
    long long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
    const char str[1096] = "  55555 f f f5555555 ddd   4    3    1 ";
    const char fstr[1096] = "%lli %lld %lld %lli";

    int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
    int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

    ck_assert_int_eq(res1, res2);
    ck_assert_int_eq(a1, a2);
    ck_assert_int_eq(b1, b2);
    ck_assert_int_eq(c1, c2);
    ck_assert_int_eq(d1, d2);
} END_TEST

START_TEST(sscanf_spec_i_hex1) {
    long long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
    const char str[1096] = "0xFFF 0xA123123 0x123123 0x0";
    const char fstr[1096] = "%lli %lld %lld %lli";

    int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
    int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

    ck_assert_int_eq(res1, res2);
    ck_assert_int_eq(a1, a2);
    ck_assert_int_eq(b1, b2);
    ck_assert_int_eq(c1, c2);
    ck_assert_int_eq(d1, d2);
} END_TEST

START_TEST(sscanf_spec_i_hex2) {
    long long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
    const char str[1096] = " 0xFFFF 0xf 0xf 0xf5555555 ddd   4    3    1 ";
    const char fstr[1096] = "%lli %lld %lld %lli";

    int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
    int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

    ck_assert_int_eq(res1, res2);
    ck_assert_int_eq(a1, a2);
    ck_assert_int_eq(b1, b2);
    ck_assert_int_eq(c1, c2);
    ck_assert_int_eq(d1, d2);
} END_TEST

START_TEST(sscanf_spec_i_oct1) {
    long long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
    const char str[1096] = "  055555 0f 0f 0f5555555 0ddd   4    3    1 ";
    const char fstr[1096] = "%lli %lld %lld %lli";

    int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
    int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

    ck_assert_int_eq(res1, res2);
    ck_assert_int_eq(a1, a2);
    ck_assert_int_eq(b1, b2);
    ck_assert_int_eq(c1, c2);
    ck_assert_int_eq(d1, d2);
} END_TEST

START_TEST(sscanf_spec_i_oct2) {
    long long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
    const char str[1096] = "  055555 0f 0f 0f5555555 0ddd   4    3    1 ";
    const char fstr[1096] = "%lli %lld %lld %lli";

    int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
    int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

    ck_assert_int_eq(res1, res2);
    ck_assert_int_eq(a1, a2);
    ck_assert_int_eq(b1, b2);
    ck_assert_int_eq(c1, c2);
    ck_assert_int_eq(d1, d2);
} END_TEST

// [%s] //
START_TEST(sscanf_strings1) {
    char s1[BUFF_SIZE] = {'\0'};
    char s2[BUFF_SIZE] = {'\0'};
    char s3[BUFF_SIZE] = {'\0'};
    char s4[BUFF_SIZE] = {'\0'};

    char s5[BUFF_SIZE] = {'\0'};
    char s6[BUFF_SIZE] = {'\0'};
    char s7[BUFF_SIZE] = {'\0'};
    char s8[BUFF_SIZE] = {'\0'};

    const char str[1096] = "Aboba Floppa Keppa Shleppa Anuroba";
    const char fstr[1096] = "%s %s %s %s";

    int16_t res1 = s21_sscanf(str, fstr, s1, s2, s3, s4);
    int16_t res2 = sscanf(str, fstr, s5, s6, s7, s8);

    ck_assert_int_eq(res1, res2);

    ck_assert_str_eq(s1, s5);
    ck_assert_str_eq(s2, s6);
    ck_assert_str_eq(s3, s7);
    ck_assert_str_eq(s4, s8);
} END_TEST

START_TEST(sscanf_strings_mixed3) {
    char s1[BUFF_SIZE] = {'\0'};
    char s2[BUFF_SIZE] = {'\0'};
    char s3[BUFF_SIZE] = {'\0'};
    char s4[BUFF_SIZE] = {'\0'};

    char s5[BUFF_SIZE] = {'\0'};
    char s6[BUFF_SIZE] = {'\0'};
    char s7[BUFF_SIZE] = {'\0'};
    char s8[BUFF_SIZE] = {'\0'};

    long long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;

    const char str[1096] = "Aboba 123 Floppa -3 Keppa 4444Shleppa 333Anuroba 3";
    const char fstr[1096] = "%s%ld%s%d%s%d%s";

    int16_t res1 = s21_sscanf(str, fstr, s1, &a1, s2, &b1, s3, &c1, s4, &d1);
    int16_t res2 = s21_sscanf(str, fstr, s5, &a2, s6, &b2, s7, &c2, s8, &d2);

    ck_assert_int_eq(res1, res2);
    ck_assert_int_eq(a1, a2);
    ck_assert_int_eq(b1, b2);
    ck_assert_int_eq(c1, c2);
    ck_assert_int_eq(d1, d2);

    ck_assert_str_eq(s1, s5);
    ck_assert_str_eq(s2, s6);
    ck_assert_str_eq(s3, s7);
    ck_assert_str_eq(s4, s8);
} END_TEST

START_TEST(sscanf_strings2) {
    char s1[BUFF_SIZE] = {'\0'};
    char s2[BUFF_SIZE] = {'\0'};
    char s3[BUFF_SIZE] = {'\0'};
    char s4[BUFF_SIZE] = {'\0'};

    char s5[BUFF_SIZE] = {'\0'};
    char s6[BUFF_SIZE] = {'\0'};
    char s7[BUFF_SIZE] = {'\0'};
    char s8[BUFF_SIZE] = {'\0'};

    const char str[1096] = "aboba\tshlepa\tasdfasdf\tasdfasdf";
    const char fstr[1096] = "%s%s%s%s";

    int16_t res1 = s21_sscanf(str, fstr, s1, s2, s3, s4);
    int16_t res2 = sscanf(str, fstr, s5, s6, s7, s8);

    ck_assert_int_eq(res1, res2);

    ck_assert_str_eq(s1, s5);
    ck_assert_str_eq(s2, s6);
    ck_assert_str_eq(s3, s7);
    ck_assert_str_eq(s4, s8);
} END_TEST

START_TEST(sscanf_strings3) {
    char s1[BUFF_SIZE] = {'\0'};
    char s2[BUFF_SIZE] = {'\0'};
    char s3[BUFF_SIZE] = {'\0'};
    char s4[BUFF_SIZE] = {'\0'};

    char s5[BUFF_SIZE] = {'\0'};
    char s6[BUFF_SIZE] = {'\0'};
    char s7[BUFF_SIZE] = {'\0'};
    char s8[BUFF_SIZE] = {'\0'};

    const char str[1096] = "aboba\tkepaboba floppa shleppa koooppa ap p p p p";
    const char fstr[1096] = "%*s%*s%*s%*s";

    int16_t res1 = s21_sscanf(str, fstr);
    int16_t res2 = sscanf(str, fstr);

    ck_assert_int_eq(res1, res2);

    ck_assert_str_eq(s1, s5);
    ck_assert_str_eq(s2, s6);
    ck_assert_str_eq(s3, s7);
    ck_assert_str_eq(s4, s8);
} END_TEST

START_TEST(sscanf_strings4) {
    char s1[BUFF_SIZE] = {'\0'};
    char s2[BUFF_SIZE] = {'\0'};
    char s3[BUFF_SIZE] = {'\0'};
    char s4[BUFF_SIZE] = {'\0'};

    char s5[BUFF_SIZE] = {'\0'};
    char s6[BUFF_SIZE] = {'\0'};
    char s7[BUFF_SIZE] = {'\0'};
    char s8[BUFF_SIZE] = {'\0'};

    const char str[1096] = "aboba\tshlepa\tasdfasdf\tasdfasdf";
    const char fstr[1096] = "%1s%1s%1s%1s";

    int16_t res1 = s21_sscanf(str, fstr, s1, s2, s3, s4);
    int16_t res2 = sscanf(str, fstr, s5, s6, s7, s8);

    ck_assert_int_eq(res1, res2);

    ck_assert_str_eq(s1, s5);
    ck_assert_str_eq(s2, s6);
    ck_assert_str_eq(s3, s7);
    ck_assert_str_eq(s4, s8);
} END_TEST

START_TEST(sscanf_strings5) {
    char s1[BUFF_SIZE] = {'\0'};
    char s2[BUFF_SIZE] = {'\0'};
    char s3[BUFF_SIZE] = {'\0'};
    char s4[BUFF_SIZE] = {'\0'};

    char s5[BUFF_SIZE] = {'\0'};
    char s6[BUFF_SIZE] = {'\0'};
    char s7[BUFF_SIZE] = {'\0'};
    char s8[BUFF_SIZE] = {'\0'};

    const char str[1096] = "aboba\tshlepa\tasdfasdf\tasdfasdf";
    const char fstr[1096] = "%3s%3s%3s%3s";

    int16_t res1 = s21_sscanf(str, fstr, s1, s2, s3, s4);
    int16_t res2 = sscanf(str, fstr, s5, s6, s7, s8);

    ck_assert_int_eq(res1, res2);

    ck_assert_str_eq(s1, s5);
    ck_assert_str_eq(s2, s6);
    ck_assert_str_eq(s3, s7);
    ck_assert_str_eq(s4, s8);
} END_TEST

START_TEST(sscanf_strings6) {
    char s1[BUFF_SIZE] = {'\0'};
    char s2[BUFF_SIZE] = {'\0'};
    char s3[BUFF_SIZE] = {'\0'};
    char s4[BUFF_SIZE] = {'\0'};

    char s5[BUFF_SIZE] = {'\0'};
    char s6[BUFF_SIZE] = {'\0'};
    char s7[BUFF_SIZE] = {'\0'};
    char s8[BUFF_SIZE] = {'\0'};

    const char str[1096] = "aboba\tshlepa\tasdfasdf\tasdfasdf";
    const char fstr[1096] = "%150s%1s%1s\t%3s";

    int16_t res1 = s21_sscanf(str, fstr, s1, s2, s3, s4);
    int16_t res2 = sscanf(str, fstr, s5, s6, s7, s8);

    ck_assert_int_eq(res1, res2);

    ck_assert_str_eq(s1, s5);
    ck_assert_str_eq(s2, s6);
    ck_assert_str_eq(s3, s7);
    ck_assert_str_eq(s4, s8);
} END_TEST

// strings_mixed1
START_TEST(sscanf_strings_mixed1) {
    unsigned long long int a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0;
    long long d1 = 0, d2 = 0;
    long double e1 = 0, e2 = 0;

    const char str[1096] = "4444444"
                       "eeeeeee\teeeeeee";
    const char fstr[1096] = "%5s %1s %*s %*s %llu %s %llu %llu %lld %Lf %33s";

    char s1[BUFF_SIZE] = {'\0'};
    char s2[BUFF_SIZE] = {'\0'};
    char s3[BUFF_SIZE] = {'\0'};
    char s4[BUFF_SIZE] = {'\0'};
    char s5[BUFF_SIZE] = {'\0'};
    char s6[BUFF_SIZE] = {'\0'};
    char s7[BUFF_SIZE] = {'\0'};
    char s8[BUFF_SIZE] = {'\0'};
    char s9[BUFF_SIZE] = {'\0'};
    char s10[BUFF_SIZE] = {'\0'};

    int16_t res1 =
        s21_sscanf(str, fstr, s7, s9, &a1, s5, &b1, &c1, &d1, &e1, s1);
    int16_t res2 = sscanf(str, fstr, s8, s10, &a2, s6, &b2, &c2, &d2, &e2, s2);

    ck_assert_int_eq(res1, res2);
    ck_assert_str_eq(s1, s2);
    ck_assert_str_eq(s3, s4);
    ck_assert_str_eq(s5, s6);
    ck_assert_int_eq(a1, a2);
    ck_assert_int_eq(b1, b2);
    ck_assert_int_eq(c1, c2);
    ck_assert_int_eq(d1, d2);
} END_TEST

START_TEST(sscanf_strings_mixed2) {
    int d1 = 0, d2 = 0, b1 = 0, b2 = 0, a1 = 0, a2 = 0;
    long long v1, v2;

    const char str[1096] = "1 1 1 1 1 -1";
    const char fstr[1096] = "%1s %5d %1s %1s %d %lld %d";

    char s1[BUFF_SIZE] = {'\0'};
    char s2[BUFF_SIZE] = {'\0'};
    char s3[BUFF_SIZE] = {'\0'};
    char s4[BUFF_SIZE] = {'\0'};
    char s5[BUFF_SIZE] = {'\0'};
    char s6[BUFF_SIZE] = {'\0'};

    int16_t res1 = s21_sscanf(str, fstr, s1, &a1, s2, s3, &b1, &v1, &d1);
    int16_t res2 = sscanf(str, fstr, s4, &a2, s5, s6, &b2, &v2, &d2);

    ck_assert_int_eq(res1, res2);
    ck_assert_str_eq(s1, s2);
    ck_assert_str_eq(s3, s4);
    ck_assert_str_eq(s5, s6);
    ck_assert_int_eq(a1, a2);
    ck_assert_int_eq(b1, b2);
    ck_assert_int_eq(d1, d2);
} END_TEST

// [%n] //
START_TEST(sscanf_n1) {
    long long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
    int32_t n1 = 0, n2 = 5;

    const char str[BUFF_SIZE] = "50 160 70 80";
    const char fstr[BUFF_SIZE] = "%lli %lli %n %lli %lli";

    int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &n1, &c1, &d1);
    int16_t res2 = sscanf(str, fstr, &a2, &b2, &n2, &c2, &d2);

    ck_assert_int_eq(res1, res2);
    ck_assert_int_eq(n1, n2);
    ck_assert_int_eq(a1, a2);
    ck_assert_int_eq(b1, b2);
    ck_assert_int_eq(c1, c2);
    ck_assert_int_eq(d1, d2);
} END_TEST

START_TEST(sscanf_n2) {
    int n1 = 1, n2 = 5;

    char s1[BUFF_SIZE] = {'\0'};
    char s2[BUFF_SIZE] = {'\0'};
    char s3[BUFF_SIZE] = {'\0'};
    char s5[BUFF_SIZE] = {'\0'};
    char s6[BUFF_SIZE] = {'\0'};
    char s7[BUFF_SIZE] = {'\0'};

    const char str[1096] = "cbobErobM fl? asdfasdflkasdf asdfasdf asdfasdf 88888";
    const char fstr[1096] = "%s %s %n %s";

    int32_t res1 = s21_sscanf(str, fstr, s1, s2, &n1, s3);
    int32_t res2 = sscanf(str, fstr, s5, s6, &n2, s7);

    ck_assert_int_eq(res1, res2);

    ck_assert_int_eq(n1, n2);
    ck_assert_str_eq(s1, s5);
    ck_assert_str_eq(s2, s6);
    ck_assert_str_eq(s3, s7);
} END_TEST

START_TEST(sscanf_n3) {
    int n1 = 0, n2 = 5;

    const char str[BUFF_SIZE] = "50 60 70 80";
    const char fstr[BUFF_SIZE] = "%n";

    int16_t res1 = s21_sscanf(str, fstr, &n1);
    int16_t res2 = sscanf(str, fstr, &n2);

    ck_assert_int_eq(res1, res2);
    ck_assert_int_eq(n1, n2);
} END_TEST

START_TEST(sscanf_n4) {
    long long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
    int32_t n1 = 0, n2 = 5;

    const char str[1096] = "50 60 70 80";
    const char fstr[1096] = "%lli %lli %n %lli %lli";

    int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &n1, &c1, &d1);
    int16_t res2 = sscanf(str, fstr, &a2, &b2, &n2, &c2, &d2);

    ck_assert_int_eq(res1, res2);
    ck_assert_int_eq(n1, n2);
    ck_assert_int_eq(a1, a2);
    ck_assert_int_eq(b1, b2);
    ck_assert_int_eq(c1, c2);
    ck_assert_int_eq(d1, d2);
} END_TEST

START_TEST(sscanf_n5) {
    long long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
    int n1 = 0, n2 = 5;

    const char str[1096] = "50 60 70 80";
    const char fstr[1096] = "%lli %lli %n %lli %lli";

    int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &n1, &c1, &d1);
    int16_t res2 = sscanf(str, fstr, &a2, &b2, &n2, &c2, &d2);

    ck_assert_int_eq(res1, res2);
    ck_assert_int_eq(n1, n2);
    ck_assert_int_eq(a1, a2);
    ck_assert_int_eq(b1, b2);
    ck_assert_int_eq(c1, c2);
    ck_assert_int_eq(d1, d2);
} END_TEST

// [%f] / [%g] / %[%G] //
START_TEST(sscanf_floats1) {
    long double a1 = 1, a2 = 0, b1 = 1, b2 = 0, c1 = 1, c2 = 0, d1 = 1, d2 = 0;

    const char str[1096] = "53.1 -4.1135 41.3333 +2.0001";
    const char fstr[1096] = "%Lf %Lf %Lf %Lf";

    int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
    int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

    ck_assert_int_eq(res1, res2);
    ck_assert_double_eq(a1, a2);
    ck_assert_double_eq(b1, b2);
    ck_assert_double_eq(c1, c2);
    ck_assert_double_eq(d1, d2);
} END_TEST

START_TEST(sscanf_floats2) {
    double a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;

    const char str[1096] = "0.00001 -4123123 4. .";
    const char fstr[1096] = "%lf %lf %lf %lf";

    int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
    int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

    ck_assert_int_eq(res1, res2);
    ck_assert_double_eq(a1, a2);
    ck_assert_double_eq(b1, b2);
    ck_assert_double_eq(c1, c2);
    ck_assert_double_eq(d1, d2);
} END_TEST

START_TEST(sscanf_floats3) {
    float a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;

    const char str[1096] = ". . . .";
    const char fstr[1096] = "%f %f %f %f";

    int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
    int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

    ck_assert_int_eq(res1, res2);
    ck_assert_double_eq(a1, a2);
    ck_assert_double_eq(b1, b2);
    ck_assert_double_eq(c1, c2);
    ck_assert_double_eq(d1, d2);
} END_TEST

START_TEST(sscanf_floats4) {
    long double a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;

    const char str[1096] = "513.41 -4.14135 414.3333 +112.0001";
    const char fstr[1096] = "%Lf %Lf %Lf %Lf";

    int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
    int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

    ck_assert_int_eq(res1, res2);
    ck_assert_double_eq(a1, a2);
    ck_assert_double_eq(b1, b2);
    ck_assert_double_eq(c1, c2);
    ck_assert_double_eq(d1, d2);
} END_TEST

START_TEST(sscanf_floats5) {
    float a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0;

    const char str[1096] = "53.1 -4.1135 411231.333 +2.0001";
    const char fstr[1096] = "%*f %f %f %f";

    int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1);
    int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2);

    ck_assert_int_eq(res1, res2);
    ck_assert_float_eq(a1, a2);
    ck_assert_float_eq(b1, b2);
    ck_assert_float_eq(c1, c2);
} END_TEST

START_TEST(sscanf_floats_sci1) {
    float a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;

    const char str[1096] = "1.4441 1.31e+4 -3.31e-4 0.444e-5";
    const char fstr[1096] = "%G %G %G %G";

    int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
    int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

    ck_assert_int_eq(res1, res2);
    ck_assert_double_eq(a1, a2);
    ck_assert_double_eq(b1, b2);
    ck_assert_double_eq(c1, c2);
    ck_assert_double_eq(d1, d2);
} END_TEST

START_TEST(sscanf_floats_sci2) {
    float a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;

    const char str[1096] = "inf 1.31e+4 NaN 0.444e-5";
    const char fstr[1096] = "%G %G %G %G";

    int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
    int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

    ck_assert_int_eq(res1, res2);
    ck_assert_ldouble_eq(a1, a2);
    // Unfortunately, assertions for inf do not work correctly in libcheck
    // ck_assert_ldouble_infinite(a1);
    // ck_assert_ldouble_infinite(a2);
    ck_assert_double_eq(b1, b2);
    ck_assert_float_nan(c1);
    ck_assert_float_nan(c2);
    ck_assert_double_eq(d1, d2);
} END_TEST

START_TEST(sscanf_floats_sci3) {
    float a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;

    const char str[1096] = "inF InF inF INF";
    const char fstr[1096] = "%G %G %G %G";

    int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
    int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

    ck_assert_int_eq(res1, res2);
    ck_assert_ldouble_eq(a1, a2);
    ck_assert_double_eq(b1, b2);
    ck_assert_double_eq(c1, c2);
    ck_assert_double_eq(d1, d2);
} END_TEST

START_TEST(sscanf_floats_sci4) {
    float a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;

    const char str[1096] = "Nan NAN 0.0000 0";
    const char fstr[1096] = "%G %G %G %G";

    int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
    int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

    ck_assert_int_eq(res1, res2);
    ck_assert_float_nan(a1);
    ck_assert_float_nan(a2);
    ck_assert_float_nan(b1);
    ck_assert_float_nan(b2);
    ck_assert_ldouble_eq(c1, c2);
    ck_assert_ldouble_eq(d1, d2);
} END_TEST

START_TEST(sscanf_floats_sci5) {
    float a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;

    const char str[1096] =
        "nAN           INF                   -0.1111         1e-10";
    const char fstr[1096] = "%G %G %G %G";

    int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
    int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

    ck_assert_int_eq(res1, res2);
    ck_assert_float_nan(a1);
    ck_assert_float_nan(a2);
    ck_assert_ldouble_eq(b1, b2);
    ck_assert_ldouble_eq(c1, c2);
    ck_assert_ldouble_eq(d1, d2);
} END_TEST

// [%u] //
START_TEST(sscanf_uint1) {
    unsigned short a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0,
                   d2 = 0;
    const char str[1096] = "-1337 +21 --5008 3000";
    const char fstr[1096] = "%hu %hu %hu %hu";

    int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
    int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

    ck_assert_uint_eq(res1, res2);
    ck_assert_uint_eq(a1, a2);
    ck_assert_uint_eq(b1, b2);
    ck_assert_uint_eq(c1, c2);
    ck_assert_uint_eq(d1, d2);
} END_TEST

START_TEST(sscanf_uint2) {
    unsigned long long int a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0,
                           d1 = 0, d2 = 0;
    const char str[1096] = "-1337 233333331 5008 3000";
    const char fstr[1096] = "%1llu %2llu %5llu %4llu";

    int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
    int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

    ck_assert_int_eq(res1, res2);
    ck_assert_int_eq(a1, a2);
    ck_assert_int_eq(b1, b2);
    ck_assert_int_eq(c1, c2);
    ck_assert_int_eq(d1, d2);
} END_TEST

START_TEST(sscanf_uint3) {
    unsigned long long int a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0;
    long long d1 = 0, d2 = 0;
    long double v1, v2;

    const char str[1096] =
        "\t\t\t\t\t\n 3      adsfdfa%$$$$`adfasdfasdfaszcvzcxvcv -1337 "
        "anurobich+ 21 -5008 -33000 0.3333";
    const char fstr[1096] = "%*s %*s %llu %s %llu %llu %lld %Lf";

    char s1[BUFF_SIZE] = {'\0'};
    char s2[BUFF_SIZE] = {'\0'};

    int16_t res1 = s21_sscanf(str, fstr, &a1, s1, &b1, &c1, &d1, &v1);
    int16_t res2 = sscanf(str, fstr, &a2, s2, &b2, &c2, &d2, &v2);

    ck_assert_uint_eq(res1, res2);
    ck_assert_str_eq(s1, s2);
    ck_assert_uint_eq(a1, a2);
    ck_assert_uint_eq(b1, b2);
    ck_assert_uint_eq(c1, c2);
    ck_assert_uint_eq(d1, d2);
    ck_assert_ldouble_eq_tol(v1, v2, 0.0001);
} END_TEST

START_TEST(sscanf_uint4) {
    unsigned short a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0,
                   d2 = 0;
    const char str[1096] = "-1337 +21 --5008 3000";
    const char fstr[1096] = "%hu %hu %hu %hu";

    int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
    int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

    ck_assert_int_eq(res1, res2);
    ck_assert_int_eq(a1, a2);
    ck_assert_int_eq(b1, b2);
    ck_assert_int_eq(c1, c2);
    ck_assert_int_eq(d1, d2);
} END_TEST

START_TEST(sscanf_uint5) {
    unsigned short a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0,
                   d2 = 0;
    const char str[1096] = "-1337 +21 --5008 3000";
    const char fstr[1096] = "%hu %hu %hu %hu";

    int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
    int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

    ck_assert_int_eq(res1, res2);
    ck_assert_int_eq(a1, a2);
    ck_assert_int_eq(b1, b2);
    ck_assert_int_eq(c1, c2);
    ck_assert_int_eq(d1, d2);
} END_TEST

START_TEST(sscanf_uint6) {
    unsigned short a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0,
                   d2 = 0;
    const char str[1096] = "-1337 +21 --5008 3000";
    const char fstr[1096] = "%hu %hu %hu %hu";

    int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
    int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

    ck_assert_int_eq(res1, res2);
    ck_assert_int_eq(a1, a2);
    ck_assert_int_eq(b1, b2);
    ck_assert_int_eq(c1, c2);
    ck_assert_int_eq(d1, d2);
} END_TEST

START_TEST(sscanf_upeer_hex_base_version) {
    uint32_t a1, a2;
    const char str[1096] = "F";
    const char fstr[1096] = "%X";
    uint32_t res1 = s21_sscanf(str, fstr, &a1);
    uint32_t res2 = sscanf(str, fstr, &a2);

    ck_assert_int_eq(res1, res2);
    ck_assert_int_eq(a1, a2);
} END_TEST

START_TEST(sscanf_upeer_hex_overflow) {
    uint32_t a1, a2;
    const char str[1096] = "0xFFFFFFFF";
    const char fstr[1096] = "%X";
    uint32_t res1 = s21_sscanf(str, fstr, &a1);
    uint32_t res2 = sscanf(str, fstr, &a2);

    ck_assert_int_eq(res1, res2);
    ck_assert_int_eq(a1, a2);
} END_TEST

START_TEST(sscanf_upeer_hex_0x) {
    uint32_t a1, a2;
    const char str[1096] = "0x";
    const char fstr[1096] = "%X";
    uint32_t res1 = s21_sscanf(str, fstr, &a1);
    uint32_t res2 = sscanf(str, fstr, &a2);

    ck_assert_int_eq(res1, res2);
    ck_assert_int_eq(a1, a2);
} END_TEST

START_TEST(sscanf_upeer_hex_0X) {
    uint32_t a1, a2;
    const char str[1096] = "0X";
    const char fstr[1096] = "%X";
    uint32_t res1 = s21_sscanf(str, fstr, &a1);
    uint32_t res2 = sscanf(str, fstr, &a2);

    ck_assert_int_eq(res1, res2);
    ck_assert_int_eq(a1, a2);
} END_TEST

START_TEST(sscanf_upeer_hex_empty) {
    uint32_t a1, a2;
    const char str[1096] = "";
    const char fstr[1096] = "%X";
    uint32_t res1 = s21_sscanf(str, fstr, &a1);
    uint32_t res2 = sscanf(str, fstr, &a2);

    ck_assert_int_eq(res1, res2);
} END_TEST

START_TEST(sscanf_upeer_hex_fail) {
    uint32_t a1, a2;
    const char str[1096] = "qF";
    const char fstr[1096] = "%X";
    uint32_t res1 = s21_sscanf(str, fstr, &a1);
    uint32_t res2 = sscanf(str, fstr, &a2);

    ck_assert_int_eq(res1, res2);
} END_TEST

START_TEST(sscanf_upeer_hex_spaces_tabs_sns) {
    uint32_t a1, a2;
    const char str[1096] = "          \n             \n     F";
    const char fstr[1096] = "%X";
    uint32_t res1 = s21_sscanf(str, fstr, &a1);
    uint32_t res2 = sscanf(str, fstr, &a2);

    ck_assert_int_eq(res1, res2);
    ck_assert_int_eq(a1, a2);
} END_TEST

START_TEST(sscanf_upeer_hex_short) {
    uint16_t a1, a2;
    const char str[1096] = "F";
    const char fstr[1096] = "%hX";
    uint16_t res1 = s21_sscanf(str, fstr, &a1);
    uint16_t res2 = sscanf(str, fstr, &a2);

    ck_assert_int_eq(res1, res2);
    ck_assert_int_eq(a1, a2);
} END_TEST

START_TEST(sscanf_upeer_hex_long) {
    unsigned long int a1, a2;
    const char str[1096] = "F";
    const char fstr[1096] = "%lX";
    uint16_t res1 = s21_sscanf(str, fstr, &a1);
    uint16_t res2 = sscanf(str, fstr, &a2);

    ck_assert_int_eq(res1, res2);
    ck_assert_int_eq(a1, a2);
} END_TEST

START_TEST(sscanf_upeer_hex_longlong) {
    unsigned long long int a1, a2;
    const char str[1096] = "F";
    const char fstr[1096] = "%llX";
    uint16_t res1 = s21_sscanf(str, fstr, &a1);
    uint16_t res2 = sscanf(str, fstr, &a2);

    ck_assert_int_eq(res1, res2);
    ck_assert_int_eq(a1, a2);
} END_TEST

START_TEST(sscanf_upeer_hex_2x) {
    uint32_t a1, a2;
    const char str[1096] = "0xFF0x0xFFF 0xFFxFF";
    const char fstr[1096] = "%X";
    uint32_t res1 = s21_sscanf(str, fstr, &a1);
    uint32_t res2 = sscanf(str, fstr, &a2);

    ck_assert_int_eq(res1, res2);
    ck_assert_int_eq(a1, a2);
} END_TEST

START_TEST(sscanf_upeer_hex_star) {
    const char str[1096] = "0xFF0x0xFFF 0xFFxFF";
    const char fstr[1096] = "%*X";
    uint32_t res1 = s21_sscanf(str, fstr);
    uint32_t res2 = sscanf(str, fstr);

    ck_assert_int_eq(res1, res2);
} END_TEST

START_TEST(sscanf_upeer_hex_nohex) {
    uint32_t a1, a2;
    const char str[1096] = "tqwqpl";
    const char fstr[1096] = "%X";
    uint32_t res1 = s21_sscanf(str, fstr, &a1);
    uint32_t res2 = sscanf(str, fstr, &a2);

    ck_assert_int_eq(res1, res2);
} END_TEST

START_TEST(sscanf_upeer_hex_lower) {
    uint32_t a1, a2;
    const char str[1096] = "abcdef";
    const char fstr[1096] = "%X";
    uint32_t res1 = s21_sscanf(str, fstr, &a1);
    uint32_t res2 = sscanf(str, fstr, &a2);

    ck_assert_int_eq(res1, res2);
    ck_assert_int_eq(a1, a2);
} END_TEST

START_TEST(sscanf_upeer_hex_sign) {
    uint32_t a1, a2;
    const char str[1096] = "-f";
    const char fstr[1096] = "%X";
    uint32_t res1 = s21_sscanf(str, fstr, &a1);
    uint32_t res2 = sscanf(str, fstr, &a2);

    ck_assert_int_eq(res1, res2);
    ck_assert_int_eq(a1, a2);
} END_TEST

START_TEST(sscanf_lower_hex_base_version) {
    uint32_t a1, a2;
    const char str[1096] = "f";
    const char fstr[1096] = "%x";
    uint32_t res1 = s21_sscanf(str, fstr, &a1);
    uint32_t res2 = sscanf(str, fstr, &a2);

    ck_assert_int_eq(res1, res2);
    ck_assert_int_eq(a1, a2);
} END_TEST

START_TEST(sscanf_lower_hex_overflow) {
    uint32_t a1, a2;
    const char str[1096] = "0xfffffffffffffffffff";
    const char fstr[1096] = "%x";
    uint32_t res1 = s21_sscanf(str, fstr, &a1);
    uint32_t res2 = sscanf(str, fstr, &a2);

    ck_assert_int_eq(res1, res2);
    ck_assert_int_eq(a1, a2);
} END_TEST

START_TEST(sscanf_lower_hex_0x) {
    uint32_t a1, a2;
    const char str[1096] = "0x";
    const char fstr[1096] = "%x";
    uint32_t res1 = s21_sscanf(str, fstr, &a1);
    uint32_t res2 = sscanf(str, fstr, &a2);

    ck_assert_int_eq(res1, res2);
    ck_assert_int_eq(a1, a2);
} END_TEST

START_TEST(sscanf_lower_hex_0X) {
    uint32_t a1, a2;
    const char str[1096] = "0X";
    const char fstr[1096] = "%x";
    uint32_t res1 = s21_sscanf(str, fstr, &a1);
    uint32_t res2 = sscanf(str, fstr, &a2);

    ck_assert_int_eq(res1, res2);
    ck_assert_int_eq(a1, a2);
} END_TEST

START_TEST(sscanf_lower_hex_empty) {
    uint32_t a1, a2;
    const char str[1096] = "";
    const char fstr[1096] = "%x";
    uint32_t res1 = s21_sscanf(str, fstr, &a1);
    uint32_t res2 = sscanf(str, fstr, &a2);

    ck_assert_int_eq(res1, res2);
} END_TEST

START_TEST(sscanf_lower_hex_fail) {
    uint32_t a1, a2;
    const char str[1096] = "qF";
    const char fstr[1096] = "%x";
    uint32_t res1 = s21_sscanf(str, fstr, &a1);
    uint32_t res2 = sscanf(str, fstr, &a2);

    ck_assert_int_eq(res1, res2);
} END_TEST

START_TEST(sscanf_lower_hex_spaces_tabs_sns) {
    uint32_t a1, a2;
    const char str[1096] = "          \n             \n     F";
    const char fstr[1096] = "%x";
    uint32_t res1 = s21_sscanf(str, fstr, &a1);
    uint32_t res2 = sscanf(str, fstr, &a2);

    ck_assert_int_eq(res1, res2);
    ck_assert_int_eq(a1, a2);
} END_TEST

START_TEST(sscanf_lower_hex_short) {
    uint16_t a1, a2;
    const char str[1096] = "ff";
    const char fstr[1096] = "%hx";
    uint16_t res1 = s21_sscanf(str, fstr, &a1);
    uint16_t res2 = sscanf(str, fstr, &a2);

    ck_assert_int_eq(res1, res2);
    ck_assert_int_eq(a1, a2);
} END_TEST

START_TEST(sscanf_lower_hex_long) {
    unsigned long int a1, a2;
    const char str[1096] = "ff";
    const char fstr[1096] = "%lx";
    uint16_t res1 = s21_sscanf(str, fstr, &a1);
    uint16_t res2 = sscanf(str, fstr, &a2);

    ck_assert_int_eq(res1, res2);
    ck_assert_int_eq(a1, a2);
} END_TEST

START_TEST(sscanf_lower_hex_longlong) {
    unsigned long long int a1, a2;
    const char str[1096] = "faaaaaaaaaaaaf";
    const char fstr[1096] = "%llx";
    uint16_t res1 = s21_sscanf(str, fstr, &a1);
    uint16_t res2 = sscanf(str, fstr, &a2);

    ck_assert_int_eq(res1, res2);
    // ck_assert_unsigned long long int_eq(a1, a2);
    // ck_assert_uint64_eq(a1, a2);
    ck_assert_uint_eq(a1, a2);
} END_TEST

START_TEST(sscanf_lower_hex_2x) {
    uint32_t a1, a2;
    const char str[1096] = "0xFF0x0xFFF 0xFFxFF";
    const char fstr[1096] = "%x";
    uint32_t res1 = s21_sscanf(str, fstr, &a1);
    uint32_t res2 = sscanf(str, fstr, &a2);

    ck_assert_int_eq(res1, res2);
    ck_assert_int_eq(a1, a2);
} END_TEST

START_TEST(sscanf_lower_hex_star) {
    const char str[1096] = "0xFF0x0xFFF 0xFFxFF";
    const char fstr[1096] = "%*x";
    uint32_t res1 = s21_sscanf(str, fstr);
    uint32_t res2 = sscanf(str, fstr);

    ck_assert_int_eq(res1, res2);
} END_TEST

START_TEST(sscanf_lower_hex_nohex) {
    uint32_t a1, a2;
    const char str[1096] = "tqwqpl";
    const char fstr[1096] = "%x";
    uint32_t res1 = s21_sscanf(str, fstr, &a1);
    uint32_t res2 = sscanf(str, fstr, &a2);

    ck_assert_int_eq(res1, res2);
} END_TEST

START_TEST(sscanf_lower_hex_lower) {
    uint32_t a1, a2;
    const char str[1096] = "abcdef";
    const char fstr[1096] = "%x";
    uint32_t res1 = s21_sscanf(str, fstr, &a1);
    uint32_t res2 = sscanf(str, fstr, &a2);

    ck_assert_int_eq(res1, res2);
    ck_assert_int_eq(a1, a2);
} END_TEST

START_TEST(sscanf_lower_hex_sign) {
    uint32_t a1, a2;
    const char str[1096] = "-f";
    const char fstr[1096] = "%x";
    uint32_t res1 = s21_sscanf(str, fstr, &a1);
    uint32_t res2 = sscanf(str, fstr, &a2);

    ck_assert_int_eq(res1, res2);
    ck_assert_int_eq(a1, a2);
} END_TEST

START_TEST(upper_hex_len) {
    uint32_t a1, a2;
    const char str[1096] = "123531FFF";
    const char fstr[1096] = "%2X";
    uint32_t res1 = s21_sscanf(str, fstr, &a1);
    uint32_t res2 = sscanf(str, fstr, &a2);

    ck_assert_int_eq(res1, res2);
    ck_assert_int_eq(a1, a2);
} END_TEST

START_TEST(sscanf_lower_hex_len) {
    uint32_t a1, a2;
    const char str[1096] = "123531FFF";
    const char fstr[1096] = "%2x";
    uint32_t res1 = s21_sscanf(str, fstr, &a1);
    uint32_t res2 = sscanf(str, fstr, &a2);

    ck_assert_int_eq(res1, res2);
    ck_assert_int_eq(a1, a2);
} END_TEST

START_TEST(sscanf_octal_base_version) {
    uint32_t a1, a2;
    const char str[1096] = "777";
    const char fstr[1096] = "%o";
    uint32_t res1 = s21_sscanf(str, fstr, &a1);
    uint32_t res2 = sscanf(str, fstr, &a2);

    ck_assert_int_eq(res1, res2);
    ck_assert_int_eq(a1, a2);
} END_TEST

START_TEST(sscanf_octal_overflow) {
    uint32_t a1, a2;
    const char str[1096] = "0x7777777777777777777777";
    const char fstr[1096] = "%o";
    uint32_t res1 = s21_sscanf(str, fstr, &a1);
    uint32_t res2 = sscanf(str, fstr, &a2);

    ck_assert_int_eq(res1, res2);
    ck_assert_int_eq(a1, a2);
} END_TEST

START_TEST(sscanf_octal_0x) {
    uint32_t a1, a2;
    const char str[1096] = "0x";
    const char fstr[1096] = "%o";
    uint32_t res1 = s21_sscanf(str, fstr, &a1);
    uint32_t res2 = sscanf(str, fstr, &a2);

    ck_assert_int_eq(res1, res2);
    ck_assert_int_eq(a1, a2);
} END_TEST

START_TEST(sscanf_octal_0X) {
    uint32_t a1, a2;
    const char str[1096] = "0X";
    const char fstr[1096] = "%o";
    uint32_t res1 = s21_sscanf(str, fstr, &a1);
    uint32_t res2 = sscanf(str, fstr, &a2);

    ck_assert_int_eq(res1, res2);
    ck_assert_int_eq(a1, a2);
} END_TEST

START_TEST(sscanf_octal_empty) {
    uint32_t a1, a2;
    const char str[1096] = "";
    const char fstr[1096] = "%o";
    uint32_t res1 = s21_sscanf(str, fstr, &a1);
    uint32_t res2 = sscanf(str, fstr, &a2);

    ck_assert_int_eq(res1, res2);
} END_TEST

START_TEST(sscanf_octal_fail) {
    uint32_t a1, a2;
    const char str[1096] = "q1";
    const char fstr[1096] = "%o";
    uint32_t res1 = s21_sscanf(str, fstr, &a1);
    uint32_t res2 = sscanf(str, fstr, &a2);

    ck_assert_int_eq(res1, res2);
} END_TEST

START_TEST(sscanf_octal_spaces_tabs_sns) {
    uint32_t a1, a2;
    const char str[1096] = "          \n             \n     5";
    const char fstr[1096] = "%o";
    uint32_t res1 = s21_sscanf(str, fstr, &a1);
    uint32_t res2 = sscanf(str, fstr, &a2);

    ck_assert_int_eq(res1, res2);
    ck_assert_int_eq(a1, a2);
} END_TEST

START_TEST(sscanf_octal_short) {
    uint16_t a1, a2;
    const char str[1096] = "12";
    const char fstr[1096] = "%ho";
    uint16_t res1 = s21_sscanf(str, fstr, &a1);
    uint16_t res2 = sscanf(str, fstr, &a2);

    ck_assert_int_eq(res1, res2);
    ck_assert_int_eq(a1, a2);
} END_TEST

START_TEST(sscanf_octal_long) {
    unsigned long int a1, a2;
    const char str[1096] = "57234";
    const char fstr[1096] = "%lo";
    uint16_t res1 = s21_sscanf(str, fstr, &a1);
    uint16_t res2 = sscanf(str, fstr, &a2);

    ck_assert_int_eq(res1, res2);
    ck_assert_int_eq(a1, a2);
} END_TEST

START_TEST(sscanf_octal_longlong) {
    unsigned long long int a1, a2;
    const char str[1096] = "12356226137";
    const char fstr[1096] = "%llo";
    uint16_t res1 = s21_sscanf(str, fstr, &a1);
    uint16_t res2 = sscanf(str, fstr, &a2);

    ck_assert_int_eq(res1, res2);
    ck_assert_int_eq(a1, a2);
} END_TEST

START_TEST(sscanf_octal_2x) {
    uint32_t a1, a2;
    const char str[1096] = "0x12320x213x123213";
    const char fstr[1096] = "%o";
    uint32_t res1 = s21_sscanf(str, fstr, &a1);
    uint32_t res2 = sscanf(str, fstr, &a2);

    ck_assert_int_eq(res1, res2);
    ck_assert_int_eq(a1, a2);
} END_TEST

START_TEST(sscanf_octal_star) {
    const char str[1096] = "521561612";
    const char fstr[1096] = "%*o";
    uint32_t res1 = s21_sscanf(str, fstr);
    uint32_t res2 = sscanf(str, fstr);

    ck_assert_int_eq(res1, res2);
} END_TEST

START_TEST(sscanf_octal_nohex) {
    uint32_t a1, a2;
    const char str[1096] = "tqwqpl";
    const char fstr[1096] = "%o";
    uint32_t res1 = s21_sscanf(str, fstr, &a1);
    uint32_t res2 = sscanf(str, fstr, &a2);

    ck_assert_int_eq(res1, res2);
} END_TEST

START_TEST(sscanf_octal_lower) {
    uint32_t a1, a2;
    const char str[1096] = "01234567";
    const char fstr[1096] = "%o";
    uint32_t res1 = s21_sscanf(str, fstr, &a1);
    uint32_t res2 = sscanf(str, fstr, &a2);

    ck_assert_int_eq(res1, res2);
    ck_assert_int_eq(a1, a2);
} END_TEST

START_TEST(sscanf_octal_sign) {
    uint32_t a1, a2;
    const char str[1096] = "-66";
    const char fstr[1096] = "%o";
    uint32_t res1 = s21_sscanf(str, fstr, &a1);
    uint32_t res2 = sscanf(str, fstr, &a2);

    ck_assert_int_eq(res1, res2);
    ck_assert_int_eq(a1, a2);
} END_TEST

START_TEST(sscanf_octal_len) {
    uint32_t a1, a2;
    const char str[1096] = "123531";
    const char fstr[1096] = "%2o";
    uint32_t res1 = s21_sscanf(str, fstr, &a1);
    uint32_t res2 = sscanf(str, fstr, &a2);

    ck_assert_int_eq(res1, res2);
    ck_assert_int_eq(a1, a2);
} END_TEST

START_TEST(sscanf_buff1) {
    int32_t a1, a2;
    int32_t b1, b2;
    const char str[1096] = "12 keppa 12";
    const char fstr[1096] = "%d keppa %d";
    int32_t res1 = s21_sscanf(str, fstr, &a1, &b1);
    int32_t res2 = sscanf(str, fstr, &a2, &b2);

    ck_assert_int_eq(res1, res2);
    ck_assert_int_eq(a1, a2);
    ck_assert_int_eq(b1, b2);
} END_TEST

START_TEST(sscanf_buff2) {
    int32_t a1, a2;
    int32_t b1, b2;
    const char str[1096] = "12keppa12";
    const char fstr[1096] = "%dkeppa%d";
    int32_t res1 = s21_sscanf(str, fstr, &a1, &b1);
    int32_t res2 = sscanf(str, fstr, &a2, &b2);

    ck_assert_int_eq(res1, res2);
    ck_assert_int_eq(a1, a2);
    ck_assert_int_eq(b1, b2);
} END_TEST

START_TEST(sscanf_pointer1) {
    int *a1 = 0, *a2 = 0, *b1 = 0, *b2 = 0, *c1 = 0, *c2 = 0, *d1 = 0, *d2 = 0;
    const char str[1096] = "0xFFFF 0xAAAA 0x7123 0xBBC1FF";
    const char fstr[1096] = "%p %p %p %p";

    int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
    int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

    ck_assert_int_eq(res1, res2);
    ck_assert_ptr_eq(a1, a2);
    ck_assert_ptr_eq(b1, b2);
    ck_assert_ptr_eq(c1, c2);
    ck_assert_ptr_eq(d1, d2);
} END_TEST

START_TEST(sscanf_pointer2) {
    int *a1 = 0, *a2 = 0, *b1 = 0, *b2 = 0, *c1 = 0, *c2 = 0, *d1 = 0, *d2 = 0;
    const char str[1096] = "0xFFFF 0xAAAA 0x7123 0xBBC1FF";
    const char fstr[1096] = "%p %p %p %p";

    int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
    int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

    ck_assert_int_eq(res1, res2);
    ck_assert_ptr_eq(a1, a2);
    ck_assert_ptr_eq(b1, b2);
    ck_assert_ptr_eq(c1, c2);
    ck_assert_ptr_eq(d1, d2);
} END_TEST

START_TEST(sscanf_pointer3) {
    int *a1 = 0, *a2 = 0, *b1 = 0, *b2 = 0, *c1 = 0, *c2 = 0, *d1 = 0, *d2 = 0;
    const char str[1096] = "0xFFFF 0xAAAA 0x7123 0xBBC1FF";
    const char fstr[1096] = "%p %p %p %p";

    int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
    int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

    ck_assert_int_eq(res1, res2);
    ck_assert_ptr_eq(a1, a2);
    ck_assert_ptr_eq(b1, b2);
    ck_assert_ptr_eq(c1, c2);
    ck_assert_ptr_eq(d1, d2);
} END_TEST

START_TEST(sscanf_pointer4) {
    int *a1 = 0, *a2 = 0, *b1 = 0, *b2 = 0, *c1 = 0, *c2 = 0, *d1 = 0, *d2 = 0;
    const char str[1096] = "0xFFFF 0xAAAA 0x7123 0xBBC1FF";
    const char fstr[1096] = "%p %p %p %p";

    int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
    int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

    ck_assert_int_eq(res1, res2);
    ck_assert_ptr_eq(a1, a2);
    ck_assert_ptr_eq(b1, b2);
    ck_assert_ptr_eq(c1, c2);
    ck_assert_ptr_eq(d1, d2);
} END_TEST

START_TEST(sscanf_hard1) {
    int a1 = 0, a2 = 5, a3 = 3, a4 = 9;
    int32_t n1 = 500, n2 = 10000;

    const char str[1096] = "123123SkipMePlease!!!!123";
    const char fstr[1096] = "%dSkipMePlease!!!!%d %n";

    int16_t res1 = s21_sscanf(str, fstr, &a1, &a3, &n1);
    int16_t res2 = sscanf(str, fstr, &a2, &a4, &n2);

    ck_assert_int_eq(res1, res2);
    ck_assert_int_eq(n1, n2);
    ck_assert_int_eq(a3, a4);
    ck_assert_int_eq(n1, n2);
} END_TEST

START_TEST(sscanf_buff3) {
    int32_t a1, a2;
    int32_t b1 = 0, b2 = 0;
    const char str[1096] = "12keppa12";
    const char fstr[1096] = "%dkeppapos%d";
    int32_t res1 = s21_sscanf(str, fstr, &a1, &b1);
    int32_t res2 = sscanf(str, fstr, &a2, &b2);

    ck_assert_int_eq(res1, res2);
    ck_assert_int_eq(a1, a2);
    ck_assert_int_eq(b1, b2);
} END_TEST

START_TEST(sscanf_perc1) {
    int32_t a1, a2;
    int32_t b1 = 80, b2 = 33;
    int32_t c1 = 55, c2 = 33;
    const char str[1096] = "12 % 13 % 14";
    const char fstr[1096] = "%d %% %d %% %d";
    int32_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1);
    int32_t res2 = sscanf(str, fstr, &a2, &b2, &c2);

    ck_assert_int_eq(res1, res2);
    ck_assert_int_eq(a1, a2);
    ck_assert_int_eq(b1, b2);
    ck_assert_int_eq(c1, c2);
} END_TEST

START_TEST(sscanf_perc2) {
    int32_t a1, a2;
    int32_t b1 = 80, b2 = 33;
    int32_t c1 = 55, c2 = 33;
    const char str[1096] = "12%13%14";
    const char fstr[1096] = "%d%%%d%%%d";
    int32_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1);
    int32_t res2 = sscanf(str, fstr, &a2, &b2, &c2);

    ck_assert_int_eq(res1, res2);
    ck_assert_int_eq(a1, a2);
    ck_assert_int_eq(b1, b2);
    ck_assert_int_eq(c1, c2);
} END_TEST

START_TEST(sscanf_perc3) {
    int32_t a1 = 1234, a2 = 33333;

    const char str[1096] = "%%%16";
    const char fstr[1096] = "%%%%%%%d";
    int32_t res1 = s21_sscanf(str, fstr, &a1);
    int32_t res2 = sscanf(str, fstr, &a2);

    ck_assert_int_eq(res1, res2);
    ck_assert_int_eq(a1, a2);
} END_TEST

START_TEST(sscanf_perc4) {
    const char str[1096] = "%%%";
    const char fstr[1096] = "%%%%%%";
    int32_t res1 = s21_sscanf(str, fstr);
    int32_t res2 = sscanf(str, fstr);

    ck_assert_int_eq(res1, res2);
} END_TEST

START_TEST(sscanf_perc5) {
    int32_t a1 = 1234, a2 = 33333;
    int32_t b1 = 1234, b2 = 33333;

    const char str[1096] = "%%123%888";
    const char fstr[1096] = "%%%%%d%%%d";
    int32_t res1 = s21_sscanf(str, fstr, &a1, &b1);
    int32_t res2 = sscanf(str, fstr, &a2, &b2);

    ck_assert_int_eq(res1, res2);
    ck_assert_int_eq(a1, a2);
    ck_assert_int_eq(b1, b2);
} END_TEST

START_TEST(sscanf_mixed_ptrs1) {
    int *a1 = 0, *a2 = 0, *b1 = 0, *b2 = 0, *c1 = 0, *c2 = 0, *d1 = 0, *d2 = 0;

    const char str[1096] = "0xFFFF 0xAAA 7123 0xBBC1FF";
    const char fstr[1096] = "%p %p %p %p";

    int32_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
    int32_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

    ck_assert_int_eq(res1, res2);
    ck_assert_ptr_eq(a1, a2);
    ck_assert_ptr_eq(b1, b2);
    ck_assert_ptr_eq(c1, c2);
    ck_assert_ptr_eq(d1, d2);
} END_TEST

START_TEST(sscanf_mixed_ptrs2) {
    char *a1 = 0, *a2 = 0, *b1 = 0, *b2 = 0, *c1 = 0, *c2 = 0, *d1 = 0, *d2 = 0;

    const char str[1096] = "0x4 0x3 0x2 0x1";
    const char fstr[1096] = "%p %p %p %p";

    int32_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
    int32_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

    ck_assert_int_eq(res1, res2);
    ck_assert_ptr_eq(a1, a2);
    ck_assert_ptr_eq(b1, b2);
    ck_assert_ptr_eq(c1, c2);
    ck_assert_ptr_eq(d1, d2);
} END_TEST

START_TEST(sscanf_mixed_ptrs3) {
    int *a1 = 0, *a2 = 0, *b1 = 0, *b2 = 0, *c1 = 0, *c2 = 0, *d1 = 0, *d2 = 0;

    const char str[1096] = "03033 0333 0123 0123 0x123 0xFFFFF 0xBBC1FF";
    const char fstr[1096] = "%p %p %p %p";

    int32_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
    int32_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

    ck_assert_int_eq(res1, res2);
    ck_assert_ptr_eq(a1, a2);
    ck_assert_ptr_eq(b1, b2);
    ck_assert_ptr_eq(c1, c2);
    ck_assert_ptr_eq(d1, d2);
} END_TEST

START_TEST(sscanf_mixed_ptrs4) {
    int *a1 = 0, *a2 = 0, *b1 = 0, *b2 = 0, *c1 = 0, *c2 = 0, *d1 = 0, *d2 = 0;

    const char str[1096] = "0xABCDEF 0xAAA 7123 0xBBC1FF";
    const char fstr[1096] = "%p %p %p %p";

    int32_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
    int32_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

    ck_assert_int_eq(res1, res2);
    ck_assert_ptr_eq(a1, a2);
    ck_assert_ptr_eq(b1, b2);
    ck_assert_ptr_eq(c1, c2);
    ck_assert_ptr_eq(d1, d2);
} END_TEST

START_TEST(sscanf_mixed_ptrs5) {
    int *a1 = 0, *a2 = 0, *b1 = 0, *b2 = 0, *c1 = 0, *c2 = 0, *d1 = 0, *d2 = 0;

    const char str[1096] = "NULL";
    const char fstr[1096] = "%p %p %p %p";

    int32_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
    int32_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

    ck_assert_int_eq(res1, res2);
    ck_assert_ptr_eq(a1, a2);
    ck_assert_ptr_eq(b1, b2);
    ck_assert_ptr_eq(c1, c2);
    ck_assert_ptr_eq(d1, d2);
} END_TEST

START_TEST(sscanf_hard3) {
    char a1, a2;
    char b1[256] = {'\0'};
    char b2[256] = {'\0'};
    float c1, c2;
    short int d1, d2;
    long long int e1, e2;

    const char str[1096] = "$AmIIn%%sane? %\n\n\n \n \n \n\t   InF 0 %FIN9D-ME%";
    const char fstr[1096] = "%c%5s%%%*s %%  %G %hi %%FIN%lldDME%%";

    int32_t res1 = s21_sscanf(str, fstr, &a1, b1, &c1, &d1, &e1);
    int32_t res2 = sscanf(str, fstr, &a2, b2, &c2, &d2, &e2);

    ck_assert_int_eq(res1, res2);
    ck_assert_int_eq(a1, a2);
    ck_assert_str_eq(b1, b2);
    ck_assert_float_infinite(c1);
    ck_assert_float_infinite(c2);
    ck_assert_int_eq(d1, d2);
    ck_assert_int_eq(e1, e2);
} END_TEST

START_TEST(sscanf_hard4) {
    char a1, a2;
    char b1, b2;
    char c1, c2;
    char d1, d2;

    const char str[1096] = "%%$Char!StressssT%%estus!&&&";
    const char fstr[1096] = "%% %*c%*c%*c%*c%*c %c %c %c %c ### %*c";

    int32_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
    int32_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

    ck_assert_int_eq(res1, res2);
    ck_assert_int_eq(a1, a2);
    ck_assert_int_eq(b1, b2);
    ck_assert_int_eq(c1, c2);
    ck_assert_int_eq(d1, d2);
} END_TEST

START_TEST(sscanf_hard5) {
    char a1, a2;
    char b1, b2;
    char c1, c2;
    char d1, d2;
    const char str[1096] = "%%$Char!StressssVIm User Aboba %% %%% %%% %% % % %% % "
                       "% % %% % % %% %T%%estus!%%&&&";
    const char fstr[1096] = "%% %*c%*c%*c%*c%*c %c %c %c %c %% %% %% %% %% %% %% "
                        "%% %% %% %% %% %% %% %% %% ### %*c";

    int32_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
    int32_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

    ck_assert_int_eq(res1, res2);
    ck_assert_int_eq(a1, a2);
    ck_assert_int_eq(b1, b2);
    ck_assert_int_eq(c1, c2);
} END_TEST

Suite *suite_s21_sscanf() {
    Suite *s = suite_create("s21_sscanf");
    TCase *tc = tcase_create("test_sscanf");
    
    suite_add_tcase(s, tc);


  tcase_add_test(tc, sscanf1);
  tcase_add_test(tc, sscanf2);
  tcase_add_test(tc, sscanf3);
  tcase_add_test(tc, sscanf4);
  tcase_add_test(tc, sscanf5);
  tcase_add_test(tc, sscanf6);
  tcase_add_test(tc, sscanf7);
  tcase_add_test(tc, sscanf8);
  tcase_add_test(tc, sscanf9);
  tcase_add_test(tc, sscanf10);
  tcase_add_test(tc, sscanf11);
  tcase_add_test(tc, sscanf12);
  tcase_add_test(tc, sscanf13);
  tcase_add_test(tc, sscanf14);
  tcase_add_test(tc, sscanf15);
  tcase_add_test(tc, sscanf16);
  tcase_add_test(tc, sscanf17);
  tcase_add_test(tc, sscanf18);
  tcase_add_test(tc, sscanf19);
  tcase_add_test(tc, sscanf20);
  tcase_add_test(tc, sscanf21);
  tcase_add_test(tc, sscanf22);
  tcase_add_test(tc, sscanf23);
  tcase_add_test(tc, sscanf24);
  tcase_add_test(tc, sscanf25);
    tcase_add_test(tc, sscanf_EOF1);
    tcase_add_test(tc, sscanf_EOF2);
    tcase_add_test(tc, sscanf_EOF3);
    tcase_add_test(tc, sscanf_only_chars1);
    tcase_add_test(tc, sscanf_only_chars2);
    tcase_add_test(tc, sscanf_only_chars3);
    tcase_add_test(tc, sscanf_only_chars4);
    tcase_add_test(tc, sscanf_only_chars5);
    tcase_add_test(tc, sscanf_special_symbols_as_chars1);
    tcase_add_test(tc, sscanf_special_symbols_as_chars2);
    tcase_add_test(tc, sscanf_special_symbols_as_chars3);
    tcase_add_test(tc, sscanf_chars_flags1);  
    tcase_add_test(tc, sscanf_chars_flags2);  
    tcase_add_test(tc, sscanf_chars_flags3);  
    tcase_add_test(tc, sscanf_chars_flags4);  
    tcase_add_test(tc, sscanf_chars_flags5);  
    tcase_add_test(tc, sscanf_chars_aster1);
    tcase_add_test(tc, sscanf_chars_aster2);
    tcase_add_test(tc, sscanf_only_ints1);
    tcase_add_test(tc, sscanf_only_ints2);
    tcase_add_test(tc, sscanf_only_ints3);
    tcase_add_test(tc, sscanf_ints_nwidth1);
    tcase_add_test(tc, sscanf_ints_nwidth2);
    tcase_add_test(tc, sscanf_ints_nwidth3);
    tcase_add_test(tc, sscanf_ints_nwidth4);
    tcase_add_test(tc, sscanf_ints_astwidth1);
    tcase_add_test(tc, sscanf_ints_astwidth2);
    tcase_add_test(tc, sscanf_ints_astwidth3);
    tcase_add_test(tc, sscanf_ints_astwidth4);
    tcase_add_test(tc, sscanf_signed_ints1);
    tcase_add_test(tc, sscanf_signed_ints2);
    tcase_add_test(tc, sscanf_signed_ints3);
    tcase_add_test(tc, sscanf_signed_ints4);
    tcase_add_test(tc, sscanf_spec_i_int1);
    tcase_add_test(tc, sscanf_spec_i_int2);
    tcase_add_test(tc, sscanf_spec_i_int3);
    tcase_add_test(tc, sscanf_spec_i_int4);
    tcase_add_test(tc, sscanf_spec_i_oct1);
    tcase_add_test(tc, sscanf_spec_i_oct2);
    tcase_add_test(tc, sscanf_spec_i_hex1);
    tcase_add_test(tc, sscanf_spec_i_hex2);
    tcase_add_test(tc, sscanf_strings1);
    tcase_add_test(tc, sscanf_strings2);
    tcase_add_test(tc, sscanf_strings3);
    tcase_add_test(tc, sscanf_strings4);
    tcase_add_test(tc, sscanf_strings5);
    tcase_add_test(tc, sscanf_strings6);
    tcase_add_test(tc, sscanf_uint1);
    tcase_add_test(tc, sscanf_uint2);
    tcase_add_test(tc, sscanf_uint3);
    tcase_add_test(tc, sscanf_uint4);
    tcase_add_test(tc, sscanf_uint5);
    tcase_add_test(tc, sscanf_uint6);
    tcase_add_test(tc, sscanf_strings_mixed1);
    tcase_add_test(tc, sscanf_strings_mixed2);
    tcase_add_test(tc, sscanf_strings_mixed3);
    tcase_add_test(tc, sscanf_floats1);
    tcase_add_test(tc, sscanf_floats2);
    tcase_add_test(tc, sscanf_floats3);
    tcase_add_test(tc, sscanf_floats4);
    tcase_add_test(tc, sscanf_floats5);
    tcase_add_test(tc, sscanf_floats_sci1);
    tcase_add_test(tc, sscanf_floats_sci2);
    tcase_add_test(tc, sscanf_floats_sci3);
    tcase_add_test(tc, sscanf_floats_sci4);
    tcase_add_test(tc, sscanf_floats_sci5);
    tcase_add_test(tc, sscanf_n1);
    tcase_add_test(tc, sscanf_n2);
    tcase_add_test(tc, sscanf_n3);
    tcase_add_test(tc, sscanf_n4);
    tcase_add_test(tc, sscanf_n5);
    tcase_add_test(tc, sscanf_upeer_hex_base_version);
    tcase_add_test(tc, sscanf_upeer_hex_overflow);
    tcase_add_test(tc, sscanf_upeer_hex_0x);
    tcase_add_test(tc, sscanf_upeer_hex_0X);
    tcase_add_test(tc, sscanf_upeer_hex_empty);
    tcase_add_test(tc, sscanf_upeer_hex_fail);
    tcase_add_test(tc, sscanf_upeer_hex_spaces_tabs_sns);
    tcase_add_test(tc, sscanf_upeer_hex_short);
    tcase_add_test(tc, sscanf_upeer_hex_long);
    tcase_add_test(tc, sscanf_upeer_hex_longlong);
    tcase_add_test(tc, sscanf_upeer_hex_2x);
    tcase_add_test(tc, sscanf_upeer_hex_star);
    tcase_add_test(tc, sscanf_upeer_hex_nohex);
    tcase_add_test(tc, sscanf_upeer_hex_lower);
    tcase_add_test(tc, sscanf_upeer_hex_sign);
    tcase_add_test(tc, upper_hex_len);
    tcase_add_test(tc, sscanf_lower_hex_base_version);
    tcase_add_test(tc, sscanf_lower_hex_overflow);
    tcase_add_test(tc, sscanf_lower_hex_0x);
    tcase_add_test(tc, sscanf_lower_hex_0X);
    tcase_add_test(tc, sscanf_lower_hex_empty);
    tcase_add_test(tc, sscanf_lower_hex_fail);
    tcase_add_test(tc, sscanf_lower_hex_spaces_tabs_sns);
    tcase_add_test(tc, sscanf_lower_hex_short);
    tcase_add_test(tc, sscanf_lower_hex_long);
    tcase_add_test(tc, sscanf_lower_hex_longlong);
    tcase_add_test(tc, sscanf_lower_hex_2x);
    tcase_add_test(tc, sscanf_lower_hex_star);
    tcase_add_test(tc, sscanf_lower_hex_nohex);
    tcase_add_test(tc, sscanf_lower_hex_lower);
    tcase_add_test(tc, sscanf_lower_hex_sign);
    tcase_add_test(tc, sscanf_lower_hex_len);
    tcase_add_test(tc, sscanf_octal_base_version);
    tcase_add_test(tc, sscanf_octal_overflow);
    tcase_add_test(tc, sscanf_octal_0x);
    tcase_add_test(tc, sscanf_octal_0X);
    tcase_add_test(tc, sscanf_octal_empty);
    tcase_add_test(tc, sscanf_octal_fail);
    tcase_add_test(tc, sscanf_octal_spaces_tabs_sns);
    tcase_add_test(tc, sscanf_octal_short);
    tcase_add_test(tc, sscanf_octal_long);
    tcase_add_test(tc, sscanf_octal_longlong);
    tcase_add_test(tc, sscanf_octal_2x);
    tcase_add_test(tc, sscanf_octal_star);
    tcase_add_test(tc, sscanf_octal_nohex);
    tcase_add_test(tc, sscanf_octal_lower);
    tcase_add_test(tc, sscanf_octal_sign);
    tcase_add_test(tc, sscanf_octal_len);
    tcase_add_test(tc, sscanf_pointer1);
    tcase_add_test(tc, sscanf_pointer2);
    tcase_add_test(tc, sscanf_pointer3);
    tcase_add_test(tc, sscanf_pointer4);
    tcase_add_test(tc, sscanf_buff1);
    tcase_add_test(tc, sscanf_buff2);
    tcase_add_test(tc, sscanf_buff3);
    tcase_add_test(tc, sscanf_perc1);
    tcase_add_test(tc, sscanf_perc2);
    tcase_add_test(tc, sscanf_perc3);
    tcase_add_test(tc, sscanf_perc4);
    tcase_add_test(tc, sscanf_perc5);
    tcase_add_test(tc, sscanf_mixed_ptrs1);
    tcase_add_test(tc, sscanf_mixed_ptrs2);
    tcase_add_test(tc, sscanf_mixed_ptrs3);
    tcase_add_test(tc, sscanf_mixed_ptrs4);
    tcase_add_test(tc, sscanf_mixed_ptrs5);
    tcase_add_test(tc, sscanf_hard1);
    tcase_add_test(tc, sscanf_hard3);
    tcase_add_test(tc, sscanf_hard4);
    tcase_add_test(tc, sscanf_hard5);

  
    return s;
}
