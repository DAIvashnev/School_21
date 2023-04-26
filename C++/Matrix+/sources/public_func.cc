#include "../s21_matrix_oop.h"

bool S21Matrix::EqMatrix(const S21Matrix& other) const noexcept {
  bool result = true;
  if (IsEqualSize(other)) {
    if (!IsNullOrEmpty() && !other.IsNullOrEmpty()) {
      for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
          if (fabs(matrix_[i][j] - other.matrix_[i][j]) > 1e-7) {
            result = false;
            break;
          }
        }
      }
    }
  } else {
    result = false;
  }
  return result;
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (!IsNullOrEmpty() && !other.IsNullOrEmpty()) {
    if (IsEqualSize(other)) {
      for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
          matrix_[i][j] += other.matrix_[i][j];
        }
      }
    } else {
      throw std::invalid_argument(
          "S21Matrix::SumMatrix: different matrix dimensions exception");
    }
  } else {
    throw std::invalid_argument("S21Matrix::SumMatrix: null matrix exception");
  }
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (!IsNullOrEmpty() && !other.IsNullOrEmpty()) {
    if (IsEqualSize(other)) {
      for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
          matrix_[i][j] -= other.matrix_[i][j];
        }
      }
    } else {
      throw std::invalid_argument(
          "S21Matrix::SubMatrix: different matrix dimensions exception");
    }
  } else {
    throw std::invalid_argument("S21Matrix::SubMatrix: null matrix exception");
  }
}

void S21Matrix::MulNumber(const double num) {
  if (!IsNullOrEmpty()) {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        matrix_[i][j] *= num;
      }
    }
  } else {
    throw std::invalid_argument("S21Matrix::SubMatrix: null matrix exception");
  }
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (!IsNullOrEmpty() && !other.IsNullOrEmpty()) {
    if (IsEqualSize(other)) {
      for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
          matrix_[i][j] *= other.matrix_[i][j];
        }
      }
    } else {
      throw std::invalid_argument(
          "S21Matrix::MulMatrix: different matrix dimensions exception");
    }
  } else {
    throw std::invalid_argument("S21Matrix::MulMatrix: null matrix exception");
  }
}

S21Matrix S21Matrix::Transpose() const {
  S21Matrix result = S21Matrix();
  if (!IsNullOrEmpty()) {
    result = S21Matrix(cols_, rows_);
    for (int i = 0; i < result.rows_; i++) {
      for (int j = 0; j < result.cols_; j++) {
        result.matrix_[i][j] = matrix_[j][i];
      }
    }
  } else {
    throw std::invalid_argument("S21Matrix::Transpose: null matrix exception");
  }
  return result;
}

S21Matrix S21Matrix::CalcComplements() const {
  S21Matrix result = S21Matrix();
  if (!IsNullOrEmpty()) {
    if (IsSquare()) {
      result = S21Matrix(*this);
      for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
          S21Matrix buffer = CalcMinorElements(*this, i, j);
          double determinant = buffer.Determinant();
          result.matrix_[i][j] = pow(-1, i + j) * determinant;
        }
      }
    } else {
      throw std::invalid_argument(
          "S21Matrix::CalcComplements: matrix is not square exception");
    }
  } else {
    throw std::invalid_argument(
        "S21Matrix::CalcComplements: null matrix exception");
  }
  return result;
}

double S21Matrix::Determinant() const {
  double result = 0.0f;
  if (!IsNullOrEmpty()) {
    if (IsSquare()) {
      if (rows_ == 1) {
        result = matrix_[0][0];
      } else if (rows_ == 2) {
        result = matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0];
      } else {
        int sign = 1;
        for (int i = 0; i < cols_; i++) {
          S21Matrix buffer = CalcMinorElements(*this, 0, i);
          double minor_result = buffer.Determinant();
          result += matrix_[0][i] * minor_result * sign;
          sign = -1 * sign;
        }
      }
    } else {
      throw std::invalid_argument(
          "S21Matrix::Determinant: matrix is not square exception");
    }
  } else {
    throw std::invalid_argument(
        "S21Matrix::Determinant: null matrix exception");
  }
  return result;
}

S21Matrix S21Matrix::InverseMatrix() const {
  S21Matrix result = S21Matrix();
  if (!IsNullOrEmpty()) {
    if (IsSquare()) {
      double determinant = Determinant();
      if (fabs(determinant) > 1e-7) {
        S21Matrix complements = CalcComplements();
        S21Matrix transposed = complements.Transpose();
        transposed.MulNumber(1.0f / determinant);
        result = S21Matrix(transposed);
      } else {
        throw std::invalid_argument(
            "S21Matrix::InverseMatrix: zero determinant exception");
      }
    } else {
      throw std::invalid_argument(
          "S21Matrix::InverseMatrix: matrix is not square exception");
    }
  } else {
    throw std::invalid_argument(
        "S21Matrix::InverseMatrix: null matrix exception");
  }
  return result;
}
