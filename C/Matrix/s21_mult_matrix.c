#include "s21_matrix.h"

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = given_matrix(A);
  if (res == 0) {
    res = given_matrix(B);
    if (res == 0) {
      res = A->columns == B->rows ? 0 : 2;
      if (res == 0) {
        s21_create_matrix(A->rows, B->columns, result);
        for (int i = 0; i < A->rows; i++) {
          for (int j = 0; j < B->columns; j++) {
            result->matrix[i][j] = 0;
            for (int k = 0; k < A->columns; k++) {
              result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
            }
          }
        }
      }
    }
  }
  return res;
}
