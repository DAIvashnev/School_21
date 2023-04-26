#include "s21_matrix.h"

int s21_determinant(matrix_t *A, double *result) {
  int res = given_matrix(A);
  if (res == 0) {
    res = A->rows == A->columns ? 0 : 2;
    if (res == 0) {
      res = result != NULL ? 0 : 1;
      if (res == 0) {
        *result = calc_minor(A);
      }
    }
  }
  return res;
}
