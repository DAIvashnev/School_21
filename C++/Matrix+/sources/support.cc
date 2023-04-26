#include "../s21_matrix_oop.h"

bool S21Matrix::IsEqualSize(const S21Matrix& other) const noexcept {
  return (rows_ == other.rows_ && cols_ == other.cols_) ? true : false;
}

bool S21Matrix::IsNullOrEmpty() const noexcept {
  return (matrix_ == nullptr || rows_ < 1 || cols_ < 1) ? true : false;
}

bool S21Matrix::IsSquare() const noexcept {
  return (rows_ == cols_ && rows_ > 0) ? true : false;
}

bool S21Matrix::Contains(int indexRows, int indexCols) const noexcept {
  return (!IsNullOrEmpty() && (indexRows >= 0 && indexRows < rows_) &&
          (indexCols >= 0 && indexCols < cols_))
             ? true
             : false;
}

void S21Matrix::PrintMatrix() const noexcept {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      std::cout << matrix_[i][j] << " ";
    }
    std::cout << "\n";
  }
}