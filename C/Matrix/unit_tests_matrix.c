#include <check.h>

#include "s21_matrix.h"

START_TEST(s21_create_matrix_test_ok) {
  matrix_t mtx;
  int expected = 0, res;

  res = s21_create_matrix(5, 5, &mtx);
  ck_assert_int_eq(expected, res);
  s21_remove_matrix(&mtx);

  res = s21_create_matrix(1, 10, &mtx);
  ck_assert_int_eq(expected, res);
  s21_remove_matrix(&mtx);

  res = s21_create_matrix(10, 1, &mtx);
  ck_assert_int_eq(expected, res);
  s21_remove_matrix(&mtx);

  res = s21_create_matrix(100, 99, &mtx);
  ck_assert_int_eq(expected, res);
  s21_remove_matrix(&mtx);
}
END_TEST

START_TEST(s21_create_matrix_test_error) {
  matrix_t mtx;
  int expected = 1, res;

  res = s21_create_matrix(0, 0, &mtx);
  ck_assert_int_eq(expected, res);

  res = s21_create_matrix(0, 10, &mtx);
  ck_assert_int_eq(expected, res);

  res = s21_create_matrix(10, 0, &mtx);
  ck_assert_int_eq(expected, res);
}
END_TEST

START_TEST(s21_remove_matrix_test) {
  matrix_t mtx;
  // ok
  s21_create_matrix(5, 5, &mtx);
  s21_remove_matrix(&mtx);
  ck_assert_int_eq(mtx.rows, 0);
  ck_assert_int_eq(mtx.columns, 0);
  ck_assert_ptr_null(mtx.matrix);
  // fail
  s21_create_matrix(0, 5, &mtx);
  ck_assert_int_eq(mtx.rows, 0);
  ck_assert_int_eq(mtx.columns, 0);
  ck_assert_ptr_null(mtx.matrix);
  // ok
  s21_create_matrix(50, 25, &mtx);
  s21_remove_matrix(&mtx);
  ck_assert_int_eq(mtx.rows, 0);
  ck_assert_int_eq(mtx.columns, 0);
  ck_assert_ptr_null(mtx.matrix);
}
END_TEST

START_TEST(s21_eq_matrix_test_ok) {
  matrix_t mtx1, mtx2;

  int expected = 1, res;
  s21_create_matrix(5, 5, &mtx1);
  s21_create_matrix(5, 5, &mtx2);

  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      mtx1.matrix[i][j] = 2 * 2;
      mtx2.matrix[i][j] = 2 * 2;
    }
  }
  res = s21_eq_matrix(&mtx1, &mtx2);
  ck_assert_int_eq(expected, res);

  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      mtx1.matrix[i][j] = 0;
      mtx2.matrix[i][j] = 0;
    }
  }
  res = s21_eq_matrix(&mtx1, &mtx2);
  ck_assert_int_eq(expected, res);

  s21_remove_matrix(&mtx1);
  s21_remove_matrix(&mtx2);

  s21_create_matrix(3, 9, &mtx1);
  s21_create_matrix(3, 9, &mtx2);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 9; j++) {
      mtx1.matrix[i][j] = i * j;
      mtx2.matrix[i][j] = i * j;
    }
  }
  res = s21_eq_matrix(&mtx1, &mtx2);
  ck_assert_int_eq(expected, res);

  s21_remove_matrix(&mtx1);
  s21_remove_matrix(&mtx2);
}
END_TEST

