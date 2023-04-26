#include "../s21_matrix_oop.h"

S21Matrix::S21Matrix() noexcept { InitMatrix(); }

S21Matrix::S21Matrix(int rows, int cols) {
  CreateMatrix(rows, cols);
  SetMatrix(0.0f);
}

S21Matrix::S21Matrix(const S21Matrix& other) {
  CreateMatrix(other.cols_, other.rows_);
  SetMatrix(other);
}

S21Matrix::S21Matrix(S21Matrix&& other) noexcept {
  this->cols_ = other.cols_;
  this->rows_ = other.rows_;
  this->matrix_ = other.matrix_;
  other.InitMatrix();
}

S21Matrix::~S21Matrix() { DeleteMatrix(); }