#include "s21_matrix.h"

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int res = given_matrix(A);
  if (res == FAILURE) {
    res = given_matrix(B);
    if (res == FAILURE) {
      res = A->rows == B->rows && A->columns == B->columns ? SUCCESS : FAILURE;
      for (int i = 0; i < A->rows && res == SUCCESS; i++) {
        for (int j = 0; j < A->columns && res == SUCCESS; j++) {
          if (fabs(A->matrix[i][j] - B->matrix[i][j]) > 1e-7) {
            res = FAILURE;
          }
        }
      }
    }
  }
  return res;
}