START_TEST(s21_eq_matrix_test_error) {
  matrix_t mtx1, mtx2;

  int expected = FAILURE, res;
  s21_create_matrix(5, 3, &mtx1);
  s21_create_matrix(5, 5, &mtx2);

  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 3; j++) {
      mtx1.matrix[i][j] = 2 * 2;
      mtx2.matrix[i][j] = 2 * 2;
    }
  }
  res = s21_eq_matrix(&mtx1, &mtx2);
  ck_assert_int_eq(expected, res);

  s21_remove_matrix(&mtx1);
  s21_remove_matrix(&mtx2);

  s21_create_matrix(5, 5, &mtx1);
  s21_create_matrix(5, 5, &mtx2);

  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      mtx1.matrix[i][j] = i * j;
      mtx2.matrix[i][j] = (i + 1) / (j + 1);
    }
  }
  res = s21_eq_matrix(&mtx1, &mtx2);
  ck_assert_int_eq(expected, res);

  s21_remove_matrix(&mtx1);
  s21_remove_matrix(&mtx2);

  s21_create_matrix(11, 11, &mtx1);
  s21_create_matrix(11, 11, &mtx2);

  for (int i = 0; i < 11; i++) {
    for (int j = 0; j < 11; j++) {
      mtx1.matrix[i][j] = i * 1.2222;
      mtx2.matrix[i][j] = i * 1.3333;
    }
  }
  res = s21_eq_matrix(&mtx1, &mtx2);
  ck_assert_int_eq(expected, res);

  s21_remove_matrix(&mtx1);
  s21_remove_matrix(&mtx2);
}
END_TEST

START_TEST(s21_sum_matrix_test_ok) {
  matrix_t mtx1, mtx2, expectedmtx3, mtxRes;
  int expected = 0, res;

  s21_create_matrix(3, 3, &mtx1);
  s21_create_matrix(3, 3, &mtx2);
  s21_create_matrix(3, 3, &expectedmtx3);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      mtx1.matrix[i][j] = (i + 3) * (j + 5);
      mtx2.matrix[i][j] = 10;
      expectedmtx3.matrix[i][j] = mtx1.matrix[i][j] + mtx2.matrix[i][j];
    }
  }
  res = s21_sum_matrix(&mtx1, &mtx2, &mtxRes);
  ck_assert_int_eq(expected, res);
  ck_assert_int_eq(s21_eq_matrix(&expectedmtx3, &mtxRes), SUCCESS);

  s21_remove_matrix(&mtx1);
  s21_remove_matrix(&mtx2);
  s21_remove_matrix(&expectedmtx3);
  s21_remove_matrix(&mtxRes);

  s21_create_matrix(23, 7, &mtx1);
  s21_create_matrix(23, 7, &mtx2);
  s21_create_matrix(23, 7, &expectedmtx3);
  for (int i = 0; i < 23; i++) {
    for (int j = 0; j < 7; j++) {
      mtx1.matrix[i][j] = (2.432) * (-5.23);
      mtx2.matrix[i][j] = 0.432 * pow(2, 6);
      expectedmtx3.matrix[i][j] = mtx1.matrix[i][j] + mtx2.matrix[i][j];
    }
  }
  res = s21_sum_matrix(&mtx1, &mtx2, &mtxRes);
  ck_assert_int_eq(expected, res);
  ck_assert_int_eq(s21_eq_matrix(&expectedmtx3, &mtxRes), SUCCESS);

  s21_remove_matrix(&mtx1);
  s21_remove_matrix(&mtx2);
  s21_remove_matrix(&expectedmtx3);
  s21_remove_matrix(&mtxRes);
}
END_TEST

START_TEST(s21_sum_matrix_test_error) {
  matrix_t mtx1, mtx2, mtx3, mtxRes;
  int expected = 2, res;

  s21_create_matrix(3, 3, &mtx1);
  s21_create_matrix(6, 4, &mtx2);
  s21_create_matrix(4, 5, &mtx3);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      mtx1.matrix[i][j] = (i + 3) * (j + 5);
      mtx2.matrix[i][j] = 10;
      mtx3.matrix[i][j] = mtx1.matrix[i][j] + mtx2.matrix[i][j];
    }
  }
  res = s21_sum_matrix(&mtx1, &mtx2, &mtxRes);
  ck_assert_int_eq(expected, res);

  s21_remove_matrix(&mtx1);
  s21_remove_matrix(&mtx2);
  s21_remove_matrix(&mtx3);
}
END_TEST

