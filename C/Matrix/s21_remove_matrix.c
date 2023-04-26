#include "s21_matrix.h"

void s21_remove_matrix(matrix_t *A) {
  int res = A->matrix != NULL ? 0 : 1;
  if (res == 0) {
    for (int i = 0; i < A->rows; i++) {
      free(A->matrix[i]);
    }
    A->rows = 0;
    A->columns = 0;
    free(A->matrix);
    A->matrix = NULL;
  }
}
