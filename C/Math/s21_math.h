#ifndef SRC_S21_MATH_H_
#define SRC_S21_MATH_H_

#include <stdlib.h>

#include "stdio.h"

#define S21_PI 3.141592653589793
#define S21_NAN 0.0 / 0.0
#define S21_INFINITY 1.0 / 0.0
#define S21_E 2.718281828459045235

// ======================= ADDITIONAL FUNCTIONS ========================
long double s21_factorial(long double x);
int is_NAN(double x);
long double int_degree_of_x(double x, double n);

// =========================  MAIN FUNCTIONS ===========================
int s21_abs(int x);                        // 1 модуль
long double s21_acos(double x);            // 2 арккосинус
long double s21_asin(double x);            // 3 арксинус
long double s21_atan(double x);            // 4 арктангенс
long double s21_ceil(double x);            // 5 округление вверх
long double s21_cos(double x);             // 6 косинус
long double s21_exp(double x);             // 7 e, в степени
long double s21_fabs(double x);            // 8 модуль
long double s21_floor(double x);           // 9 округление
long double s21_fmod(double x, double y);  // 10 остаток деления
long double s21_log(double x);             // 11 логарифм
long double s21_pow(double base, double exp);  // 12 число в степень
long double s21_sin(double x);                 // 13 синус
long double s21_sqrt(double x);  // 14 квадратный корень
long double s21_tan(double x);   // 15 тангенс

#endif  // SRC_S21_MATH_H_
