#include "s21_math.h"

#define s21_NAN 0.0 / 0.0
#define s21_INF 1.0 / 0.0

// 1 Вычисляет абсолютное значение целого числа.
int s21_abs(int x) {

}

// 2 Вычисляет арккосинус.
long double s21_acos(double x) {

}

// 3 Вычисляет арксинус.
long double s21_asin(double x) {

}

// 4 Вычисляет арктангенс.
long double s21_atan(double x) {

}

// 5 Возвращает ближайшее целое число, не меньшее заданного значения.
long double s21_ceil(double x) {

}

// 6 Вычисляет косинус.
long double s21_cos(double x) {

}

// 7 Возвращает значение e, возведенное в заданную степень.
long double s21_exp(double x) {

}

// 8 Вычисляет абсолютное значение числа с плавающей точкой.
long double s21_fabs(double x) {

}

// 9 Возвращает ближайшее целое число, не превышающее заданное значение.
long double s21_floor(double x) {

}

// 10 Остаток операции деления с плавающей точкой.
long double s21_fmod(double x, double y) {

}

// 11 Вычисляет натуральный логарифм.
long double s21_log(double x) {

}

// 12 Возводит число в заданную степень.
long double s21_pow(double base, double exp) {
    long double znak = 1.0;
    long double x = base;
    long double y = exp;
    if (x < 0 && y == (int)y) {
        x = -x;
        znak = -1.0;
        if ((int)y % 2 == 0) znak *= -1.0;
    }
    return y == 0 ? 1 : x == 0 ? 0 : znak * s21_exp(y * s21_log(x));
}

// 13 Вычисляет синус.
long double s21_sin(double x) {

}

// 14 Вычисляет квадратный корень.
long double s21_sqrt(double a) { 
    double t = 0, sqrt = a / 2;
    if (a > 0) {
        while ((t - sqrt) != 0) {
            t = sqrt;
            sqrt = (t + (a / t)) / 2;
        }
    }
    return a < 0 ? s21_NAN : sqrt;
}

// 15 Вычисляет тангенс.
long double s21_tan(double x) {

}

// Факториал числа.
int s21_facto(int n) {
    return (n < 2) ? 1 : n * factorial (n - 1);
}