START_TEST(s21_sub_matrix_test_ok) {
  matrix_t mtx1, mtx2, expectedmtx3, mtxRes;
  int expected = 0, res;

  s21_create_matrix(3, 3, &mtx1);
  s21_create_matrix(3, 3, &mtx2);
  s21_create_matrix(3, 3, &expectedmtx3);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      mtx1.matrix[i][j] = (i + 3) * (j + 5);
      mtx2.matrix[i][j] = 10;
      expectedmtx3.matrix[i][j] = mtx1.matrix[i][j] - mtx2.matrix[i][j];
    }
  }
  res = s21_sub_matrix(&mtx1, &mtx2, &mtxRes);
  ck_assert_int_eq(expected, res);
  ck_assert_int_eq(s21_eq_matrix(&expectedmtx3, &mtxRes), SUCCESS);

  s21_remove_matrix(&mtx1);
  s21_remove_matrix(&mtx2);
  s21_remove_matrix(&expectedmtx3);
  s21_remove_matrix(&mtxRes);

  s21_create_matrix(23, 7, &mtx1);
  s21_create_matrix(23, 7, &mtx2);
  s21_create_matrix(23, 7, &expectedmtx3);
  for (int i = 0; i < 23; i++) {
    for (int j = 0; j < 7; j++) {
      mtx1.matrix[i][j] = (2.432) * (-5.23);
      mtx2.matrix[i][j] = 0.432 * pow(2, 6);
      expectedmtx3.matrix[i][j] = mtx1.matrix[i][j] - mtx2.matrix[i][j];
    }
  }
  res = s21_sub_matrix(&mtx1, &mtx2, &mtxRes);
  ck_assert_int_eq(expected, res);
  ck_assert_int_eq(s21_eq_matrix(&expectedmtx3, &mtxRes), SUCCESS);

  s21_remove_matrix(&mtx1);
  s21_remove_matrix(&mtx2);
  s21_remove_matrix(&expectedmtx3);
  s21_remove_matrix(&mtxRes);
}
END_TEST

START_TEST(s21_sub_matrix_test_error) {
  matrix_t mtx1, mtx2, mtx3, mtxRes;
  int expected = 2, res;

  s21_create_matrix(3, 3, &mtx1);
  s21_create_matrix(6, 4, &mtx2);
  s21_create_matrix(4, 5, &mtx3);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      mtx1.matrix[i][j] = (i + 3) * (j + 5);
      mtx2.matrix[i][j] = 10;
      mtx3.matrix[i][j] = mtx1.matrix[i][j] - mtx2.matrix[i][j];
    }
  }
  res = s21_sub_matrix(&mtx1, &mtx2, &mtxRes);
  ck_assert_int_eq(expected, res);

  s21_remove_matrix(&mtx1);
  s21_remove_matrix(&mtx2);
  s21_remove_matrix(&mtx3);
}
END_TEST

START_TEST(s21_mult_number_test_ok) {
  matrix_t mtx1, expectedmtx2, mtxRes;
  int expected = 0, res;
  double num = 4.7458970;

  s21_create_matrix(25, 25, &mtx1);
  s21_create_matrix(25, 25, &expectedmtx2);

  for (int i = 0; i < 25; i++) {
    for (int j = 0; j < 25; j++) {
      mtx1.matrix[i][j] = i;
      expectedmtx2.matrix[i][j] = mtx1.matrix[i][j] * num;
    }
  }

  res = s21_mult_number(&mtx1, num, &mtxRes);
  ck_assert_int_eq(expected, res);
  ck_assert_int_eq(s21_eq_matrix(&expectedmtx2, &mtxRes), SUCCESS);

  s21_remove_matrix(&mtx1);
  s21_remove_matrix(&expectedmtx2);
  s21_remove_matrix(&mtxRes);

  num = 2345;
  s21_create_matrix(50, 90, &mtx1);
  s21_create_matrix(50, 90, &expectedmtx2);

  for (int i = 0; i < 50; i++) {
    for (int j = 0; j < 90; j++) {
      mtx1.matrix[i][j] = i * num / 20.0;
      expectedmtx2.matrix[i][j] = mtx1.matrix[i][j] * num;
    }
  }

  res = s21_mult_number(&mtx1, num, &mtxRes);
  ck_assert_int_eq(expected, res);
  ck_assert_int_eq(s21_eq_matrix(&expectedmtx2, &mtxRes), SUCCESS);

  s21_remove_matrix(&mtx1);
  s21_remove_matrix(&expectedmtx2);
  s21_remove_matrix(&mtxRes);
}
END_TEST

