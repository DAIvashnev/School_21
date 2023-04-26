#include "s21_math.h"

// ======================= ADDITIONAL FUNCTIONS ========================
long double s21_factorial(long double x) {
  long double res = 1.0;

  if (x < 0) {
    res = 0;
  } else if (x == 0) {
    res = 1.0;
  } else {
    for (int i = 1; i <= x; i++) {
      res = res * i;
    }
  }
  return res;
}

int is_NAN(double x) {
  int res = !(x == x);
  return res;
}

long double int_degree_of_x(double x, double n) {
  // возведение x в целую степень
  // хорошо бы сделать проверку n на целое число через остаток от деления = 0
  long double pow = x;
  if (n == 0) {
    pow = 1;
  } else {
    while (n > 1) {
      pow = pow * x;
      n--;
    }
  }
  return pow;
}

// =========================  MAIN FUNCTIONS ===========================
int s21_abs(int x) { return x > 0 ? x : (-x); }

long double s21_acos(double x) {
  long double res = 0;
  if (x == 0) {
    res = S21_PI / 2;
  } else if (x == 1) {
    res = 0;
  } else if (x == -1) {
    res = S21_PI;
  } else if (x < 1 && x > -1) {
    res = S21_PI / 2 - s21_asin(x);
  } else {
    res = S21_NAN;
  }
  return res;
}

long double s21_asin(double x) {
  int sign = 0;
  if (x < 0 && x != -1) {
    x = x * -1;
    sign = 1;
  }
  long double res = x;
  long double res_prom = 1;
  long double prom = x;
  long double i = 1;

  if (x == 0) {
    res = 0;
  } else if (x == 1) {
    res = S21_PI / 2;
  } else if (x == -1) {
    res = -S21_PI / 2;
  } else if (x < 1 && x > -1) {
    while (res_prom > 1.0e-17) {
      prom = x * x * (prom * (2 * i - 1)) / (2 * i);
      res_prom = prom / (2 * i + 1);
      res = res + res_prom;
      i++;
    }
    if (sign == 1) {
      res = res * -1;
    }
  } else {
    res = S21_NAN;
  }
  return res;
}

long double s21_atan(double x) {
  long double res = 0;
  if (x == S21_INFINITY) {
    res = S21_PI / 2;
  } else if (x == -S21_INFINITY) {
    res = -S21_PI / 2;
  } else if (is_NAN(x)) {
    res = S21_NAN;
  } else {
    res = s21_asin(x / s21_sqrt(1 + (x * x)));
  }
  return res;
}

long double s21_ceil(double x) {
  long double res = 0;

  if (is_NAN(x)) {
    res = S21_NAN;
  } else if (x == S21_INFINITY) {
    res = S21_INFINITY;
  } else if (x == -S21_INFINITY) {
    res = -S21_INFINITY;
  } else {
    // к целочисленному типу, чтоб избавиться от дроби
    if (x < 0) {
      res = (long long)x;
    } else {
      if (x == (long long)x) {
        res = (long long)x;
      } else {
        res = (long long)(x + 1);
      }
    }
  }
  return res;
}

long double s21_cos(double x) {
  long double res = 0;

  if (x == S21_INFINITY || x == -S21_INFINITY || is_NAN(x)) {
    res = S21_NAN;
  } else {
    // подведем под интервал -2пи до 2пи
    x = s21_fmod(x, 2 * S21_PI);
    // вычислим по ряду Тейора
    long double res_prom = 1;
    int i = 0;
    while (s21_fabs(res_prom) > 1.0e-17) {
      res_prom =
          ((s21_pow(-1, i) * s21_pow(x, 2 * i)) / (s21_factorial(2 * i)));
      res = res + res_prom;
      i++;
    }
  }
  return res;
}

long double s21_exp(double x) {
  double n = 0;
  long double a = 0;
  long double b = 0;
  long double iter = 1;
  long double exp = 0;
  int neg_fl = 0;

  // проверка начального x
  if (x == S21_INFINITY) {
    exp = S21_INFINITY;
  } else if (x == -S21_INFINITY) {
    exp = 0;
  } else if (is_NAN(x)) {
    exp = S21_NAN;
  } else {
    if (x < 0) {
      neg_fl = 1;
      x = -x;
    }
    while (iter > 1.0e-17) {
      a = int_degree_of_x(x, n);
      b = s21_factorial(n);
      iter = a / b;
      n++;
      exp = exp + iter;
      if (a == S21_INFINITY || b == S21_INFINITY || exp == S21_INFINITY) {
        exp = S21_INFINITY;
        break;
      }
    }
    if (neg_fl == 1) exp = 1 / exp;
  }
  return exp;
}

long double s21_fabs(double x) { return x >= 0 ? x : (-x); }

long double s21_floor(double x) {
  long double res = 0;
  if (is_NAN(x)) {
    res = S21_NAN;
  } else if (x == S21_INFINITY) {
    res = S21_INFINITY;
  } else if (x == -S21_INFINITY) {
    res = -S21_INFINITY;
  } else {
    if (x < 0) {
      if (x == (long long)x) {
        res = (long long)x;
      } else {
        x = x - 1;
        res = (long long)x;
      }
    } else {
      res = (long long)x;
    }
  }
  return res;
}

