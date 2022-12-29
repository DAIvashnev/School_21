#include "s21_math.h"
#include <math.h>

// 1 Вычисляет абсолютное значение целого числа.
int s21_abs(int x) {
    return x < 0 ? x * -1 : x;
}
/*
// 2 Вычисляет арккосинус.
long double s21_acos(double x) {

}

// 3 Вычисляет арксинус.
long double s21_asin(double x) {

}

// 4 Вычисляет арктангенс.
long double s21_atan(double x) {

}
*/
// 5 Возвращает ближайшее целое число, не меньшее заданного значения.
long double s21_ceil(double a) {
    long double x = a;
    return x - (long long int)a > 0 ? x - (x - (long long int)a) + 1 : x - (x - (long long int)a);
}
/*
// 6 Вычисляет косинус.
long double s21_cos(double x) {

}
*/
// 7 Возвращает значение e, возведенное в заданную степень.
long double s21_exp(double a) {
    long double res, t;
    long double b = a;
    int znak = 0;
    if (b < 0) {
        b = -b;
        znak = -1;
    }
    int n = 1;
    for (res = 1.0, t = 1.0; s21_fabs(t) > s21_E; n++) {
        t *= b / n;
        res += t;
        if (res > s21_MAX_double) {
            res = s21_INF;
            break;
        }
    }
    return res != s21_INF ? znak == -1 ? 1 / res : res : s21_INF;
}

// 8 Вычисляет абсолютное значение числа с плавающей точкой.
long double s21_fabs(double x) {
    return x < 0.0 ? x * -1 : x;
}

// 9 Возвращает ближайшее целое число, не превышающее заданное значение.
long double s21_floor(double x) {
    long double a = x;
    return x - (int)x > 0 ? x - (x - (int)x) : x - (int)x < 0 ? (int)x - 1 : x;
}
/*
// 10 Остаток операции деления с плавающей точкой.
long double s21_fmod(double x, double y) {

}
*/
// 11 Вычисляет натуральный логарифм.
long double s21_log(double a) {
    long double result;
    if (a == 1)
        result = 0;
    else if (a == 0)
        result = -s21_INF;
    else if (a < 0) {
        result = s21_NAN;
    } else {
        if (a > 0 && a < 1) {
        result = p_log(a);
        } else {
            long double res = 0.0, term = (a - 1) / a;
            long long denominator = 2;
            long double temp = term;
            unsigned int count = 0;
            while (temp > s21_E) {
                res += temp;
                term *= (a - 1) / a;
            
                temp = term * (1.0 / denominator);
                denominator += 1;
                count++;
            }
            result = res;
        }
    }
    return result;
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
long double s21_sin(double a) {
    if (s21_fabs(a) <= 0.000001) a = 0.0;
    round_to_pi(&a);
    long double res = 0.0, n = 0.0, an = 1.0;
    while (!(an >= -s21_E && an <= s21_E)) {
        an = s21_pow(-1, n) * s21_pow(a, 2 * n + 1) / s21_factorial(2 * n + 1);
        res += an;
        n++;
    }
    return res;
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
/*
// 15 Вычисляет тангенс.
long double s21_tan(double x) {

}
*/
// Факториал числа.
int s21_factorial(int n) {
    return (n < 2) ? 1 : n * s21_factorial(n - 1);
}

long double p_log(double a) {
  a--;
  long double r = a, t = a;
  long double i = 2;
  while (s21_fabs(r) > s21_E) {
    r *= -a * (i - 1) / i;
    i += 1;
    t += r;
  }
  return t;
}

void round_to_pi(double *a) {
  while (s21_fabs(*a) > (2.0 * s21_PI)) {
    if (*a < 0)
      *a = *a + (2.0 * s21_PI);
    else
      *a = *a - (2.0 * s21_PI);
  }
}