#include "s21_matrix.h"

int given_matrix(matrix_t *mtx) {
  return mtx != NULL && mtx->rows > 0 && mtx->columns > 0 && mtx->matrix != NULL
             ? 0
             : 1;
}

double calc_minor(matrix_t *A) {
  double res = 0;
  if (A->rows == 1) {
    res = A->matrix[0][0];
  } else if (A->rows == 2) {
    res = A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
  } else {
    matrix_t minor;
    for (int j = 0; j < A->rows; j++) {
      s21_create_matrix(A->rows - 1, A->rows - 1, &minor);
      for (int mi = 0; mi < A->rows; mi++) {
        for (int mj = 0; mj < A->columns; mj++) {
          if (mi != 0 && mj != j) {
            minor.matrix[mi > 0 ? mi - 1 : mi][mj > j ? mj - 1 : mj] =
                A->matrix[mi][mj];
          }
        }
      }
      res += (j % 2 == 0 ? calc_minor(&minor) : -calc_minor(&minor)) *
             A->matrix[0][j];
      s21_remove_matrix(&minor);
    }
  }
  return res;
}