long double s21_fmod(double x, double y) {
  long double res;

  if (x == S21_INFINITY || x == -S21_INFINITY || is_NAN(x)) {
    res = S21_NAN;
  } else if (x == 0 && y == 0) {
    res = S21_NAN;
  } else if (x == 0 && (y == -S21_INFINITY || y == S21_INFINITY)) {
    res = 0;
  } else if (y == S21_INFINITY || y == -S21_INFINITY) {
    res = x;
  } else if (y == 0) {
    res = S21_NAN;
  } else {
    // x-n*y, где n – это результат деления x на y округленный в сторону нуля
    long long n = (long long)(x / y);
    res = (x - (n * y));
  }
  return res;
}

long double s21_log(double x) {
  long double res = 0.0;
  long double iter = 1;
  long double log = 0;
  double EPS = 1.0e-10;

  if (x == 0) {
    res = -S21_INFINITY;
  } else if (x < 0 || x == S21_NAN || x == -S21_INFINITY) {
    res = S21_NAN;
  } else if (x == S21_INFINITY) {
    res = S21_INFINITY;
  } else {
    int e_pow = 0;  // приводим x к диапазону (0; e], e_pow степень, которую
                    // потом прибавим к результату
    while (x >= S21_E) {
      x /= S21_E;
      e_pow++;
    }

    while (s21_fabs(iter - log) > EPS) {
      iter = log;
      log = iter + 2 * ((x - s21_exp(iter)) / (x + s21_exp(iter)));
    }
    res = log + e_pow;
  }
  return res;
}

long double s21_pow(double x, double y) {
  long double res = 0;
  if (x == 1) {
    res = 1;
  } else if (y == 0) {
    res = 1;
  } else if (x == 0 && y < 0) {
    res = S21_INFINITY;
  } else if (x == 0) {
    res = 0;
  } else if (x == S21_INFINITY && y == S21_INFINITY) {
    res = S21_INFINITY;
  } else if (x == S21_INFINITY && y == -S21_INFINITY) {
    res = 0;
  } else if (x == -S21_INFINITY && y == 1) {
    res = -S21_INFINITY;
  } else if (x == -S21_INFINITY && y > 0) {
    res = S21_INFINITY;
  } else if (x == -S21_INFINITY && y < 0) {
    res = 0;
  } else if (y == 0) {
    res = 1;
  } else if (is_NAN(x)) {
    res = S21_NAN;
  } else if (y == -S21_INFINITY && s21_abs(x) > 1) {
    res = 0;
  } else if (y == -S21_INFINITY && s21_abs(x) < 1) {
    res = S21_INFINITY;
  } else if (y == S21_INFINITY && s21_abs(x) > 1) {
    res = S21_INFINITY;
  } else if (y == S21_INFINITY && s21_abs(x) < 1) {
    res = 0;
  } else {
    int neg_fl = 0;

    if (y < 0) {
      neg_fl = 1;
      y = -y;
    }
    if (s21_fmod(y, 1) == 0) {
      res = int_degree_of_x(x, y);
    } else {
      double y_int = s21_floor(y);
      double y_d = y - y_int;
      res = s21_exp(y_d * s21_log(x)) * int_degree_of_x(x, y_int);
    }
    if (neg_fl == 1) res = 1. / res;
  }
  return res;
}

long double s21_sin(double x) {
  // при x > 999999999 пропадает точность
  long double res = 0;

  if (x == S21_INFINITY || x == -S21_INFINITY || is_NAN(x)) {
    res = S21_NAN;
  } else {
    // подведем под интервал -2пи до 2пи
    x = s21_fmod(x, 2 * S21_PI);

    long double res_prom = 1;
    int i = 0;
    while (s21_fabs(res_prom) > 1.0e-16) {
      res_prom = ((s21_pow(-1, i) * s21_pow(x, 1 + (2.0 * i))) /
                  (s21_factorial(1 + (2.0 * i))));
      res = res + res_prom;
      i++;
    }
  }
  return res;
}

long double s21_sqrt(double x) {
  long double approx = x / 2;

  if (x == S21_INFINITY) {
    approx = S21_INFINITY;
  } else if (x == 0) {
    approx = 0;
  } else if (x > 0) {
    while (s21_fabs(approx - x / approx) > 1.0e-10) {
      approx = (approx + x / approx) * 0.5;
    }
  } else {
    approx = S21_NAN;
  }
  return approx;
}

long double s21_tan(double x) {
  long double res = 0;
  if (x == S21_INFINITY || x == -S21_INFINITY || is_NAN(x)) {
    res = S21_NAN;
  } else {
    if (x == S21_PI / 2) {
      res = S21_INFINITY;
    } else if (x == -(S21_PI / 2)) {
      res = -S21_INFINITY;
    } else {
      res = s21_sin(x) / s21_cos(x);
    }
  }

  return res;
}