START_TEST(s21_mult_number_test_error) {
  matrix_t mtxRes;
  int expected = 1, res;
  double num = 4.7458970;

  res = s21_mult_number(NULL, num, &mtxRes);
  ck_assert_int_eq(expected, res);
}
END_TEST

START_TEST(s21_mult_matrix_test_ok) {
  matrix_t mtx1, mtx2, expectedmtx3, mtxRes;
  int expected = 0, res;

  s21_create_matrix(3, 2, &mtx1);
  s21_create_matrix(2, 3, &mtx2);
  s21_create_matrix(3, 3, &expectedmtx3);

  mtx1.matrix[0][0] = 1;
  mtx1.matrix[0][1] = 4;
  mtx1.matrix[1][0] = 2;
  mtx1.matrix[1][1] = 5;
  mtx1.matrix[2][0] = 3;
  mtx1.matrix[2][1] = 6;

  mtx2.matrix[0][0] = 1;
  mtx2.matrix[0][1] = -1;
  mtx2.matrix[0][2] = 1;
  mtx2.matrix[1][0] = 2;
  mtx2.matrix[1][1] = 3;
  mtx2.matrix[1][2] = 4;

  expectedmtx3.matrix[0][0] = 9;
  expectedmtx3.matrix[0][1] = 11;
  expectedmtx3.matrix[0][2] = 17;
  expectedmtx3.matrix[1][0] = 12;
  expectedmtx3.matrix[1][1] = 13;
  expectedmtx3.matrix[1][2] = 22;
  expectedmtx3.matrix[2][0] = 15;
  expectedmtx3.matrix[2][1] = 15;
  expectedmtx3.matrix[2][2] = 27;

  res = s21_mult_matrix(&mtx1, &mtx2, &mtxRes);
  ck_assert_int_eq(expected, res);
  ck_assert_int_eq(s21_eq_matrix(&expectedmtx3, &mtxRes), SUCCESS);

  s21_remove_matrix(&mtx1);
  s21_remove_matrix(&mtx2);
  s21_remove_matrix(&expectedmtx3);
  s21_remove_matrix(&mtxRes);

  s21_create_matrix(3, 2, &mtx1);
  s21_create_matrix(2, 3, &mtx2);

  mtx1.matrix[0][0] = 1.454;
  mtx1.matrix[0][1] = 4.34522;
  mtx1.matrix[1][0] = 2.865;
  mtx1.matrix[1][1] = 5.32;
  mtx1.matrix[2][0] = 3.0;
  mtx1.matrix[2][1] = 6.342;

  mtx2.matrix[0][0] = 1.4;
  mtx2.matrix[0][1] = -1.8567;
  mtx2.matrix[0][2] = 1.345;
  mtx2.matrix[1][0] = 2.245;
  mtx2.matrix[1][1] = 3.7546345222;
  mtx2.matrix[1][2] = 4.4353464564;

  res = s21_mult_matrix(&mtx1, &mtx2, &mtxRes);
  ck_assert_int_eq(expected, res);

  s21_remove_matrix(&mtx1);
  s21_remove_matrix(&mtx2);
  s21_remove_matrix(&mtxRes);
}
END_TEST

