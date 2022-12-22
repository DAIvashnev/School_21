#include "s21_math.h"

long double s21_pow(double base, double exp) {
    double result = base;
    for(double i = exp; i > 1.0; i--) {
        result = result * base;
    }
    return result;
}

/*int main () {
    double x;;
    double y;
    scanf("%lf %lf", &x, &y);
    printf("%Lf\n", s21_pow(x, y));
    return 0;
}*/