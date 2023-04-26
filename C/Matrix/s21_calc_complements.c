#include "s21_matrix.h"

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int res = given_matrix(A);
  if (res == 0) {
    res = A->rows == A->columns ? 0 : 2;
    if (res == 0) {
      s21_create_matrix(A->rows, A->columns, result);
      if (A->rows == 1) {
        result->matrix[0][0] = A->matrix[0][0];
      } else {
        for (int i = 0; i < A->rows; i++) {
          for (int j = 0; j < A->columns; j++) {
            matrix_t minor;
            s21_create_matrix(A->rows - 1, A->columns - 1, &minor);
            for (int mi = 0; mi < A->rows; mi++) {
              for (int mj = 0; mj < A->columns; mj++) {
                if (mi != i && mj != j) {
                  minor.matrix[mi > i ? mi - 1 : mi][mj > j ? mj - 1 : mj] =
                      A->matrix[mi][mj];
                }
              }
            }
            result->matrix[i][j] =
                (i + j) % 2 == 0 ? calc_minor(&minor) : -calc_minor(&minor);
            s21_remove_matrix(&minor);
          }
        }
      }
    }
  }
  return res;
}
