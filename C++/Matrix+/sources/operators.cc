#include "../s21_matrix_oop.h"

double& S21Matrix::operator()(int i, int j) {
  if (!Contains(i, j)) {
    throw std::out_of_range("S21Matrix: index out of range exception");
  }
  return matrix_[i][j];
}

const double& S21Matrix::operator()(int i, int j) const {
  if (!Contains(i, j)) {
    throw std::out_of_range("S21Matrix: index out of range exception");
  }
  return matrix_[i][j];
}

bool S21Matrix::operator==(const S21Matrix& other) const noexcept {
  return EqMatrix(other);
}

bool S21Matrix::operator!=(const S21Matrix& other) const noexcept {
  return !EqMatrix(other);
}

S21Matrix S21Matrix::operator=(const S21Matrix& other) {
  CopyMatrix(other, other.rows_, other.cols_);
  return *this;
}

S21Matrix S21Matrix::operator+(const S21Matrix& other) const {
  S21Matrix result = S21Matrix(*this);
  result.SumMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) const {
  S21Matrix result = S21Matrix(*this);
  result.SubMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) const {
  S21Matrix result = S21Matrix(*this);
  result.MulMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator*(double num) const {
  S21Matrix result = S21Matrix(*this);
  result.MulNumber(num);
  return result;
}

S21Matrix operator*(const double num, const S21Matrix& other) {
  S21Matrix result(other);
  return result * num;
}

S21Matrix S21Matrix::operator+=(const S21Matrix& other) {
  SumMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator-=(const S21Matrix& other) {
  SubMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator*=(const S21Matrix& other) {
  MulMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator*=(double num) {
  MulNumber(num);
  return *this;
}