START_TEST(s21_mult_matrix_test_error) {
  matrix_t mtx1, mtx2, mtxRes;
  int expected = 1, res;
  res = s21_mult_matrix(NULL, &mtx2, &mtxRes);
  ck_assert_int_eq(expected, res);

  s21_create_matrix(5, 5, &mtx1);
  res = s21_mult_matrix(&mtx1, NULL, &mtxRes);
  ck_assert_int_eq(expected, res);
  s21_remove_matrix(&mtx1);

  expected = 2;
  s21_create_matrix(5, 5, &mtx1);
  s21_create_matrix(6, 6, &mtx2);
  res = s21_mult_matrix(&mtx1, &mtx2, &mtxRes);
  ck_assert_int_eq(expected, res);
  s21_remove_matrix(&mtx1);
  s21_remove_matrix(&mtx2);
}
END_TEST

START_TEST(s21_transpose_test_ok) {
  matrix_t mtx1, expectedmtx2, mtxRes;
  int expected = 0, res;

  s21_create_matrix(3, 2, &mtx1);
  s21_create_matrix(2, 3, &expectedmtx2);

  mtx1.matrix[0][0] = 1;
  mtx1.matrix[0][1] = 4;
  mtx1.matrix[1][0] = 2;
  mtx1.matrix[1][1] = 5;
  mtx1.matrix[2][0] = 3;
  mtx1.matrix[2][1] = 6;

  expectedmtx2.matrix[0][0] = 1;
  expectedmtx2.matrix[0][1] = 2;
  expectedmtx2.matrix[0][2] = 3;
  expectedmtx2.matrix[1][0] = 4;
  expectedmtx2.matrix[1][1] = 5;
  expectedmtx2.matrix[1][2] = 6;

  res = s21_transpose(&mtx1, &mtxRes);
  ck_assert_int_eq(expected, res);
  ck_assert_int_eq(s21_eq_matrix(&expectedmtx2, &mtxRes), SUCCESS);

  s21_remove_matrix(&mtx1);
  s21_remove_matrix(&expectedmtx2);
  s21_remove_matrix(&mtxRes);
}
END_TEST

START_TEST(s21_transpose_test_error) {
  matrix_t mtxRes;
  int expected = 1, res;

  res = s21_transpose(NULL, &mtxRes);
  ck_assert_int_eq(expected, res);
}
END_TEST

START_TEST(s21_calc_complements_test_ok) {
  matrix_t mtx1, expectedRes, mtxRes;
  int expected = 0, a = 1, res;

  s21_create_matrix(1, 1, &mtx1);
  s21_create_matrix(1, 1, &expectedRes);
  mtx1.matrix[0][0] = 49;
  expectedRes.matrix[0][0] = 49;
  res = s21_calc_complements(&mtx1, &mtxRes);
  ck_assert_int_eq(expected, res);
  ck_assert_int_eq(s21_eq_matrix(&expectedRes, &mtxRes), SUCCESS);
  s21_remove_matrix(&mtx1);
  s21_remove_matrix(&expectedRes);
  s21_remove_matrix(&mtxRes);

  s21_create_matrix(3, 3, &mtx1);
  s21_create_matrix(3, 3, &expectedRes);

  mtx1.matrix[0][0] = 1;
  mtx1.matrix[0][1] = 2;
  mtx1.matrix[0][2] = 3;
  mtx1.matrix[1][0] = 0;
  mtx1.matrix[1][1] = 4;
  mtx1.matrix[1][2] = 2;
  mtx1.matrix[2][0] = 5;
  mtx1.matrix[2][1] = 2;
  mtx1.matrix[2][2] = 1;

  expectedRes.matrix[0][0] = 0;
  expectedRes.matrix[0][1] = 10;
  expectedRes.matrix[0][2] = -20;
  expectedRes.matrix[1][0] = 4;
  expectedRes.matrix[1][1] = -14;
  expectedRes.matrix[1][2] = 8;
  expectedRes.matrix[2][0] = -8;
  expectedRes.matrix[2][1] = -2;
  expectedRes.matrix[2][2] = 4;

  res = s21_calc_complements(&mtx1, &mtxRes);
  ck_assert_int_eq(expected, res);
  ck_assert_int_eq(s21_eq_matrix(&expectedRes, &mtxRes), SUCCESS);

  s21_remove_matrix(&mtx1);
  s21_remove_matrix(&expectedRes);
  s21_remove_matrix(&mtxRes);

  s21_create_matrix(4, 4, &mtx1);
  s21_create_matrix(4, 4, &expectedRes);
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++, a++) mtx1.matrix[i][j] = a * a;
  expectedRes.matrix[0][0] = -512;
  expectedRes.matrix[0][1] = 1536;
  expectedRes.matrix[0][2] = -1536;
  expectedRes.matrix[0][3] = 512;
  expectedRes.matrix[1][0] = 1536;
  expectedRes.matrix[1][1] = -4608;
  expectedRes.matrix[1][2] = 4608;
  expectedRes.matrix[1][3] = -1536;
  expectedRes.matrix[2][0] = -1536;
  expectedRes.matrix[2][1] = 4608;
  expectedRes.matrix[2][2] = -4608;
  expectedRes.matrix[2][3] = 1536;
  expectedRes.matrix[3][0] = 512;
  expectedRes.matrix[3][1] = -1536;
  expectedRes.matrix[3][2] = 1536;
  expectedRes.matrix[3][3] = -512;

  res = s21_calc_complements(&mtx1, &mtxRes);
  ck_assert_int_eq(expected, res);
  ck_assert_int_eq(s21_eq_matrix(&expectedRes, &mtxRes), SUCCESS);

  s21_remove_matrix(&mtx1);
  s21_remove_matrix(&expectedRes);
  s21_remove_matrix(&mtxRes);
}
END_TEST

