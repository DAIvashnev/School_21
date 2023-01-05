#include "s21_math.h"

// 1 Вычисляет абсолютное значение целого числа.
int s21_abs(int x) { return x < 0 ? x * -1 : x; }

// 2 Вычисляет арккосинус, по отношению к артангенсу.
long double s21_acos(double x) {
  long double res = 0;
  if (x < 1 && x > -1) {
    res = s21_PI / 2 - s21_asin(x);
  } else if (x == 1) {
    res = 0;
  } else if (x == -1) {
    res = s21_PI;
  } else {
    res = s21_NAN;
  }
  return res;
}

// 3 Вычисляет арксинус. Ряд Маклорена.
long double s21_asin(double x) {
  int metka = 0;
  if (x < 0 && x != -1) {
    x = x * -1;
    metka = 1;
  }
  long double n = 1, a = x, s = 1, res = x;
  if (x < 1 && x > -1) {
    while (s > s21_E) {
      a = x * x * (a * (2 * n - 1)) / (2 * n);
      s = a / (2 * n + 1);
      res = res + s;
      n++;
    }
    if (metka == 1) {
      res = res * -1;
    }
  } else if (x == 1) {
    res = s21_PI / 2;
  } else if (x == -1) {
    res = -s21_PI / 2;
  } else if (x == 0) {
    res = 0;
  } else {
    res = s21_NAN;
  }
  return res;
}

// 4 Вычисляет арктангенс, по отношению к арксинусу.
long double s21_atan(double x) { return s21_asin(x / s21_sqrt(1 + (x * x))); }

// 5 Возвращает ближайшее целое число, не меньшее заданного значения.
long double s21_ceil(double x) {
  long double a = x;
  return a - (long long int)x > 0 ? a - (a - (long long int)x) + 1
                                  : a - (a - (long long int)x);
}

// 6 Вычисляет косинус.
long double s21_cos(double x) {
  if (s21_fabs(x) <= 0.000001) x = 0.0;
  round_to_pi(&x);
  long double res = 1.0, n = 1.0, an = 1.0;
  while (!(an >= -s21_E && an <= s21_E)) {
    an *= (-1.0) * x * x / ((2.0 * n - 1.0) * (2.0 * n));
    res += an;
    n++;
  }
  return res;
}

// 7 Возвращает значение e, возведенное в заданную степень.
long double s21_exp(double x) {
  long double res, t;
  long double a = x;
  int znak = 0;
  if (a < 0) {
    a = -a;
    znak = -1;
  }
  int n = 1;
  for (res = 1.0, t = 1.0; s21_fabs(t) > s21_E; n++) {
    t *= a / n;
    res += t;
    if (res > s21_MAX_double) {
      res = s21_INF;
      break;
    }
  }
  return res != s21_INF ? znak == -1 ? 1 / res : res : s21_INF;
}

// 8 Вычисляет абсолютное значение числа с плавающей точкой.
long double s21_fabs(double x) { return x < 0.0 ? x * -1.0 : x; }

// 9 Возвращает ближайшее целое число, не превышающее заданное значение.
long double s21_floor(double x) {
  long double a = x;
  return a - (int)a > 0 ? a - (a - (int)a) : a - (int)a < 0 ? (int)a - 1 : a;
}

// 10 Остаток операции деления с плавающей точкой.
long double s21_fmod(double x, double y) {
  int metka_a = 0, metka_b = 0;
  if (x < 0) {
    metka_a = 1;
  }
  if (y < 0) {
    metka_b = 1;
  }
  if (metka_b == 1) {
    y = y * (-1);
  }
  if (metka_a == 1) {
    x = x * (-1);
  }
  double n = s21_floor(x / y);
  double result = x - n * y;
  if (metka_a == 1) {
    result = result * (-1);
  }
  return result;
}

// 11 Вычисляет натуральный логарифм.
long double s21_log(double x) {
  long double result;
  if (x == 1)
    result = 0;
  else if (x == 0)
    result = -s21_INF;
  else if (x < 0) {
    result = s21_NAN;
  } else {
    if (x > 0 && x < 1) {
      result = p_log(x);
    } else {
      long double res = 0.0, term = (x - 1) / x;
      long long denominator = 2;
      long double temp = term;
      unsigned int count = 0;
      while (temp > s21_E) {
        res += temp;
        term *= (x - 1) / x;

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

// 13 Вычисляет синус. Ряд Тейлора + ряд Маклорена.
long double s21_sin(double x) {
  if (s21_fabs(x) <= 0.000001) x = 0.0;
  round_to_pi(&x);
  long double res = 0.0, n = 0.0, an = 1.0;
  while (!(an >= -s21_E && an <= s21_E)) {
    an = s21_pow(-1, n) * s21_pow(x, 2 * n + 1) / s21_factorial(2 * n + 1);
    res += an;
    n++;
  }
  return res;
}

// 14 Вычисляет квадратный корень, методом Ньютона.
long double s21_sqrt(double x) {
  double t = 0, sqrt = x / 2;
  if (x > 0) {
    while ((t - sqrt) != 0) {
      t = sqrt;
      sqrt = (t + (x / t)) / 2;
    }
  }
  return x < 0 ? s21_NAN : sqrt;
}

// 15 Вычисляет тангенс. По формуле.
long double s21_tan(double x) { return s21_sin(x) / s21_cos(x); }

// Факториал числа.
long double s21_factorial(double x) {
  return (x < 2) ? 1 : x * s21_factorial(x - 1);
}

long double p_log(double x) {
  x--;
  long double r = x, t = x;
  long double i = 2;
  while (s21_fabs(r) > s21_E) {
    r *= -x * (i - 1) / i;
    i += 1;
    t += r;
  }
  return t;
}

void round_to_pi(double *x) {
  while (s21_fabs(*x) > (2.0 * s21_PI)) {
    if (*x < 0)
      *x = *x + (2.0 * s21_PI);
    else
      *x = *x - (2.0 * s21_PI);
  }
}
