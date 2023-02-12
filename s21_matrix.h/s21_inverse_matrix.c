#include "s21_matrix.h"

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int res = given_matrix(A);
  if (res == 0) {
    res = A->rows == A->columns ? 0 : 2;
    if (res == 0) {
      if (A->rows == 1) {
        double det = 0;
        s21_determinant(A, &det);
        if (fabs(det - 0) > 1e-6) {
          s21_create_matrix(A->rows, A->columns, result);
          result->matrix[0][0] = (double)1 / A->matrix[0][0];
        } else {
          res = 2;
        }
      } else {
        double det = 0;
        s21_determinant(A, &det);
        if (fabs(det - 0) > 1e-6) {
          matrix_t complements;
          s21_calc_complements(A, &complements);
          matrix_t transpose;
          s21_transpose(&complements, &transpose);
          s21_mult_number(&transpose, 1 / det, result);
          s21_remove_matrix(&complements);
          s21_remove_matrix(&transpose);
        } else {
          res = 2;
        }
      }
    }
  }
  return res;
}