START_TEST(s21_calc_complements_test_error) {
  matrix_t mtx1, mtxRes;
  int expected = 1, res;

  res = s21_calc_complements(NULL, &mtxRes);
  ck_assert_int_eq(expected, res);

  expected = 2, s21_create_matrix(2, 3, &mtx1);
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 3; j++) {
      mtx1.matrix[i][j] = 0 + i * j;
    }
  }
  res = s21_calc_complements(&mtx1, &mtxRes);
  ck_assert_int_eq(expected, res);
  s21_remove_matrix(&mtx1);
}
END_TEST

START_TEST(s21_determinant_test_ok) {
  matrix_t mtx1;
  int expected = 0, res;
  double expectedRes = -4543.2342;

  s21_create_matrix(3, 3, &mtx1);

  mtx1.matrix[0][0] = 1;
  mtx1.matrix[0][1] = 2;
  mtx1.matrix[0][2] = 3;
  mtx1.matrix[1][0] = 4;
  mtx1.matrix[1][1] = 5;
  mtx1.matrix[1][2] = 6;
  mtx1.matrix[2][0] = 7;
  mtx1.matrix[2][1] = 8;
  mtx1.matrix[2][2] = 9;

  res = s21_determinant(&mtx1, &expectedRes);
  ck_assert_int_eq(expected, res);
  ck_assert_double_eq_tol(expectedRes, expected, 1e-7);

  s21_remove_matrix(&mtx1);

  s21_create_matrix(5, 5, &mtx1);

  mtx1.matrix[0][0] = 4;
  mtx1.matrix[0][1] = 7;
  mtx1.matrix[0][2] = 4;
  mtx1.matrix[0][3] = 8;
  mtx1.matrix[0][4] = 4;
  mtx1.matrix[1][0] = 3;
  mtx1.matrix[1][1] = -4;
  mtx1.matrix[1][2] = 2;
  mtx1.matrix[1][3] = -4;
  mtx1.matrix[1][4] = 2;
  mtx1.matrix[2][0] = 3;
  mtx1.matrix[2][1] = 3;
  mtx1.matrix[2][2] = 3;
  mtx1.matrix[2][3] = 4;
  mtx1.matrix[2][4] = 1;
  mtx1.matrix[3][0] = 0;
  mtx1.matrix[3][1] = -4;
  mtx1.matrix[3][2] = 3;
  mtx1.matrix[3][3] = 3;
  mtx1.matrix[3][4] = 4;
  mtx1.matrix[4][0] = 5;
  mtx1.matrix[4][1] = 5;
  mtx1.matrix[4][2] = -4;
  mtx1.matrix[4][3] = 3;
  mtx1.matrix[4][4] = 2;

  res = s21_determinant(&mtx1, &expectedRes);
  ck_assert_int_eq(expected, res);
  expected = 3955;
  ck_assert_double_eq_tol(expectedRes, expected, 1e-7);

  s21_remove_matrix(&mtx1);
}
END_TEST

