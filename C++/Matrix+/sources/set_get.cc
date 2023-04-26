#include "../s21_matrix_oop.h"

void S21Matrix::SetRowsCount(int newValue) {
  if (rows_ != newValue) {
    S21Matrix copy = S21Matrix(*this);
    CopyMatrix(copy, newValue, cols_);
  }
}

void S21Matrix::SetColsCount(int newValue) {
  if (cols_ != newValue) {
    S21Matrix copy = S21Matrix(*this);
    CopyMatrix(copy, rows_, newValue);
  }
}

void S21Matrix::SetMatrix(double value) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = value;
    }
  }
}

void S21Matrix::SetMatrix(double valueMin, double valueIncrement) {
  double value = valueMin;
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      if (matrix_[i] != nullptr) {
        matrix_[i][j] = value;
        value += valueIncrement;
      }
    }
  }
}

void S21Matrix::SetMatrix(const S21Matrix& matrix) {
  SetMatrix(0.0f);

  for (int i = 0; i < matrix.rows_ && i < rows_; i++) {
    for (int j = 0; j < matrix.cols_ && j < cols_; j++) {
      matrix_[i][j] = matrix.matrix_[i][j];
    }
  }
}

void S21Matrix::SetElementAtIndex(int indexRows, int indexCols, double value) {
  if (!Contains(indexRows, indexCols)) {
    throw std::out_of_range(
        "S21Matrix::SetElementAtIndex: index out of range exception");
  }
  matrix_[indexRows][indexCols] = value;
}

int S21Matrix::GetRowsCount() const noexcept { return rows_; }

int S21Matrix::GetColsCount() const noexcept { return cols_; }

double** S21Matrix::GetMatrix() const noexcept { return matrix_; }

double S21Matrix::GetElementAtIndex(int indexRows, int indexCols) const {
  if (!Contains(indexRows, indexCols)) {
    throw std::out_of_range(
        "S21Matrix::GetElementAtIndex: index out of range exception");
  }
  return matrix_[indexRows][indexCols];
}
