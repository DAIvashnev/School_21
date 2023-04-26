#include "../s21_matrix_oop.h"

void S21Matrix::InitMatrix() noexcept {
  cols_ = 0;
  rows_ = 0;
  matrix_ = nullptr;
}

void S21Matrix::CreateMatrix(int rows, int cols) {
  rows_ = rows;
  cols_ = cols;
  AllocateMatrix();
}

void S21Matrix::AllocateMatrix() {
  if (rows_ > 0 && cols_ > 0) {
    matrix_ = new double*[rows_];
    for (int i = 0; i < rows_; i++) {
      matrix_[i] = new double[cols_];
    }
  } else {
    matrix_ = nullptr;
  }
}

void S21Matrix::DeleteMatrix() {
  if (matrix_ != nullptr) {
    for (int i = 0; i < rows_; i++) {
      if (matrix_[i] != nullptr) {
        delete[] matrix_[i];
      }
    }
    delete[] matrix_;
    InitMatrix();
  }
}

void S21Matrix::CopyMatrix(const S21Matrix& copy, int newRows, int newCols) {
  DeleteMatrix();
  CreateMatrix(newRows, newCols);
  SetMatrix(copy);
}

S21Matrix S21Matrix::CalcMinorElements(const S21Matrix& origin, int indexRows,
                                       int indexCols) const {
  S21Matrix result = S21Matrix();
  if (!origin.IsNullOrEmpty() && origin.IsSquare()) {
    int elemRows = 0;
    int elemCols = 0;
    result = S21Matrix(origin.rows_ - 1, origin.cols_ - 1);
    if (!result.IsNullOrEmpty()) {
      for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
          if (i != indexRows && j != indexCols) {
            result.matrix_[elemRows][elemCols] = origin.matrix_[i][j];
            elemCols++;
          }
        }
        if (i != indexRows) {
          elemRows++;
        }
        elemCols = 0;
      }
    }
  }
  return result;
}