START_TEST(s21_determinant_test_error) {
  matrix_t mtx1;
  int expected = 1, res;
  double expectedRes = -4543.2342;

  res = s21_determinant(NULL, &expectedRes);
  ck_assert_int_eq(expected, res);

  expected = 2, s21_create_matrix(2, 3, &mtx1);
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 3; j++) {
      mtx1.matrix[i][j] = 0 + i * j;
    }
  }
  res = s21_determinant(&mtx1, &expectedRes);
  ck_assert_int_eq(expected, res);
  s21_remove_matrix(&mtx1);

  expected = 1, s21_create_matrix(3, 3, &mtx1);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      mtx1.matrix[i][j] = 0 + i * j;
    }
  }
  res = s21_determinant(&mtx1, NULL);
  ck_assert_int_eq(expected, res);
  s21_remove_matrix(&mtx1);
}
END_TEST

START_TEST(s21_inverse_matrix_test_ok) {
  matrix_t mtx1, expectedRes, mtxRes;
  int expected = 0, res;

  s21_create_matrix(1, 1, &mtx1);
  s21_create_matrix(1, 1, &expectedRes);
  mtx1.matrix[0][0] = 49;
  expectedRes.matrix[0][0] = (double)1 / (double)49;
  res = s21_inverse_matrix(&mtx1, &mtxRes);
  ck_assert_int_eq(expected, res);
  ck_assert_int_eq(s21_eq_matrix(&expectedRes, &mtxRes), SUCCESS);

  s21_remove_matrix(&mtx1);
  s21_remove_matrix(&expectedRes);
  s21_remove_matrix(&mtxRes);

  s21_create_matrix(3, 3, &mtx1);
  s21_create_matrix(3, 3, &expectedRes);

  mtx1.matrix[0][0] = 2;
  mtx1.matrix[0][1] = 5;
  mtx1.matrix[0][2] = 7;
  mtx1.matrix[1][0] = 6;
  mtx1.matrix[1][1] = 3;
  mtx1.matrix[1][2] = 4;
  mtx1.matrix[2][0] = 5;
  mtx1.matrix[2][1] = -2;
  mtx1.matrix[2][2] = -3;

  expectedRes.matrix[0][0] = 1;
  expectedRes.matrix[0][1] = -1;
  expectedRes.matrix[0][2] = 1;
  expectedRes.matrix[1][0] = -38;
  expectedRes.matrix[1][1] = 41;
  expectedRes.matrix[1][2] = -34;
  expectedRes.matrix[2][0] = 27;
  expectedRes.matrix[2][1] = -29;
  expectedRes.matrix[2][2] = 24;

  res = s21_inverse_matrix(&mtx1, &mtxRes);
  ck_assert_int_eq(expected, res);
  ck_assert_int_eq(s21_eq_matrix(&expectedRes, &mtxRes), SUCCESS);

  s21_remove_matrix(&mtx1);
  s21_remove_matrix(&expectedRes);
  s21_remove_matrix(&mtxRes);

  s21_create_matrix(3, 3, &mtx1);
  s21_create_matrix(3, 3, &expectedRes);

  mtx1.matrix[0][0] = 1;
  mtx1.matrix[0][1] = 2;
  mtx1.matrix[0][2] = 3;
  mtx1.matrix[1][0] = 0;
  mtx1.matrix[1][1] = 4;
  mtx1.matrix[1][2] = 2;
  mtx1.matrix[2][0] = 5;
  mtx1.matrix[2][1] = 2;
  mtx1.matrix[2][2] = 1;

  expectedRes.matrix[0][0] = (double)0;
  expectedRes.matrix[0][1] = (double)-1 / 10;
  expectedRes.matrix[0][2] = (double)1 / 5;
  expectedRes.matrix[1][0] = (double)-1 / 4;
  expectedRes.matrix[1][1] = (double)7 / 20;
  expectedRes.matrix[1][2] = (double)1 / 20;
  expectedRes.matrix[2][0] = (double)1 / 2;
  expectedRes.matrix[2][1] = (double)-1 / 5;
  expectedRes.matrix[2][2] = (double)-1 / 10;

  res = s21_inverse_matrix(&mtx1, &mtxRes);
  ck_assert_int_eq(expected, res);
  ck_assert_int_eq(s21_eq_matrix(&expectedRes, &mtxRes), SUCCESS);

  s21_remove_matrix(&mtx1);
  s21_remove_matrix(&expectedRes);
  s21_remove_matrix(&mtxRes);
}
END_TEST

START_TEST(s21_inverse_matrix_test_error) {
  matrix_t mtx1, mtxRes;
  int expected = 1, a = 1, res;

  res = s21_inverse_matrix(NULL, &mtxRes);
  ck_assert_int_eq(expected, res);

  expected = 2, s21_create_matrix(2, 3, &mtx1);
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 3; j++) {
      mtx1.matrix[i][j] = 0 + i * j;
    }
  }
  res = s21_inverse_matrix(&mtx1, &mtxRes);
  ck_assert_int_eq(expected, res);
  s21_remove_matrix(&mtx1);

  s21_create_matrix(3, 3, &mtx1);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      mtx1.matrix[i][j] = a;
    }
  }
  res = s21_inverse_matrix(&mtx1, &mtxRes);
  ck_assert_int_eq(expected, res);
  s21_remove_matrix(&mtx1);

  s21_create_matrix(1, 1, &mtx1);
  mtx1.matrix[0][0] = 0;
  res = s21_inverse_matrix(&mtx1, &mtxRes);
  ck_assert_int_eq(expected, res);
  s21_remove_matrix(&mtx1);
}
END_TEST

int main(void) {
  Suite *s1 = suite_create("Suite");
  SRunner *sr = srunner_create(s1);

  TCase *tc_main = tcase_create("tests");
  suite_add_tcase(s1, tc_main);

  tcase_add_test(tc_main, s21_create_matrix_test_ok);
  tcase_add_test(tc_main, s21_create_matrix_test_error);

  tcase_add_test(tc_main, s21_remove_matrix_test);

  tcase_add_test(tc_main, s21_eq_matrix_test_ok);
  tcase_add_test(tc_main, s21_eq_matrix_test_error);

  tcase_add_test(tc_main, s21_sum_matrix_test_ok);
  tcase_add_test(tc_main, s21_sum_matrix_test_error);

  tcase_add_test(tc_main, s21_sub_matrix_test_ok);
  tcase_add_test(tc_main, s21_sub_matrix_test_error);

  tcase_add_test(tc_main, s21_mult_number_test_ok);
  tcase_add_test(tc_main, s21_mult_number_test_error);

  tcase_add_test(tc_main, s21_mult_matrix_test_ok);
  tcase_add_test(tc_main, s21_mult_matrix_test_error);

  tcase_add_test(tc_main, s21_transpose_test_ok);
  tcase_add_test(tc_main, s21_transpose_test_error);

  tcase_add_test(tc_main, s21_calc_complements_test_ok);
  tcase_add_test(tc_main, s21_calc_complements_test_error);

  tcase_add_test(tc_main, s21_determinant_test_ok);
  tcase_add_test(tc_main, s21_determinant_test_error);

  tcase_add_test(tc_main, s21_inverse_matrix_test_ok);
  tcase_add_test(tc_main, s21_inverse_matrix_test_error);

  srunner_run_all(sr, CK_ENV);
  srunner_free(sr);

  return 0;
}
