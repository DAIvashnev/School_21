#include <check.h>
#include <stdio.h>

#include "s21_decimal.h"

#define EDGE_TESTS 23
#define SIMPLE_TESTS 12
#define TRUNC_TESTS 12
#define FLOOR_TESTS 16
#define ROUND_TESTS 20
#define TRUNCATE_TESTS 22
#define NEGATE_TESTS 22
#define MUL_PIE_TESTS 20
#define MUL_ERR_TESTS 10
#define MUL_ROUND_TESTS 16
#define TESTS_COMP 13

void print_dec(s21_decimal x) {
  for (int i = 0; i < 4; i++) printf("%u ", x.bits[i]);
  printf("\n");
}

void print_super_dec(s21_super_decimal x) {
  for (int i = 0; i < 6; i++) printf("%u ", x.bits[i]);
  printf("\n");
}

// clytemne arrays
float float_edge_arr[EDGE_TESTS] = {1,
                                    -1,
                                    7e28,
                                    -7e28,
                                    2e-28,
                                    -2e-28,
                                    1e30,
                                    -1e30,
                                    1e-30,
                                    -1e-30,
                                    8388608,
                                    -8388608,
                                    7922817e22,
                                    -7922817e22,
                                    7922816e22,
                                    -7922816e22,
                                    9.999999e-29,
                                    -9.999999e-29,
                                    1. / 0.,
                                    -1. / 0.,
                                    0. / 0.,
                                    -0. / 0.,
                                    0};

s21_decimal dec_edge_arr[EDGE_TESTS] = {
    {1, 0, 0, 0},
    {1, 0, 0, 1 << 31},
    {1879048192, 3003322535, 3794707603, 0},
    {1879048192, 3003322535, 3794707603, 1 << 31},
    {2, 0, 0, 28 << 16},
    {2, 0, 0, (28 << 16) | (1 << 31)},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {8388608, 0, 0, 0},
    {8388608, 0, 0, 1 << 31},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {536870912, 3012735514, 4294967159, 0},
    {536870912, 3012735514, 4294967159, 1 << 31},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0}};
int int_edge_res[EDGE_TESTS] = {0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0,
                                1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0};

float float_simple_arr[SIMPLE_TESTS] = {1.1,     -1.1,     2.13,     -2.13,
                                        3.518,   -3.518,   4.3452,   -4.3452,
                                        5.13567, -5.13567, 6.121212, -6.121212};
s21_decimal dec_simple_arr[SIMPLE_TESTS] = {
    {11, 0, 0, 1 << 16},      {11, 0, 0, (1 << 31) | (1 << 16)},
    {213, 0, 0, 2 << 16},     {213, 0, 0, (1 << 31) | (2 << 16)},
    {3518, 0, 0, 3 << 16},    {3518, 0, 0, (1 << 31) | (3 << 16)},
    {43452, 0, 0, 4 << 16},   {43452, 0, 0, (1 << 31) | (4 << 16)},
    {513567, 0, 0, 5 << 16},  {513567, 0, 0, (1 << 31) | (5 << 16)},
    {6121212, 0, 0, 6 << 16}, {6121212, 0, 0, (1 << 31) | (6 << 16)}};
int int_simple_res[SIMPLE_TESTS] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

float float_trunc_arr[TRUNC_TESTS] = {
    1234567890, -1234567890, 0.987654321, -0.987654321, 123.456789, -123.456789,
    1.1111115,  -1.1111115,  1010101.7,   -1010101.7,   19999999,   -19999999};
s21_decimal dec_trunc_arr[TRUNC_TESTS] = {
    {1234568000, 0, 0, 0},    {1234568000, 0, 0, 1 << 31},
    {9876543, 0, 0, 7 << 16}, {9876543, 0, 0, (1 << 31) | (7 << 16)},
    {1234568, 0, 0, 4 << 16}, {1234568, 0, 0, (1 << 31) | (4 << 16)},
    {1111112, 0, 0, 6 << 16}, {1111112, 0, 0, (1 << 31) | (6 << 16)},
    {1010102, 0, 0, 0},       {1010102, 0, 0, 1 << 31},
    {20000000, 0, 0, 0},      {20000000, 0, 0, 1 << 31}};
int int_trunc_res[TRUNC_TESTS] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

s21_decimal dec_floor_src_arr[FLOOR_TESTS] = {
    {35, 0, 0, 2 << 16},
    {35, 0, 0, (1 << 31) | (2 << 16)},
    {9, 0, 0, 1 << 16},
    {9, 0, 0, (1 << 31) | (1 << 16)},
    {15, 0, 0, 1 << 16},
    {15, 0, 0, (1 << 31) | (1 << 16)},
    {268435455, 1042612833, 542101086, 27 << 16},
    {268435457, 1042612833, 542101086, (1 << 31) | (27 << 16)},
    {1009, 0, 0, 1 << 16},
    {1009, 0, 0, (1 << 31) | (1 << 16)},
    {0, 0, 0, 0},
    {0, 0, 0, 1 << 31},
    {1316134913, 2328, 0, 13 << 16},
    {1316134913, 2328, 0, (1 << 31) | (13 << 16)},
    {0, 0, 0, 1},
    {0, 0, 0, 30 << 16}};
s21_decimal dec_floor_dst_arr[FLOOR_TESTS] = {
    {0, 0, 0, 0},   {1, 0, 0, 1 << 31},   {0, 0, 0, 0}, {1, 0, 0, 1 << 31},
    {1, 0, 0, 0},   {2, 0, 0, 1 << 31},   {9, 0, 0, 0}, {11, 0, 0, 1 << 31},
    {100, 0, 0, 0}, {101, 0, 0, 1 << 31}, {0, 0, 0, 0}, {0, 0, 0, 1 << 31},
    {1, 0, 0, 0},   {2, 0, 0, 1 << 31},   {0, 0, 0, 0}, {0, 0, 0, 0}};
int int_floor_res[FLOOR_TESTS] = {0, 0, 0, 0, 0, 0, 0, 0,
                                  0, 0, 0, 0, 0, 0, 1, 1};

int float_mul_out[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
s21_decimal dec_round_src_arr[ROUND_TESTS] = {
    {35, 0, 0, 2 << 16},
    {35, 0, 0, (1 << 31) | (2 << 16)},
    {9, 0, 0, 1 << 16},
    {9, 0, 0, (1 << 31) | (1 << 16)},
    {15, 0, 0, 1 << 16},
    {15, 0, 0, (1 << 31) | (1 << 16)},
    {268435455, 1042612833, 542101086, 28 << 16},
    {268435457, 1042612833, 542101086, (1 << 31) | (28 << 16)},
    {1009, 0, 0, 1 << 16},
    {1009, 0, 0, (1 << 31) | (1 << 16)},
    {0, 0, 0, 0},
    {0, 0, 0, 1 << 31},
    {1316134913, 2328, 0, 13 << 16},
    {1316134913, 2328, 0, (1 << 31) | (13 << 16)},
    {35, 0, 0, 1 << 16},
    {35, 0, 0, (1 << 31) | (1 << 16)},
    {25, 0, 0, 1 << 16},
    {25, 0, 0, (1 << 31) | (1 << 16)},
    {0, 0, 0, 1},
    {0, 0, 0, 30 << 16}};
s21_decimal dec_round_dst_arr[ROUND_TESTS] = {
    {0, 0, 0, 0},   {0, 0, 0, 1 << 31},   {1, 0, 0, 0}, {1, 0, 0, 1 << 31},
    {2, 0, 0, 0},   {2, 0, 0, 1 << 31},   {1, 0, 0, 0}, {1, 0, 0, 1 << 31},
    {101, 0, 0, 0}, {101, 0, 0, 1 << 31}, {0, 0, 0, 0}, {0, 0, 0, 1 << 31},
    {1, 0, 0, 0},   {1, 0, 0, 1 << 31},   {4, 0, 0, 0}, {4, 0, 0, 1 << 31},
    {2, 0, 0, 0},   {2, 0, 0, 1 << 31},   {0, 0, 0, 0}, {0, 0, 0, 0}};
int int_round_res[ROUND_TESTS] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                  0, 0, 0, 0, 0, 0, 0, 0, 1, 1};

s21_decimal dec_truncate_src_arr[TRUNCATE_TESTS] = {
    {35, 0, 0, 2 << 16},
    {35, 0, 0, (1 << 31) | (2 << 16)},
    {9, 0, 0, 1 << 16},
    {9, 0, 0, (1 << 31) | (1 << 16)},
    {15, 0, 0, 1 << 16},
    {15, 0, 0, (1 << 31) | (1 << 16)},
    {268435455, 1042612833, 542101086, 28 << 16},
    {268435457, 1042612833, 542101086, (1 << 31) | (28 << 16)},
    {1009, 0, 0, 1 << 16},
    {1009, 0, 0, (1 << 31) | (1 << 16)},
    {0, 0, 0, 0},
    {0, 0, 0, 1 << 31},
    {1316134913, 2328, 0, 13 << 16},
    {1316134913, 2328, 0, (1 << 31) | (13 << 16)},
    {55, 0, 0, 1 << 16},
    {55, 0, 0, (1 << 31) | (1 << 16)},
    {5000005, 0, 0, 5 << 16},
    {5000005, 0, 0, (1 << 31) | (5 << 16)},
    {1234567, 0, 0, 6 << 16},
    {1234567, 0, 0, (1 << 31) | (6 << 16)},
    {0, 0, 0, 1},
    {0, 0, 0, 30 << 16}};
s21_decimal dec_truncate_dst_arr[TRUNCATE_TESTS] = {
    {0, 0, 0, 0},   {0, 0, 0, 1 << 31},   {0, 0, 0, 0}, {0, 0, 0, 1 << 31},
    {1, 0, 0, 0},   {1, 0, 0, 1 << 31},   {0, 0, 0, 0}, {1, 0, 0, 1 << 31},
    {100, 0, 0, 0}, {100, 0, 0, 1 << 31}, {0, 0, 0, 0}, {0, 0, 0, 1 << 31},
    {1, 0, 0, 0},   {1, 0, 0, 1 << 31},   {5, 0, 0, 0}, {5, 0, 0, 1 << 31},
    {50, 0, 0, 0},  {50, 0, 0, 1 << 31},  {1, 0, 0, 0}, {1, 0, 0, 1 << 31},
    {0, 0, 0, 0},   {0, 0, 0, 0}};
int int_truncate_res[TRUNCATE_TESTS] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                        0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1};

s21_decimal dec_negative_src_arr[NEGATE_TESTS] = {
    {35, 0, 0, 2 << 16},
    {35, 0, 0, (1 << 31) | (2 << 16)},
    {9, 0, 0, 1 << 16},
    {9, 0, 0, (1 << 31) | (1 << 16)},
    {15, 0, 0, 1 << 16},
    {15, 0, 0, (1 << 31) | (1 << 16)},
    {268435455, 1042612833, 542101086, 27 << 16},
    {268435457, 1042612833, 542101086, (1 << 31) | (27 << 16)},
    {1009, 0, 0, 1 << 16},
    {1009, 0, 0, (1 << 31) | (1 << 16)},
    {0, 0, 0, 0},
    {0, 0, 0, 1 << 31},
    {1316134913, 2328, 0, 13 << 16},
    {1316134913, 2328, 0, (1 << 31) | (13 << 16)},
    {55, 0, 0, 1 << 16},
    {55, 0, 0, (1 << 31) | (1 << 16)},
    {5000005, 0, 0, 5 << 16},
    {5000005, 0, 0, (1 << 31) | (5 << 16)},
    {1234567, 0, 0, 6 << 16},
    {1234567, 0, 0, (1 << 31) | (6 << 16)},
    {0, 0, 0, 1},
    {0, 0, 0, 30 << 16}};
s21_decimal dec_negative_dst_arr[NEGATE_TESTS] = {
    {35, 0, 0, (1 << 31) | (2 << 16)},
    {35, 0, 0, 2 << 16},
    {9, 0, 0, (1 << 31) | (1 << 16)},
    {9, 0, 0, 1 << 16},
    {15, 0, 0, (1 << 31) | (1 << 16)},
    {15, 0, 0, 1 << 16},
    {268435455, 1042612833, 542101086, (1 << 31) | (27 << 16)},
    {268435457, 1042612833, 542101086, 27 << 16},
    {1009, 0, 0, (1 << 31) | (1 << 16)},
    {1009, 0, 0, 1 << 16},
    {0, 0, 0, 1 << 31},
    {0, 0, 0, 0},
    {1316134913, 2328, 0, (1 << 31) | (13 << 16)},
    {1316134913, 2328, 0, 13 << 16},
    {55, 0, 0, (1 << 31) | (1 << 16)},
    {55, 0, 0, 1 << 16},
    {5000005, 0, 0, (1 << 31) | (5 << 16)},
    {5000005, 0, 0, 5 << 16},
    {1234567, 0, 0, (1 << 31) | (6 << 16)},
    {1234567, 0, 0, 6 << 16},
    {0, 0, 0, 0},
    {0, 0, 0, 0}};
int int_negative_res[NEGATE_TESTS] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                      0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1};

s21_decimal dec_mul_pi_e_src1[MUL_PIE_TESTS] = {
    {2257730743, 18587456, 170306079, 27 << 16},
    {2257730743, 18587456, 170306079, (27 << 16) | (1 << 31)},
    {2257730743, 18587456, 170306079, 27 << 16},
    {2257730743, 18587456, 170306079, (27 << 16) | (1 << 31)},
    {2257730743, 18587456, 170306079, 27 << 16},
    {2257730743, 18587456, 170306079, (27 << 16) | (1 << 31)},
    {2257730743, 18587456, 170306079, 27 << 16},
    {2257730743, 18587456, 170306079, (27 << 16) | (1 << 31)},
    {2257730743, 18587456, 170306079, 27 << 16},
    {2257730743, 18587456, 170306079, (27 << 16) | (1 << 31)},
    {3230419695, 825313643, 147358353, 27 << 16},
    {3230419695, 825313643, 147358353, (27 << 16) | (1 << 31)},
    {3230419695, 825313643, 147358353, 27 << 16},
    {3230419695, 825313643, 147358353, (27 << 16) | (1 << 31)},
    {3230419695, 825313643, 147358353, 27 << 16},
    {3230419695, 825313643, 147358353, (27 << 16) | (1 << 31)},
    {3230419695, 825313643, 147358353, 27 << 16},
    {3230419695, 825313643, 147358353, (27 << 16) | (1 << 31)},
    {3230419695, 825313643, 147358353, 27 << 16},
    {3230419695, 825313643, 147358353, (27 << 16) | (1 << 31)}};
s21_decimal dec_mul_pi_e_src2[MUL_PIE_TESTS] = {
    {2257730743, 18587456, 170306079, 27 << 16},
    {2257730743, 18587456, 170306079, (27 << 16) | (1 << 31)},
    {3230419695, 825313643, 147358353, (27 << 16) | (1 << 31)},
    {3230419695, 825313643, 147358353, 27 << 16},
    {1, 0, 0, 0},
    {1, 0, 0, 1 << 31},
    {1, 0, 0, 1 << 31},
    {1, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {2257730743, 18587456, 170306079, 27 << 16},
    {2257730743, 18587456, 170306079, (27 << 16) | (1 << 31)},
    {3230419695, 825313643, 147358353, (27 << 16) | (1 << 31)},
    {3230419695, 825313643, 147358353, 27 << 16},
    {1, 0, 0, 0},
    {1, 0, 0, 1 << 31},
    {1, 0, 0, 1 << 31},
    {1, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0}};
s21_decimal dec_mul_pi_e_res[MUL_PIE_TESTS] = {
    {3747862134, 2841889338, 535032326, 27 << 16},
    {3747862134, 2841889338, 535032326, 27 << 16},
    {399733652, 3580175622, 462939919, (27 << 16) | (1 << 31)},
    {399733652, 3580175622, 462939919, (27 << 16) | (1 << 31)},
    {2257730743, 18587456, 170306079, 27 << 16},
    {2257730743, 18587456, 170306079, 27 << 16},
    {2257730743, 18587456, 170306079, (27 << 16) | (1 << 31)},
    {2257730743, 18587456, 170306079, (27 << 16) | (1 << 31)},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {399733652, 3580175622, 462939919, 27 << 16},
    {399733652, 3580175622, 462939919, 27 << 16},
    {3839876251, 2314723989, 4005615337, (28 << 16) | (1 << 31)},
    {3839876251, 2314723989, 4005615337, (28 << 16) | (1 << 31)},
    {3230419695, 825313643, 147358353, 27 << 16},
    {3230419695, 825313643, 147358353, 27 << 16},
    {3230419695, 825313643, 147358353, (27 << 16) | (1 << 31)},
    {3230419695, 825313643, 147358353, (27 << 16) | (1 << 31)},
    {0, 0, 0, 0},
    {0, 0, 0, 0}};
int int_mul_pi_e[MUL_PIE_TESTS] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                   0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

s21_decimal dec_mul_error_cases_src1[MUL_ERR_TESTS] = {
    {0, 0, 1 << 31, 0},
    {0, 0, 1 << 31, 1 << 31},
    {0, 0, 1 << 31, 0},
    {0, 0, 1 << 31, 1 << 31},
    {2257730743, 18587456, 170306079, 27 << 16},
    {2257730743, 18587456, 170306079, (27 << 16) | (1 << 31)},
    {1, 0, 0, 15 << 16},
    {1, 0, 0, (1 << 31) | (15 << 16)},
    {1, 0, 0, 15 << 16},
    {1, 0, 0, (1 << 31) | (15 << 16)}};
s21_decimal dec_mul_error_cases_src2[MUL_ERR_TESTS] = {
    {0, 0, 1 << 31, 0},
    {0, 0, 1 << 31, 1 << 31},
    {0, 0, 1 << 31, 1 << 31},
    {0, 0, 1 << 31, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {1, 0, 0, 15 << 16},
    {1, 0, 0, (1 << 31) | (15 << 16)},
    {1, 0, 0, (1 << 31) | (15 << 16)},
    {1, 0, 0, 15 << 16}

};
s21_decimal dec_mul_error_cases_res[MUL_ERR_TESTS] = {
    {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0},
    {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
int int_mul_error[MUL_ERR_TESTS] = {1, 1, 2, 2, 0, 0, 2, 2, 2, 2};

s21_decimal dec_mul_round_src1[MUL_ROUND_TESTS] = {
    {268435461, 1042612833, 542101086, 1 << 16},
    {268435461, 1042612833, 542101086,
     (1 << 16) | (1 << 31)},  // 10000...0.5 * 11
    {268435461, 1042612833, 542101086, 1 << 16},
    {268435461, 1042612833, 542101086,
     (1 << 16) | (1 << 31)},  // 10000...0.5 * 11
    {268435461, 1042612833, 542101086, 1 << 16},
    {268435461, 1042612833, 542101086, (1 << 16) | (1 << 31)},
    {268435461, 1042612833, 542101086, 1 << 16},
    {268435461, 1042612833, 542101086, (1 << 16) | (1 << 31)},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {5, 0, 0, 28 << 16},
    {5, 0, 0, (28 << 16) | (1 << 31)},
    {5, 0, 0, 28 << 16},
    {5, 0, 0, (28 << 16) | (1 << 31)}};
s21_decimal dec_mul_round_src2[MUL_ROUND_TESTS] = {
    {11, 0, 0, 0},
    {11, 0, 0, 1 << 31},  // 10000...0.5 * 11
    {11, 0, 0, 1 << 31},
    {11, 0, 0, 0},  // 10000...0.5 * 11
    {9, 0, 0, 0},
    {9, 0, 0, 1 << 31},
    {9, 0, 0, 1 << 31},
    {9, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {11, 0, 0, 1 << 16},
    {11, 0, 0, (1 << 16) | (1 << 31)},
    {11, 0, 0, (1 << 16) | (1 << 31)},
    {11, 0, 0, 1 << 16}};
s21_decimal dec_mul_round_res[MUL_ROUND_TESTS] = {
    {4160749574, 3723854493, 596311194, 0},
    {4160749574, 3723854493, 596311194, 0},
    {4160749574, 3723854493, 596311194, 1 << 31},
    {4160749574, 3723854493, 596311194, 1 << 31},
    {671088644, 2656338468, 487890977, 0},
    {671088644, 2656338468, 487890977, 0},
    {671088644, 2656338468, 487890977, 1 << 31},
    {671088644, 2656338468, 487890977, 1 << 31},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {6, 0, 0, 28 << 16},
    {6, 0, 0, 28 << 16},
    {6, 0, 0, (28 << 16) | (1 << 31)},
    {6, 0, 0, (28 << 16) | (1 << 31)}};
int int_mul_round[MUL_ROUND_TESTS] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

s21_decimal comparison_src1[TESTS_COMP] = {
    {1410065409, 2, 0, 9 << 16},
    {1410065409, 2, 0, 9 << 16},
    {276447232, 23283, 0, 13 << 16},
    {276447232, 23283, 0, 13 << 16},
    {276447232, 23283, 0, 13 << 16},
    {0, 0, 0, 18 << 16},
    {0, 0, 0, 1 << 16},
    {0, 0, 0, 4 << 16},
    {276447232, 23283, 0, (1 << 31) | (13 << 16)},
    {276447232, 23283, 0, (1 << 31) | (13 << 16)},
    {276447232, 23283, 0, (1 << 31) | (13 << 16)},
    {1410065409, 2, 0, (1 << 31) | (9 << 16)},
    {1410065409, 2, 0, (1 << 31) | (9 << 16)}};
s21_decimal comparison_src2[TESTS_COMP] = {
    {276447232, 23283, 0, 13 << 16},
    {1410065409, 2, 0, 9 << 16},
    {1410065409, 2, 0, 9 << 16},
    {0, 0, 0, 13 << 16},
    {276447232, 23283, 0, (1 << 31) | (13 << 16)},
    {276447232, 23283, 0, 13 << 16},
    {0, 0, 0, 13 << 16},
    {276447232, 23283, 0, (1 << 31) | (13 << 16)},
    {276447232, 23283, 0, 13 << 16},
    {0, 0, 0, 0},
    {1410065409, 2, 0, (1 << 31) | (9 << 16)},
    {1410065409, 2, 0, (1 << 31) | (9 << 16)},
    {276447232, 23283, 0, (1 << 31) | (13 << 16)}};
int is_less_result[TESTS_COMP] = {0, 0, 1, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1};
int is_less_or_equal_result[TESTS_COMP] = {0, 1, 1, 0, 0, 1, 1,
                                           0, 1, 1, 0, 1, 1};
int is_greater_result[TESTS_COMP] = {1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0};
int is_greater_or_equal_result[TESTS_COMP] = {1, 1, 0, 1, 1, 0, 1,
                                              1, 0, 0, 1, 1, 0};
int is_equal_result[TESTS_COMP] = {0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0};
int is_not_equal_result[TESTS_COMP] = {1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1};
// jefferso arrays
int int_simple_arr_1[12] = {2,       1,     123,      256,    2147618, 3141689,
                            1000000, -1024, -2778855, 667777, 5645654, 8388608};

int int_simple_arr_2[12] = {6,        1,        16,         256,
                            7,        3141689,  100000,     -1024,
                            -2778855, 94858950, -234234234, 8388608};

float float_simple_arr_1[12] = {0.0001,   1.34545,  16.123,   2.56,
                                0.07,     3.141689, 10.0002,  -10.24,
                                -2778.55, 94.8550,  -23.4234, 838.860};

float float_simple_arr_2[12] = {-0.00003, 1.345,    16.9999,  256.001,
                                7.00003,  31416.89, 10000.12, -10241.2,
                                -27788.6, 9485.03,  -234.234, 83886.1};

float float_edge_cases[12] = {0,      1,    -1,    7e28,  -7e28,  2e-28,
                              -2e-28, 1e30, -1e30, 1e-30, -1e-30, 8388600};

float float_simple_edge_arr[12] = {1.1,     -1.1,     2.13,     -2.13,
                                   3.518,   -3.518,   4.3452,   -4.3452,
                                   5.13567, -5.13567, 6.121212, -6.121212};

float csharp_add_res1[12] = {0.00007,   2.69045,      33.1229,    258.561,
                             7.07003,   31420.031689, 10010.1202, -10251.44,
                             -30567.15, 9579.8850,    -257.6574,  84724.960};

float csharp_sub_res1[12] = {0.00013,  0.00045,       -0.8769,    -253.441,
                             -6.93003, -31413.748311, -9990.1198, 10230.96,
                             25010.05, -9390.1750,    210.8106,   -83047.240};

float csharp_addedge_res[12] = {1.1,     -0.1,      1.13,     -2.13,
                                3.518,   -3.518,    4.3452,   -4.3452,
                                5.13567, -5.135670, 6.121212, 8388593.878788};

float csharp_pi_div[12] = {
    15707963,  31415926,   255414.031250, 122718.460938, 14.628265, 9.999693,
    31.415926, -30679.615, -11.305349,    47.045535,     5.5646213, 3.74507028,
};

float massive_1[6] = {1.2, 9.9, 123.123, 0.4, 44.44, 56.5};

float massive_2[6] = {0.3, 6.6, 141.111, 8.2, 96.02, 11.5};

// clytemne cases
void floatToDecAddAssert(s21_decimal src, s21_decimal dst, int s21_res,
                         int res) {
  ck_assert_int_eq(s21_res, res);
  ck_assert_int_eq(src.bits[0], dst.bits[0]);
  ck_assert_int_eq(src.bits[1], dst.bits[1]);
  ck_assert_int_eq(src.bits[2], dst.bits[2]);
  ck_assert_int_eq(src.bits[3], dst.bits[3]);
}

START_TEST(s21_float_to_dec_edge_test) {
  s21_decimal opt;
  for (int i = 0; i < EDGE_TESTS; i++) {
    s21_init_decimal(&opt);
    int s21_res = s21_from_float_to_decimal(float_edge_arr[i], &opt);
    floatToDecAddAssert(dec_edge_arr[i], opt, s21_res, int_edge_res[i]);
  }
}
END_TEST

START_TEST(s21_float_to_dec_simple_test) {
  s21_decimal opt;
  for (int i = 0; i < SIMPLE_TESTS; i++) {
    s21_init_decimal(&opt);
    int s21_res = s21_from_float_to_decimal(float_simple_arr[i], &opt);
    floatToDecAddAssert(dec_simple_arr[i], opt, s21_res, int_simple_res[i]);
  }
}
END_TEST

START_TEST(s21_float_to_dec_trunc_test) {
  s21_decimal opt;
  for (int i = 0; i < TRUNC_TESTS; i++) {
    s21_init_decimal(&opt);
    int s21_res = s21_from_float_to_decimal(float_trunc_arr[i], &opt);
    floatToDecAddAssert(dec_trunc_arr[i], opt, s21_res, int_trunc_res[i]);
  }
}
END_TEST

START_TEST(s21_floor_test) {
  s21_decimal opt;
  for (int i = 0; i < FLOOR_TESTS; i++) {
    s21_init_decimal(&opt);
    int s21_res = s21_floor(dec_floor_src_arr[i], &opt);
    floatToDecAddAssert(dec_floor_dst_arr[i], opt, s21_res, int_floor_res[i]);
  }
}
END_TEST

START_TEST(s21_round_test) {
  s21_decimal opt;
  for (int i = 0; i < ROUND_TESTS; i++) {
    s21_init_decimal(&opt);
    int s21_res = s21_round(dec_round_src_arr[i], &opt);
    floatToDecAddAssert(dec_round_dst_arr[i], opt, s21_res, int_round_res[i]);
  }
}
END_TEST

START_TEST(s21_truncate_test) {
  s21_decimal opt;
  for (int i = 0; i < TRUNCATE_TESTS; i++) {
    s21_init_decimal(&opt);

    int s21_res = s21_truncate(dec_truncate_src_arr[i], &opt);

    floatToDecAddAssert(dec_truncate_dst_arr[i], opt, s21_res,
                        int_truncate_res[i]);
  }
}
END_TEST

START_TEST(s21_negative_test) {
  s21_decimal opt;
  for (int i = 0; i < NEGATE_TESTS; i++) {
    s21_init_decimal(&opt);
    int s21_res = s21_negate(dec_negative_src_arr[i], &opt);
    floatToDecAddAssert(dec_negative_dst_arr[i], opt, s21_res,
                        int_negative_res[i]);
  }
}
END_TEST

START_TEST(s21_mul_pi_e_test) {
  s21_decimal opt;
  for (int i = 0; i < MUL_PIE_TESTS; i++) {
    s21_init_decimal(&opt);

    int s21_res = s21_mul(dec_mul_pi_e_src1[i], dec_mul_pi_e_src2[i], &opt);
    floatToDecAddAssert(dec_mul_pi_e_res[i], opt, s21_res, int_mul_pi_e[i]);
  }
}
END_TEST

START_TEST(s21_mul_err_test) {
  s21_decimal opt;
  for (int i = 0; i < MUL_ERR_TESTS; i++) {
    s21_init_decimal(&opt);
    int s21_res =
        s21_mul(dec_mul_error_cases_src1[i], dec_mul_error_cases_src2[i], &opt);
    floatToDecAddAssert(dec_mul_error_cases_res[i], opt, s21_res,
                        int_mul_error[i]);
  }
}
END_TEST

START_TEST(s21_mul_round_test) {
  s21_decimal opt;
  for (int i = 0; i < MUL_ROUND_TESTS; i++) {
    s21_init_decimal(&opt);
    int s21_res = s21_mul(dec_mul_round_src1[i], dec_mul_round_src2[i], &opt);
    floatToDecAddAssert(dec_mul_round_res[i], opt, s21_res, int_mul_round[i]);
  }
}
END_TEST

START_TEST(s21_mul_float_test) {
  s21_decimal a, b, res, orig;
  float s21_res;
  int out;
  for (int i = 0; i < 12; i++) {
    s21_init_decimal(&a);
    s21_init_decimal(&b);
    s21_init_decimal(&res);
    s21_from_float_to_decimal(float_simple_arr_1[i], &a);
    s21_from_float_to_decimal(float_simple_arr_2[i], &b);
    out = s21_mul(a, b, &res);

    float original = float_simple_arr_1[i] * float_simple_arr_2[i];
    s21_from_decimal_to_float(res, &s21_res);

    ck_assert_float_eq_tol(original, s21_res, 1e6);
    ck_assert_int_eq(out, float_mul_out[i]);
  }
}
END_TEST

START_TEST(s21_is_less_test) {
  s21_decimal opt;
  for (int i = 0; i < TESTS_COMP; i++) {
    s21_init_decimal(&opt);

    int s21_res = s21_is_less(comparison_src1[i], comparison_src2[i]);
    ck_assert_int_eq(s21_res, is_less_result[i]);
  }
}
END_TEST
START_TEST(s21_is_less_or_equal_test) {
  s21_decimal opt;
  for (int i = 0; i < TESTS_COMP; i++) {
    s21_init_decimal(&opt);

    int s21_res = s21_is_less_or_equal(comparison_src1[i], comparison_src2[i]);
    ck_assert_int_eq(s21_res, is_less_or_equal_result[i]);
  }
}
END_TEST
START_TEST(s21_is_greater_test) {
  s21_decimal opt;
  for (int i = 0; i < TESTS_COMP; i++) {
    s21_init_decimal(&opt);

    int s21_res = s21_is_greater(comparison_src1[i], comparison_src2[i]);
    ck_assert_int_eq(s21_res, is_greater_result[i]);
  }
}
END_TEST
START_TEST(s21_is_greater_or_equal_test) {
  s21_decimal opt;
  for (int i = 0; i < TESTS_COMP; i++) {
    s21_init_decimal(&opt);

    int s21_res =
        s21_is_greater_or_equal(comparison_src1[i], comparison_src2[i]);
    ck_assert_int_eq(s21_res, is_greater_or_equal_result[i]);
  }
}
END_TEST
START_TEST(s21_is_equal_test) {
  s21_decimal opt;
  for (int i = 0; i < TESTS_COMP; i++) {
    s21_init_decimal(&opt);

    int s21_res = s21_is_equal(comparison_src1[i], comparison_src2[i]);
    ck_assert_int_eq(s21_res, is_equal_result[i]);
  }
}
END_TEST
START_TEST(s21_is_not_equal_test) {
  s21_decimal opt;
  for (int i = 0; i < TESTS_COMP; i++) {
    s21_init_decimal(&opt);

    int s21_res = s21_is_not_equal(comparison_src1[i], comparison_src2[i]);
    ck_assert_int_eq(s21_res, is_not_equal_result[i]);
  }
}
END_TEST
// jefferso cases

START_TEST(s21_add_int_test) {
  s21_decimal a, b, res;
  int s21_res;
  for (int i = 0; i < 12; i++) {
    s21_init_decimal(&a);
    s21_init_decimal(&b);
    s21_init_decimal(&res);
    s21_from_int_to_decimal(int_simple_arr_1[i], &a);
    s21_from_int_to_decimal(int_simple_arr_2[i], &b);
    s21_add(a, b, &res);
    s21_from_decimal_to_int(res, &s21_res);
    int original = int_simple_arr_1[i] + int_simple_arr_2[i];
    ck_assert_int_eq(original, s21_res);
  }
}
END_TEST

START_TEST(s21_sub_int_test) {
  s21_decimal a, b, res;
  int s21_res;
  for (int i = 0; i < 12; i++) {
    s21_init_decimal(&a);
    s21_init_decimal(&b);
    s21_init_decimal(&res);
    s21_from_int_to_decimal(int_simple_arr_1[i], &a);
    s21_from_int_to_decimal(int_simple_arr_2[i], &b);
    s21_sub(a, b, &res);
    s21_from_decimal_to_int(res, &s21_res);
    int original = int_simple_arr_1[i] - int_simple_arr_2[i];
    ck_assert_int_eq(original, s21_res);
  }
}
END_TEST

START_TEST(s21_add_float_test) {
  s21_decimal a, b, res;
  float s21_res;
  for (int i = 0; i < 12; i++) {
    s21_init_decimal(&a);
    s21_init_decimal(&b);
    s21_init_decimal(&res);
    s21_from_float_to_decimal(float_simple_arr_1[i], &a);
    s21_from_float_to_decimal(float_simple_arr_2[i], &b);
    if (float_simple_arr_1[i] < 0) setsign(&a, 1);
    if (float_simple_arr_2[i] < 0) setsign(&b, 1);
    s21_add(a, b, &res);
    s21_from_decimal_to_float(res, &s21_res);
    ck_assert_float_eq(csharp_add_res1[i], s21_res);
  }
}
END_TEST

START_TEST(s21_add_edge_float_test) {
  s21_decimal a, b, res;
  float s21_res;
  for (int i = 0; i < 12; i++) {
    s21_init_decimal(&a);
    s21_init_decimal(&b);
    s21_init_decimal(&res);
    s21_from_float_to_decimal(float_edge_cases[i], &a);
    s21_from_float_to_decimal(float_simple_edge_arr[i], &b);
    if (float_edge_cases[i] < 0) setsign(&a, 1);
    if (float_simple_edge_arr[i] < 0) setsign(&b, 1);
    s21_add(a, b, &res);
    s21_from_decimal_to_float(res, &s21_res);
    float original = float_edge_cases[i] + float_simple_edge_arr[i];
    if (i != 3 && i != 4) ck_assert_float_eq(csharp_addedge_res[i], s21_res);
    if (i == 3 || i == 4) ck_assert_float_eq(original, s21_res);
  }
}
END_TEST

START_TEST(s21_sub_float_test) {
  s21_decimal a, b, res;
  float s21_res;
  for (int i = 0; i < 12; i++) {
    s21_init_decimal(&a);
    s21_init_decimal(&b);
    s21_init_decimal(&res);
    s21_from_float_to_decimal(float_simple_arr_1[i], &a);
    s21_from_float_to_decimal(float_simple_arr_2[i], &b);
    if (float_simple_arr_1[i] < 0) setsign(&a, 1);
    if (float_simple_arr_2[i] < 0) setsign(&b, 1);
    s21_sub(a, b, &res);
    s21_from_decimal_to_float(res, &s21_res);
    ck_assert_float_eq(csharp_sub_res1[i], s21_res);
  }
}
END_TEST

START_TEST(s21_sub_edge_float_test) {
  s21_decimal a, b, res;
  float s21_res;
  for (int i = 0; i < 12; i++) {
    s21_init_decimal(&a);
    s21_init_decimal(&b);
    s21_init_decimal(&res);
    s21_from_float_to_decimal(float_edge_cases[i], &a);
    s21_from_float_to_decimal(float_simple_edge_arr[i], &b);
    if (float_edge_cases[i] < 0) setsign(&a, 1);
    if (float_simple_edge_arr[i] < 0) setsign(&b, 1);
    s21_sub(a, b, &res);
    s21_from_decimal_to_float(res, &s21_res);
    float original = float_edge_cases[i] - float_simple_edge_arr[i];
    if (i != 7 && i != 8) ck_assert_float_eq(original, s21_res);
    if (i == 7 || i == 8)
      ck_assert_float_eq(float_simple_edge_arr[i] * -1, s21_res);
  }
}
END_TEST

START_TEST(s21_div_int_test) {
  s21_decimal a, b, res;
  int s21_res = 0;
  int original = 0;
  for (int i = 0; i < 12; i++) {
    s21_init_decimal(&a);
    s21_init_decimal(&b);
    s21_init_decimal(&res);
    s21_from_int_to_decimal(int_simple_arr_1[i], &a);
    s21_from_int_to_decimal(int_simple_arr_2[i], &b);
    s21_div(a, b, &res);

    s21_from_decimal_to_int(res, &s21_res);
    ck_assert_int_eq(int_simple_arr_1[i] / int_simple_arr_2[i], s21_res);
  }
}
END_TEST

START_TEST(s21_div_float_test) {
  s21_decimal a, b, res;
  float s21_res = 0;
  int original = 0;
  for (int i = 0; i < 12; i++) {
    s21_init_decimal(&a);
    s21_init_decimal(&b);
    s21_init_decimal(&res);
    s21_from_float_to_decimal(float_simple_arr_1[i], &a);
    s21_from_float_to_decimal(float_simple_arr_2[i], &b);
    s21_div(a, b, &res);
    s21_from_decimal_to_float(res, &s21_res);
    if ((float_simple_arr_1[i] / float_simple_arr_2[i]) < 0) s21_res *= -1;
  }
}
END_TEST

START_TEST(s21_div_float_edge_test) {
  s21_decimal a, b, res;
  float s21_res = 0;
  int original = 0;
  for (int i = 0; i < 12; i++) {
    s21_init_decimal(&a);
    s21_init_decimal(&b);
    s21_init_decimal(&res);
    s21_from_float_to_decimal(float_edge_arr[i], &a);
    s21_from_float_to_decimal(float_simple_edge_arr[i], &b);
    s21_div(a, b, &res);
    s21_from_decimal_to_float(res, &s21_res);
    ck_assert_float_eq(float_edge_arr[i] / float_simple_edge_arr[i], s21_res);
  }
}
END_TEST

START_TEST(s21_div_massive_test) {
  s21_decimal decarr[3] = {{-1, -1, -1, 1 << 31},
                           {INT_MAX - 100000, -1, -1, 0},
                           {1, 0, 0, 28 << 16}};
  s21_decimal res;
  int code = 0;
  for (int i = 0; i < 12; i++) {
    s21_init_decimal(&res);
    code = s21_div(dec_edge_arr[i], dec_simple_arr[i], &res);
    ck_assert_int_eq(code, 0);
  }

  code = s21_div(dec_simple_arr[0], dec_mul_pi_e_src1[0], &res);
  ck_assert_int_eq(code, 0);

  code = s21_div(dec_mul_pi_e_src1[0], dec_mul_pi_e_src1[0], &res);
  ck_assert_int_eq(code, 0);

  code = s21_div(dec_mul_pi_e_src1[0], dec_mul_pi_e_src1[0], &res);
  ck_assert_int_eq(code, 0);

  code = s21_div(decarr[0], decarr[1], &res);

  ck_assert_int_eq(code, 0);
  float ff = 0;
  s21_from_decimal_to_float(res, &ff);
  ck_assert_float_eq(-1.0, ff);
  code = s21_div(decarr[1], decarr[0], &res);
  ff = 0;
  s21_from_decimal_to_float(res, &ff);
  ck_assert_float_eq(-1.0, ff);
  code = s21_div(decarr[0], decarr[2], &res);

  ff = 0;
  s21_from_decimal_to_float(res, &ff);
  ck_assert_float_eq(0, ff);

  s21_decimal *null_res = NULL;
  code = s21_div(dec_mul_pi_e_src1[0], dec_mul_pi_e_src1[0], null_res);
  ck_assert_int_eq(code, 4);
}
END_TEST

// 3141592653589793238462643383

START_TEST(s21_div_pi_test) {
  s21_decimal a, b;
  float s21_res = 0;
  int original = 0;
  int pi_1 = 314159265;
  int pi_2 = 53589;
  int pi_3 = 79323;
  int pi_4 = 84626;
  int pi_5 = 43383;

  s21_init_decimal(&a);
  s21_init_decimal(&b);
  s21_from_int_to_decimal(pi_1, &a);

  float ff = pi_2 / pow(10, 5);
  s21_from_float_to_decimal(ff, &b);
  s21_add(a, b, &a);
  for (int i = 0; i < 5; i++) {
    s21_mul_10_dec(&a);
  }

  ff = pi_3 / pow(10, 5);
  s21_from_float_to_decimal(ff, &b);
  s21_add(a, b, &a);
  setscale(&a, 0);

  ff = pi_4 / pow(10, 5);
  s21_from_float_to_decimal(ff, &b);
  s21_add(a, b, &a);
  setscale(&a, 0);

  ff = pi_5 / pow(10, 5);
  s21_from_float_to_decimal(ff, &b);
  s21_add(a, b, &a);
  setscale(&a, 0);

  float res = 0;
  s21_from_decimal_to_float(a, &res);
  setscale(&a, 21);

  for (int i = 0; i < 12; i++) {
    s21_init_decimal(&b);
    s21_from_int_to_decimal(int_simple_arr_1[i], &b);
    s21_div(a, b, &b);
    s21_from_decimal_to_float(b, &s21_res);
    ck_assert_float_eq(csharp_pi_div[i], s21_res);
  }
}
END_TEST

// robertom cases

START_TEST(Less1) {
  s21_decimal value_1 = {{0, 0, 0, 0b10000000000000000000000000000000}};
  s21_decimal value_2 = {{0, 0, 0, 0b00000000000000000000000000000000}};
  int s21_result = s21_is_less(value_1, value_2);
  int result = 0;
  ck_assert_int_eq(result, s21_result);
}
END_TEST

START_TEST(Less2) {
  s21_decimal value_1 = {
      {4294967295, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal value_2 = {
      {17, 8, 4294967295, 0b00000000000001010000000000000000}};
  int s21_result = s21_is_less(value_1, value_2);
  int result = 1;
  ck_assert_int_eq(result, s21_result);
}
END_TEST

START_TEST(Less3) {
  s21_decimal value_1 = {
      {0, 0, 4294967295, 0b00000000000000000000000000000000}};
  s21_decimal value_2 = {
      {17, 8, 4294967295, 0b00000000000100000000000000000000}};
  int s21_result = s21_is_less(value_1, value_2);
  int result = 0;
  ck_assert_int_eq(result, s21_result);
}
END_TEST

START_TEST(Less4) {
  s21_decimal value_1 = {{1, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal value_2 = {
      {17, 8, 4294967295, 0b10000000000100000000000000000000}};
  int s21_result = s21_is_less(value_1, value_2);
  int result = 0;
  ck_assert_int_eq(result, s21_result);
}
END_TEST

START_TEST(Less5) {
  s21_decimal value_1 = {{8, 0, 0, 0b10000000000000000000000000000000}};
  s21_decimal value_2 = {{17, 0, 0, 0b10000000000000000000000000000000}};
  int s21_result = s21_is_less(value_1, value_2);
  int result = 0;
  ck_assert_int_eq(result, s21_result);
}
END_TEST

START_TEST(Less6) {
  s21_decimal value_1 = {{8, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal value_2 = {{17, 0, 0, 0b00000000000000000000000000000000}};
  int s21_result = s21_is_less(value_1, value_2);
  int result = 1;
  ck_assert_int_eq(result, s21_result);
}
END_TEST

START_TEST(Less7) {
  s21_decimal value_1 = {{8, 0, 0, 0b00000000000001010000000000000000}};
  s21_decimal value_2 = {{7, 0, 0, 0b00000000000001000000000000000000}};
  int s21_result = s21_is_less(value_1, value_2);
  int result = 1;
  ck_assert_int_eq(result, s21_result);
}
END_TEST

START_TEST(Less8) {
  s21_decimal value_1 = {{80, 0, 0, 0b00000000000001010000000000000000}};
  s21_decimal value_2 = {{7, 0, 0, 0b00000000000001001000000000000000}};
  int s21_result = s21_is_less(value_1, value_2);
  int result = 0;
  ck_assert_int_eq(result, s21_result);
}
END_TEST

START_TEST(Less9) {
  s21_decimal value_1 = {{0, 80, 0, 0b00000000000000000000000000000000}};
  s21_decimal value_2 = {{0, 800, 0, 0b00000000000010110000000000000000}};
  int s21_result = s21_is_less(value_1, value_2);
  int result = 0;
  s21_decimal new_value_1 = {
      {0b00000000000000000000000000000000, 0b10100101001010001000000000000000,
       0b00000000000000000000011101000110, 0b00000000000010110000000000000000}};
  s21_decimal s21_new_value_1 = {
      {0, 2770894848, 1862, 0b00000000000010110000000000000000}};
  ck_assert_int_eq(result, s21_result);
  ck_assert_uint_eq(new_value_1.bits[0], s21_new_value_1.bits[0]);
  ck_assert_uint_eq(new_value_1.bits[1], s21_new_value_1.bits[1]);
  ck_assert_uint_eq(new_value_1.bits[2], s21_new_value_1.bits[2]);
  ck_assert_uint_eq(new_value_1.bits[3], s21_new_value_1.bits[3]);
}
END_TEST

START_TEST(Less10) {
  s21_decimal value_1 = {{0, 0, 80, 0b00000000000000100000000000000000}};
  s21_decimal value_2 = {
      {4294967295, 4294967295, 0, 0b00000000000000000000000000000000}};
  int s21_result = s21_is_less(value_1, value_2);
  int result = 1;
  s21_decimal new_value_2 = {
      {0b11111111111111111111111110011100, 0b11111111111111111111111111111111,
       0b00000000000000000000000001100011, 0b00000000000000100000000000000000}};
  s21_decimal s21_new_value_2 = {
      {4294967196, 4294967295, 99, 0b00000000000000100000000000000000}};
  ck_assert_int_eq(result, s21_result);
  ck_assert_uint_eq(new_value_2.bits[0], s21_new_value_2.bits[0]);
  ck_assert_uint_eq(new_value_2.bits[1], s21_new_value_2.bits[1]);
  ck_assert_uint_eq(new_value_2.bits[2], s21_new_value_2.bits[2]);
  ck_assert_uint_eq(new_value_2.bits[3], s21_new_value_2.bits[3]);
}
END_TEST

START_TEST(Less11) {
  s21_decimal value_1 = {{1, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal value_2 = {{10, 0, 0, 0b00000000000000010000000000000000}};
  int s21_result = s21_is_less(value_1, value_2);
  int result = 0;
  ck_assert_int_eq(result, s21_result);
}
END_TEST

START_TEST(Less12) {
  s21_decimal value_1 = {
      {4294967295, 4294967295, 4294967295, 0b00000000000000000000000000000000}};
  s21_decimal value_2 = {
      {4294967295, 4294967295, 4294967295, 0b00000000000000010000000000000000}};
  int s21_result = s21_is_less(value_1, value_2);
  int result = 0;
  ck_assert_int_eq(result, s21_result);
}
END_TEST

START_TEST(Less13) {
  s21_decimal value_1 = {{8, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal value_2 = {{7, 0, 0, 0b00000000000111000000000000000000}};
  int s21_result = s21_is_less(value_1, value_2);
  int result = 0;
  ck_assert_int_eq(result, s21_result);
}
END_TEST

START_TEST(Less_or_equal1) {
  s21_decimal value_1 = {{0, 0, 0, 0b10000000000000000000000000000000}};
  s21_decimal value_2 = {{0, 0, 0, 0b00000000000000000000000000000000}};
  int s21_result = s21_is_less_or_equal(value_1, value_2);
  int result = 1;
  ck_assert_int_eq(result, s21_result);
}
END_TEST

START_TEST(Less_or_equal2) {
  s21_decimal value_1 = {
      {4294967295, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal value_2 = {
      {17, 8, 4294967295, 0b00000000000001010000000000000000}};
  int s21_result = s21_is_less_or_equal(value_1, value_2);
  int result = 1;
  ck_assert_int_eq(result, s21_result);
}
END_TEST

START_TEST(Less_or_equal3) {
  s21_decimal value_1 = {
      {0, 0, 4294967295, 0b00000000000000000000000000000000}};
  s21_decimal value_2 = {
      {17, 8, 4294967295, 0b00000000000100000000000000000000}};
  int s21_result = s21_is_less_or_equal(value_1, value_2);
  int result = 0;
  ck_assert_int_eq(result, s21_result);
}
END_TEST

START_TEST(Less_or_equal4) {
  s21_decimal value_1 = {{1, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal value_2 = {
      {17, 8, 4294967295, 0b10000000000100000000000000000000}};
  int s21_result = s21_is_less_or_equal(value_1, value_2);
  int result = 0;
  ck_assert_int_eq(result, s21_result);
}
END_TEST

START_TEST(Less_or_equal5) {
  s21_decimal value_1 = {{8, 0, 0, 0b10000000000000000000000000000000}};
  s21_decimal value_2 = {{17, 0, 0, 0b10000000000000000000000000000000}};
  int s21_result = s21_is_less_or_equal(value_1, value_2);
  int result = 0;
  ck_assert_int_eq(result, s21_result);
}
END_TEST

START_TEST(Less_or_equal6) {
  s21_decimal value_1 = {{8, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal value_2 = {{17, 0, 0, 0b00000000000000000000000000000000}};
  int s21_result = s21_is_less_or_equal(value_1, value_2);
  int result = 1;
  ck_assert_int_eq(result, s21_result);
}
END_TEST

START_TEST(Less_or_equal7) {
  s21_decimal value_1 = {{8, 0, 0, 0b00000000000001010000000000000000}};
  s21_decimal value_2 = {{7, 0, 0, 0b00000000000001000000000000000000}};
  int s21_result = s21_is_less_or_equal(value_1, value_2);
  int result = 1;
  ck_assert_int_eq(result, s21_result);
}
END_TEST

START_TEST(Less_or_equal8) {
  s21_decimal value_1 = {{80, 0, 0, 0b00000000000001000000000000000000}};
  s21_decimal value_2 = {{7, 0, 0, 0b00000000000001000000000000000000}};
  int s21_result = s21_is_less_or_equal(value_1, value_2);
  int result = 0;
  ck_assert_int_eq(result, s21_result);
}
END_TEST

START_TEST(Less_or_equal9) {
  s21_decimal value_1 = {{0, 80, 0, 0b00000000000000000000000000000000}};
  s21_decimal value_2 = {{0, 800, 0, 0b00000000000010110000000000000000}};
  int s21_result = s21_is_less_or_equal(value_1, value_2);
  int result = 0;
  s21_decimal new_value_1 = {
      {0b00000000000000000000000000000000, 0b10100101001010001000000000000000,
       0b00000000000000000000011101000110, 0b00000000000010110000000000000000}};
  s21_decimal s21_new_value_1 = {
      {0, 2770894848, 1862, 0b00000000000010110000000000000000}};
  ck_assert_int_eq(result, s21_result);
  ck_assert_uint_eq(new_value_1.bits[0], s21_new_value_1.bits[0]);
  ck_assert_uint_eq(new_value_1.bits[1], s21_new_value_1.bits[1]);
  ck_assert_uint_eq(new_value_1.bits[2], s21_new_value_1.bits[2]);
  ck_assert_uint_eq(new_value_1.bits[3], s21_new_value_1.bits[3]);
}
END_TEST

START_TEST(Less_or_equal10) {
  s21_decimal value_1 = {{0, 0, 80, 0b00000000000000100000000000000000}};
  s21_decimal value_2 = {
      {4294967295, 4294967295, 0, 0b00000000000000000000000000000000}};
  int s21_result = s21_is_less_or_equal(value_1, value_2);
  int result = 1;
  s21_decimal new_value_2 = {
      {0b11111111111111111111111110011100, 0b11111111111111111111111111111111,
       0b00000000000000000000000001100011, 0b00000000000000100000000000000000}};
  s21_decimal s21_new_value_2 = {
      {4294967196, 4294967295, 99, 0b00000000000000100000000000000000}};
  ck_assert_int_eq(result, s21_result);
  ck_assert_uint_eq(new_value_2.bits[0], s21_new_value_2.bits[0]);
  ck_assert_uint_eq(new_value_2.bits[1], s21_new_value_2.bits[1]);
  ck_assert_uint_eq(new_value_2.bits[2], s21_new_value_2.bits[2]);
  ck_assert_uint_eq(new_value_2.bits[3], s21_new_value_2.bits[3]);
}
END_TEST

START_TEST(Less_or_equal11) {
  s21_decimal value_1 = {
      {4294967295, 4294967295, 4294967295, 0b00000000000000000000000000000000}};
  s21_decimal value_2 = {
      {4294967295, 4294967295, 4294967295, 0b00000000000000010000000000000000}};
  int s21_result = s21_is_less_or_equal(value_1, value_2);
  int result = 0;
  ck_assert_int_eq(result, s21_result);
}
END_TEST

START_TEST(Less_or_equal12) {
  s21_decimal value_1 = {{1, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal value_2 = {{10, 0, 0, 0b00000000000000010000000000000000}};
  int s21_result = s21_is_less_or_equal(value_1, value_2);
  int result = 1;
  ck_assert_int_eq(result, s21_result);
}
END_TEST

START_TEST(Greater1) {
  s21_decimal value_1 = {{0, 0, 0, 0b10000000000000000000000000000000}};
  s21_decimal value_2 = {{0, 0, 0, 0b00000000000000000000000000000000}};
  int s21_result = s21_is_greater(value_1, value_2);
  int result = 0;
  ck_assert_int_eq(result, s21_result);
}
END_TEST

START_TEST(Greater2) {
  s21_decimal value_1 = {
      {4294967295, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal value_2 = {
      {17, 8, 4294967295, 0b00000000000001010000000000000000}};
  int s21_result = s21_is_greater(value_1, value_2);
  int result = 0;
  ck_assert_int_eq(result, s21_result);
}
END_TEST

START_TEST(Greater3) {
  s21_decimal value_1 = {
      {0, 0, 4294967295, 0b00000000000000000000000000000000}};
  s21_decimal value_2 = {
      {17, 8, 4294967295, 0b00000000000100000000000000000000}};
  int s21_result = s21_is_greater(value_1, value_2);
  int result = 1;
  ck_assert_int_eq(result, s21_result);
}
END_TEST

START_TEST(Greater4) {
  s21_decimal value_1 = {{1, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal value_2 = {
      {17, 8, 4294967295, 0b10000000000100000000000000000000}};
  int s21_result = s21_is_greater(value_1, value_2);
  int result = 1;
  ck_assert_int_eq(result, s21_result);
}
END_TEST

START_TEST(Greater5) {
  s21_decimal value_1 = {{8, 0, 0, 0b10000000000000000000000000000000}};
  s21_decimal value_2 = {{17, 0, 0, 0b10000000000000000000000000000000}};
  int s21_result = s21_is_greater(value_1, value_2);
  int result = 1;
  ck_assert_int_eq(result, s21_result);
}
END_TEST

START_TEST(Greater6) {
  s21_decimal value_1 = {{8, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal value_2 = {{17, 0, 0, 0b00000000000000000000000000000000}};
  int s21_result = s21_is_greater(value_1, value_2);
  int result = 0;
  ck_assert_int_eq(result, s21_result);
}
END_TEST

START_TEST(Greater7) {
  s21_decimal value_1 = {{8, 0, 0, 0b00000000000001010000000000000000}};
  s21_decimal value_2 = {{7, 0, 0, 0b00000000000001000000000000000000}};
  int s21_result = s21_is_greater(value_1, value_2);
  int result = 0;
  ck_assert_int_eq(result, s21_result);
}
END_TEST

START_TEST(Greater8) {
  s21_decimal value_1 = {{80, 0, 0, 0b00000000000001010000000000000000}};
  s21_decimal value_2 = {{7, 0, 0, 0b00000000000001001000000000000000}};
  int s21_result = s21_is_greater(value_1, value_2);
  int result = 1;
  ck_assert_int_eq(result, s21_result);
}
END_TEST

START_TEST(Greater9) {
  s21_decimal value_1 = {{0, 80, 0, 0b00000000000000000000000000000000}};
  s21_decimal value_2 = {{0, 800, 0, 0b00000000000010110000000000000000}};
  int s21_result = s21_is_greater(value_1, value_2);
  int result = 1;
  s21_decimal new_value_1 = {
      {0b00000000000000000000000000000000, 0b10100101001010001000000000000000,
       0b00000000000000000000011101000110, 0b00000000000010110000000000000000}};
  s21_decimal s21_new_value_1 = {
      {0, 2770894848, 1862, 0b00000000000010110000000000000000}};
  ck_assert_int_eq(result, s21_result);
  ck_assert_uint_eq(new_value_1.bits[0], s21_new_value_1.bits[0]);
  ck_assert_uint_eq(new_value_1.bits[1], s21_new_value_1.bits[1]);
  ck_assert_uint_eq(new_value_1.bits[2], s21_new_value_1.bits[2]);
  ck_assert_uint_eq(new_value_1.bits[3], s21_new_value_1.bits[3]);
}
END_TEST

START_TEST(Greater10) {
  s21_decimal value_1 = {{0, 0, 80, 0b00000000000000100000000000000000}};
  s21_decimal value_2 = {
      {4294967295, 4294967295, 0, 0b00000000000000000000000000000000}};
  int s21_result = s21_is_greater(value_1, value_2);
  int result = 0;
  s21_decimal new_value_2 = {
      {0b11111111111111111111111110011100, 0b11111111111111111111111111111111,
       0b00000000000000000000000001100011, 0b00000000000000100000000000000000}};
  s21_decimal s21_new_value_2 = {
      {4294967196, 4294967295, 99, 0b00000000000000100000000000000000}};
  ck_assert_int_eq(result, s21_result);
  ck_assert_uint_eq(new_value_2.bits[0], s21_new_value_2.bits[0]);
  ck_assert_uint_eq(new_value_2.bits[1], s21_new_value_2.bits[1]);
  ck_assert_uint_eq(new_value_2.bits[2], s21_new_value_2.bits[2]);
  ck_assert_uint_eq(new_value_2.bits[3], s21_new_value_2.bits[3]);
}
END_TEST

START_TEST(Greater11) {
  s21_decimal value_1 = {{1, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal value_2 = {{10, 0, 0, 0b00000000000000010000000000000000}};
  int s21_result = s21_is_greater(value_1, value_2);
  int result = 0;
  ck_assert_int_eq(result, s21_result);
}
END_TEST

START_TEST(Greater12) {
  s21_decimal value_1 = {
      {4294967295, 4294967295, 4294967295, 0b00000000000000000000000000000000}};
  s21_decimal value_2 = {
      {4294967295, 4294967295, 4294967295, 0b00000000000000010000000000000000}};
  int s21_result = s21_is_greater(value_1, value_2);
  int result = 1;
  ck_assert_int_eq(result, s21_result);
}
END_TEST

START_TEST(Greater_or_equal1) {
  s21_decimal value_1 = {{0, 0, 0, 0b10000000000000000000000000000000}};
  s21_decimal value_2 = {{0, 0, 0, 0b00000000000000000000000000000000}};
  int s21_result = s21_is_greater_or_equal(value_1, value_2);
  int result = 1;
  ck_assert_int_eq(result, s21_result);
}
END_TEST

START_TEST(Greater_or_equal2) {
  s21_decimal value_1 = {
      {4294967295, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal value_2 = {
      {17, 8, 4294967295, 0b00000000000001010000000000000000}};
  int s21_result = s21_is_greater_or_equal(value_1, value_2);
  int result = 0;
  ck_assert_int_eq(result, s21_result);
}
END_TEST

START_TEST(Greater_or_equal3) {
  s21_decimal value_1 = {
      {0, 0, 4294967295, 0b00000000000000000000000000000000}};
  s21_decimal value_2 = {
      {17, 8, 4294967295, 0b00000000000100000000000000000000}};
  int s21_result = s21_is_greater_or_equal(value_1, value_2);
  int result = 1;
  ck_assert_int_eq(result, s21_result);
}
END_TEST

START_TEST(Greater_or_equal4) {
  s21_decimal value_1 = {{1, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal value_2 = {
      {17, 8, 4294967295, 0b10000000000100000000000000000000}};
  int s21_result = s21_is_greater_or_equal(value_1, value_2);
  int result = 1;
  ck_assert_int_eq(result, s21_result);
}
END_TEST

START_TEST(Greater_or_equal5) {
  s21_decimal value_1 = {{8, 0, 0, 0b10000000000000000000000000000000}};
  s21_decimal value_2 = {{17, 0, 0, 0b10000000000000000000000000000000}};
  int s21_result = s21_is_greater_or_equal(value_1, value_2);
  int result = 1;
  ck_assert_int_eq(result, s21_result);
}
END_TEST

START_TEST(Greater_or_equal6) {
  s21_decimal value_1 = {{8, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal value_2 = {{17, 0, 0, 0b00000000000000000000000000000000}};
  int s21_result = s21_is_greater_or_equal(value_1, value_2);
  int result = 0;
  ck_assert_int_eq(result, s21_result);
}
END_TEST

START_TEST(Greater_or_equal7) {
  s21_decimal value_1 = {{8, 0, 0, 0b00000000000001010000000000000000}};
  s21_decimal value_2 = {{7, 0, 0, 0b00000000000001000000000000000000}};
  int s21_result = s21_is_greater_or_equal(value_1, value_2);
  int result = 0;
  ck_assert_int_eq(result, s21_result);
}
END_TEST

START_TEST(Greater_or_equal8) {
  s21_decimal value_1 = {{80, 0, 0, 0b00000000000001010000000000000000}};
  s21_decimal value_2 = {{7, 0, 0, 0b00000000000001001000000000000000}};
  int s21_result = s21_is_greater_or_equal(value_1, value_2);
  int result = 1;
  ck_assert_int_eq(result, s21_result);
}
END_TEST

START_TEST(Greater_or_equal9) {
  s21_decimal value_1 = {{0, 80, 0, 0b00000000000000000000000000000000}};
  s21_decimal value_2 = {{0, 800, 0, 0b00000000000010110000000000000000}};
  int s21_result = s21_is_greater_or_equal(value_1, value_2);
  int result = 1;
  s21_decimal new_value_1 = {
      {0b00000000000000000000000000000000, 0b10100101001010001000000000000000,
       0b00000000000000000000011101000110, 0b00000000000010110000000000000000}};
  s21_decimal s21_new_value_1 = {
      {0, 2770894848, 1862, 0b00000000000010110000000000000000}};
  ck_assert_int_eq(result, s21_result);
  ck_assert_uint_eq(new_value_1.bits[0], s21_new_value_1.bits[0]);
  ck_assert_uint_eq(new_value_1.bits[1], s21_new_value_1.bits[1]);
  ck_assert_uint_eq(new_value_1.bits[2], s21_new_value_1.bits[2]);
  ck_assert_uint_eq(new_value_1.bits[3], s21_new_value_1.bits[3]);
}
END_TEST

START_TEST(Greater_or_equal10) {
  s21_decimal value_1 = {{0, 0, 80, 0b00000000000000100000000000000000}};
  s21_decimal value_2 = {
      {4294967295, 4294967295, 0, 0b00000000000000000000000000000000}};
  int s21_result = s21_is_greater_or_equal(value_1, value_2);
  int result = 0;
  s21_decimal new_value_2 = {
      {0b11111111111111111111111110011100, 0b11111111111111111111111111111111,
       0b00000000000000000000000001100011, 0b00000000000000100000000000000000}};
  s21_decimal s21_new_value_2 = {
      {4294967196, 4294967295, 99, 0b00000000000000100000000000000000}};
  ck_assert_int_eq(result, s21_result);
  ck_assert_uint_eq(new_value_2.bits[0], s21_new_value_2.bits[0]);
  ck_assert_uint_eq(new_value_2.bits[1], s21_new_value_2.bits[1]);
  ck_assert_uint_eq(new_value_2.bits[2], s21_new_value_2.bits[2]);
  ck_assert_uint_eq(new_value_2.bits[3], s21_new_value_2.bits[3]);
}
END_TEST

START_TEST(Greater_or_equal11) {
  s21_decimal value_1 = {{1, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal value_2 = {{10, 0, 0, 0b00000000000000010000000000000000}};
  int s21_result = s21_is_greater_or_equal(value_1, value_2);
  int result = 1;
  ck_assert_int_eq(result, s21_result);
}
END_TEST

START_TEST(Greater_or_equal12) {
  s21_decimal value_1 = {
      {4294967295, 4294967295, 4294967295, 0b00000000000000000000000000000000}};
  s21_decimal value_2 = {
      {4294967295, 4294967295, 4294967295, 0b00000000000000010000000000000000}};
  int s21_result = s21_is_greater_or_equal(value_1, value_2);
  int result = 1;
  ck_assert_int_eq(result, s21_result);
}
END_TEST

START_TEST(Equal1) {
  s21_decimal value_1 = {{0, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal value_2 = {{0, 0, 0, 0b00000000000000000000000000000000}};
  int s21_result = s21_is_equal(value_1, value_2);
  int result = 1;
  ck_assert_int_eq(result, s21_result);
}
END_TEST

START_TEST(Equal2) {
  s21_decimal value_1 = {
      {4294967295, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal value_2 = {
      {17, 8, 4294967295, 0b00000000000001010000000000000000}};
  int s21_result = s21_is_equal(value_1, value_2);
  int result = 0;
  ck_assert_int_eq(result, s21_result);
}
END_TEST

START_TEST(Equal3) {
  s21_decimal value_1 = {{1, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal value_2 = {{10, 0, 0, 0b00000000000000010000000000000000}};
  int s21_result = s21_is_equal(value_1, value_2);
  int result = 1;
  ck_assert_int_eq(result, s21_result);
}
END_TEST

START_TEST(Equal4) {
  s21_decimal value_1 = {{0, 80000, 0, 0b00000000000000100000000000000000}};
  s21_decimal value_2 = {{0, 800, 0, 0b00000000000000000000000000000000}};
  int s21_result = s21_is_greater_or_equal(value_1, value_2);
  int result = 1;
  ck_assert_int_eq(result, s21_result);
}
END_TEST

START_TEST(Equal5) {
  s21_decimal value_1 = {{0, 800, 1, 0b10000000000000000000000000000000}};
  s21_decimal value_2 = {{0, 800, 1, 0b00000000000000000000000000000000}};
  int s21_result = s21_is_greater_or_equal(value_1, value_2);
  int result = 0;
  ck_assert_int_eq(result, s21_result);
}
END_TEST

START_TEST(Not_equal1) {
  s21_decimal value_1 = {{0, 0, 0, 0b10000000000000000000000000000000}};
  s21_decimal value_2 = {{0, 0, 0, 0b00000000000000000000000000000000}};
  int s21_result = s21_is_not_equal(value_1, value_2);
  int result = 0;
  ck_assert_int_eq(result, s21_result);
}
END_TEST

START_TEST(Not_equal2) {
  s21_decimal value_1 = {
      {4294967295, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal value_2 = {
      {17, 8, 4294967295, 0b00000000000001010000000000000000}};
  int s21_result = s21_is_not_equal(value_1, value_2);
  int result = 1;
  ck_assert_int_eq(result, s21_result);
}
END_TEST

START_TEST(Not_equal3) {
  s21_decimal value_1 = {{1, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal value_2 = {{10, 0, 0, 0b00000000000000010000000000000000}};
  int s21_result = s21_is_not_equal(value_1, value_2);
  int result = 0;
  ck_assert_int_eq(result, s21_result);
}
END_TEST

START_TEST(Not_equal4) {
  s21_decimal value_1 = {{0, 80000, 0, 0b00000000000000100000000000000000}};
  s21_decimal value_2 = {{0, 800, 0, 0b00000000000000000000000000000000}};
  int s21_result = s21_is_not_equal(value_1, value_2);
  int result = 0;
  ck_assert_int_eq(result, s21_result);
}
END_TEST

START_TEST(Not_equal5) {
  s21_decimal value_1 = {{0, 80000, 0, 0b00000000000000100000000000000000}};
  s21_decimal value_2 = {{0, 800, 0, 0b10000000000000000000000000000000}};
  int s21_result = s21_is_greater_or_equal(value_1, value_2);
  int result = 1;
  ck_assert_int_eq(result, s21_result);
}
END_TEST

START_TEST(Not_equal6) {
  s21_decimal value_1 = {{0, 800, 1, 0b10000000000000000000000000000000}};
  s21_decimal value_2 = {{0, 800, 1, 0b00000000000000000000000000000000}};
  int s21_result = s21_is_not_equal(value_1, value_2);
  int result = 1;
  ck_assert_int_eq(result, s21_result);
}
END_TEST
// enedinae cases
START_TEST(int_to_decimal) {
  s21_decimal value;

  s21_from_int_to_decimal(0, &value);
  ck_assert_int_eq(value.bits[0], 0);
  ck_assert_int_eq(value.bits[1], 0);
  ck_assert_int_eq(value.bits[2], 0);
  ck_assert_int_eq(value.bits[3], 0);

  s21_from_int_to_decimal(-128, &value);
  ck_assert_int_eq(value.bits[0], 128);
  ck_assert_int_eq(value.bits[1], 0);
  ck_assert_int_eq(value.bits[2], 0);
  ck_assert_int_eq(value.bits[3], -2147483648);

  s21_from_int_to_decimal(127, &value);
  ck_assert_int_eq(value.bits[0], 127);
  ck_assert_int_eq(value.bits[1], 0);
  ck_assert_int_eq(value.bits[2], 0);
  ck_assert_int_eq(value.bits[3], 0);

  s21_from_int_to_decimal(-2147483648, &value);
  ck_assert_int_eq(value.bits[0], -2147483648);
  ck_assert_int_eq(value.bits[1], 0);
  ck_assert_int_eq(value.bits[2], 0);
  ck_assert_int_eq(value.bits[3], -2147483648);

  s21_from_int_to_decimal(2147483647, &value);
  ck_assert_int_eq(value.bits[0], 2147483647);
  ck_assert_int_eq(value.bits[1], 0);
  ck_assert_int_eq(value.bits[2], 0);
  ck_assert_int_eq(value.bits[3], 0);
}
END_TEST

START_TEST(decimal_to_int1) {
  s21_decimal src;
  int result = 0, number = 0;

  src.bits[0] = INT_MAX;
  src.bits[1] = 0;
  src.bits[2] = 0;
  src.bits[3] = 0;
  result = s21_from_decimal_to_int(src, &number);
  ck_assert_int_eq(number, INT_MAX);
  ck_assert_int_eq(result, 0);
}
END_TEST
START_TEST(decimal_to_int2) {
  s21_decimal src;
  int result = 0, number = 0;

  src.bits[0] = 133467;
  src.bits[1] = 0;
  src.bits[2] = 0;
  src.bits[3] = 0;
  result = s21_from_decimal_to_int(src, &number);
  ck_assert_int_eq(number, 133467);
  ck_assert_int_eq(result, 0);
}
END_TEST
START_TEST(decimal_to_int3) {
  s21_decimal src;
  int result = 0, number = 0;

  src.bits[0] = 2147483648;
  src.bits[1] = 0;
  src.bits[2] = 0;
  src.bits[3] = 0;
  setsign(&src, 1);
  result = s21_from_decimal_to_int(src, &number);
  ck_assert_int_eq(number, -2147483648);
  ck_assert_int_eq(result, 0);
}
END_TEST
START_TEST(decimal_to_int4) {
  s21_decimal src;
  int result = 0, number = 0;

  src.bits[0] = 123451234;
  src.bits[1] = 0;
  src.bits[2] = 0;
  src.bits[3] = 0;
  setsign(&src, 1);
  result = s21_from_decimal_to_int(src, &number);
  ck_assert_int_eq(number, -123451234);
  ck_assert_int_eq(result, 0);
}
END_TEST
START_TEST(decimal_to_int5) {
  s21_decimal src;
  int result = 0, number = 0;

  src.bits[0] = 18;
  src.bits[1] = 0;
  src.bits[2] = 0;
  src.bits[3] = 2147483648;
  result = s21_from_decimal_to_int(src, &number);
  ck_assert_int_eq(number, -18);
  ck_assert_int_eq(result, 0);

  src.bits[0] = 49;
  src.bits[1] = 0;
  src.bits[2] = 0;
  src.bits[3] = 0;
  setscale(&src, 1);
  setsign(&src, 1);
  result = s21_from_decimal_to_int(src, &number);
  ck_assert_int_eq(number, -4);
  ck_assert_int_eq(result, 0);
}
END_TEST
START_TEST(decimal_to_int6) {
  s21_decimal src;
  int result = 0, number = -2147483648;

  src.bits[0] = 2147483648;
  src.bits[1] = 0;
  src.bits[2] = 0;
  src.bits[3] = 0;
  setsign(&src, 1);
  result = s21_from_decimal_to_int(src, &number);
  ck_assert_int_eq(result, 0);

  src.bits[0] = 2147483649;
  src.bits[1] = 0;
  src.bits[2] = 0;
  src.bits[3] = 0;
  setsign(&src, 1);
  result = s21_from_decimal_to_int(src, &number);
  ck_assert_int_eq(result, 1);
}
END_TEST
START_TEST(decimal_to_int7) {
  s21_decimal src;
  int result = 0, number = 0;

  src.bits[0] = 4294967295;
  src.bits[1] = 0;
  src.bits[2] = 0;
  src.bits[3] = 0;
  setsign(&src, 1);
  result = s21_from_decimal_to_int(src, &number);
  ck_assert_int_eq(result, 1);
}
END_TEST
START_TEST(decimal_to_int8) {
  s21_decimal src;
  int result = 0, number = 0;

  src.bits[0] = 2147483647.342345;
  src.bits[1] = 0;
  src.bits[2] = 0;
  src.bits[3] = 0;
  result = s21_from_decimal_to_int(src, &number);
  ck_assert_int_eq(number, 2147483647);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(mod1) {
  s21_decimal src1, src2, res_mod;
  int a = 3;
  int b = 2;
  int res_origin = a % b;
  int res = 0, ret = 0;
  s21_from_int_to_decimal(a, &src1);
  s21_from_int_to_decimal(b, &src2);
  ret = s21_mod(src1, src2, &res_mod);
  s21_from_decimal_to_int(res_mod, &res);
  ck_assert_int_eq(res_origin, res);
  ck_assert_int_eq(ret, 0);
}
END_TEST
START_TEST(mod2) {
  s21_decimal src1, src2, res_mod;
  int a = 98765;
  int b = 1234;
  int res_origin = a % b;
  int res = 0, ret = 0;
  s21_from_int_to_decimal(a, &src1);
  s21_from_int_to_decimal(b, &src2);
  ret = s21_mod(src1, src2, &res_mod);
  s21_from_decimal_to_int(res_mod, &res);
  ck_assert_int_eq(res_origin, res);
  ck_assert_int_eq(ret, 0);
}
END_TEST
START_TEST(mod3) {
  s21_decimal src1, src2, res_mod;
  int a = 30198;
  int b = 20210;
  int res_origin = a % b;
  int res = 0, ret = 0;
  s21_from_int_to_decimal(a, &src1);
  s21_from_int_to_decimal(b, &src2);
  ret = s21_mod(src1, src2, &res_mod);

  s21_from_decimal_to_int(res_mod, &res);
  ck_assert_int_eq(res_origin, res);
  ck_assert_int_eq(ret, 0);
}
END_TEST
START_TEST(mod4) {
  s21_decimal src1, src2, res_mod;
  int a = -98765;
  int b = 1234;
  int res_origin = a % b;
  int res = 0, ret = 0;
  s21_from_int_to_decimal(a, &src1);
  s21_from_int_to_decimal(b, &src2);
  ret = s21_mod(src1, src2, &res_mod);
  s21_from_decimal_to_int(res_mod, &res);
  ck_assert_int_eq(res_origin, res);
  ck_assert_int_eq(ret, 0);
}
END_TEST
START_TEST(mod4_1) {
  s21_decimal src1, src2, res_mod;
  int a = -29;
  int b = 7;
  int res_origin = a % b;
  int res = 0, ret = 0;
  s21_from_int_to_decimal(a, &src1);
  s21_from_int_to_decimal(b, &src2);
  ret = s21_mod(src1, src2, &res_mod);
  s21_from_decimal_to_int(res_mod, &res);
  ck_assert_int_eq(res_origin, res);
  ck_assert_int_eq(ret, 0);
}
END_TEST
START_TEST(mod5) {
  s21_decimal src1, src2, res_mod;
  int a = 98765;
  int b = 127234;
  int res_origin = a % b;
  int res = 0, ret = 0;
  s21_from_int_to_decimal(a, &src1);
  s21_from_int_to_decimal(b, &src2);
  ret = s21_mod(src1, src2, &res_mod);
  s21_from_decimal_to_int(res_mod, &res);
  ck_assert_int_eq(res_origin, res);
  ck_assert_int_eq(ret, 0);
}
END_TEST
START_TEST(mod6) {
  s21_decimal src1, src2, res_mod;
  int a = 342576;
  int b = 1542134;
  int res_origin = a % b;
  int res = 0, ret = 0;
  s21_from_int_to_decimal(a, &src1);
  s21_from_int_to_decimal(b, &src2);
  ret = s21_mod(src1, src2, &res_mod);
  s21_from_decimal_to_int(res_mod, &res);
  ck_assert_int_eq(res_origin, res);
  ck_assert_int_eq(ret, 0);
}
END_TEST
START_TEST(mod7) {
  s21_decimal src1, src2, res_mod;
  float a = 1.2;
  float b = 0.3;
  float res_origin = fmod(a, b);
  float res = 0.0;
  int ret = 0;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  ret = s21_mod(src1, src2, &res_mod);
  s21_from_decimal_to_float(res_mod, &res);
  ck_assert_float_eq(res_origin, res);
  ck_assert_int_eq(ret, 0);
}
END_TEST
START_TEST(mod8) {
  s21_decimal src1, src2, res_mod;
  float a = 1.2;
  int b = 3;
  float res_origin = fmod(a, b);
  float res = 0, ret = 0;
  s21_from_float_to_decimal(a, &src1);
  s21_from_int_to_decimal(b, &src2);
  ret = s21_mod(src1, src2, &res_mod);
  s21_from_decimal_to_float(res_mod, &res);
  ck_assert_float_eq(res_origin, res);
  ck_assert_int_eq(ret, 0);

  a = 0, b = 2.2;
  res_origin = fmod(a, b);
  s21_from_float_to_decimal(a, &src1);
  s21_from_int_to_decimal(b, &src2);
  ret = s21_mod(src1, src2, &res_mod);
  s21_from_decimal_to_float(res_mod, &res);
  ck_assert_float_eq(res_origin, res);
  ck_assert_int_eq(ret, 0);

  a = 1.0 / 0.0, b = 2.2;
  s21_from_float_to_decimal(a, &src1);
  s21_from_int_to_decimal(b, &src2);
  ret = s21_mod(src1, src2, &res_mod);
  s21_from_decimal_to_float(res_mod, &res);
  ck_assert_int_eq(ret, 0);

  a = 2.0, b = 1 / 0.0;
  res_origin = fmod(a, b);
  s21_from_float_to_decimal(a, &src1);
  s21_from_int_to_decimal(b, &src2);
  ret = s21_mod(src1, src2, &res_mod);
  s21_from_decimal_to_float(res_mod, &res);
  ck_assert_float_eq(res_origin, res);
  ck_assert_int_eq(ret, 0);
}
END_TEST
START_TEST(mod9) {  // 0, inf, -inf, nan
  s21_decimal src1, src2, res_mod;
  float b = 1.0 / 0.0;
  int a = 3, ret = 0;
  float res_origin = fmod(a, b);
  float res = 0;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  ret = s21_mod(src1, src2, &res_mod);
  s21_from_decimal_to_float(res_mod, &res);
  ck_assert_float_eq(res_origin, res);
  ck_assert_int_eq(ret, 0);

  b = -1.0 / 0.0;
  a = 3;
  res_origin = fmod(a, b);
  res = 0;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  ret = s21_mod(src1, src2, &res_mod);
  s21_from_decimal_to_float(res_mod, &res);
  ck_assert_float_eq(res_origin, res);
  ck_assert_int_eq(ret, 0);

  a = 0.0 * 2 / 3 * 0.0;
  b = 3;
  res_origin = fmod(a, b);
  res = 0;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  ret = s21_mod(src1, src2, &res_mod);
  s21_from_decimal_to_float(res_mod, &res);
  ck_assert_float_eq(res_origin, res);
  ck_assert_int_eq(ret, 0);

  float c = 3 * 0.0, d = 2 * 0.0;
  b = c / d;
  a = 3;
  res_origin = fmod(a, b);
  res = 0;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  ret = s21_mod(src1, src2, &res_mod);
  s21_from_decimal_to_float(res_mod, &res);
  ck_assert_int_eq(ret, 0);
}
END_TEST

START_TEST(mod10) {
  s21_decimal src1, src2;
  s21_decimal *null_res = NULL;
  float b = 12;
  int a = 3, ret = 0;
  float res_origin = fmod(a, b);
  float res = 0;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  ret = s21_mod(src1, src2, null_res);
  ck_assert_int_eq(ret, 3);
}
END_TEST

// 3141592653589793238462643383

int main(void) {
  Suite *s1 = suite_create("Suite");
  SRunner *sr = srunner_create(s1);

  TCase *tc_main = tcase_create("tests");
  suite_add_tcase(s1, tc_main);

  tcase_add_test(tc_main, s21_float_to_dec_edge_test);
  tcase_add_test(tc_main, s21_float_to_dec_simple_test);
  tcase_add_test(tc_main, s21_float_to_dec_trunc_test);
  tcase_add_test(tc_main, s21_floor_test);
  tcase_add_test(tc_main, s21_round_test);
  tcase_add_test(tc_main, s21_truncate_test);
  tcase_add_test(tc_main, s21_negative_test);
  tcase_add_test(tc_main, s21_mul_float_test);
  tcase_add_test(tc_main, s21_mul_pi_e_test);
  tcase_add_test(tc_main, s21_mul_err_test);
  tcase_add_test(tc_main, s21_mul_round_test);
  tcase_add_test(tc_main, s21_mul_float_test);
  tcase_add_test(tc_main, s21_is_less_test);
  tcase_add_test(tc_main, s21_is_less_or_equal_test);
  tcase_add_test(tc_main, s21_is_greater_test);
  tcase_add_test(tc_main, s21_is_greater_or_equal_test);
  tcase_add_test(tc_main, s21_is_equal_test);
  tcase_add_test(tc_main, s21_is_not_equal_test);

  tcase_add_test(tc_main, s21_add_int_test);
  tcase_add_test(tc_main, s21_sub_int_test);
  tcase_add_test(tc_main, s21_add_float_test);
  tcase_add_test(tc_main, s21_sub_float_test);
  tcase_add_test(tc_main, s21_add_edge_float_test);
  tcase_add_test(tc_main, s21_sub_edge_float_test);
  tcase_add_test(tc_main, s21_div_int_test);
  tcase_add_test(tc_main, s21_div_float_test);
  tcase_add_test(tc_main, s21_div_pi_test);
  tcase_add_test(tc_main, s21_div_massive_test);
  tcase_add_test(tc_main, Less1);
  tcase_add_test(tc_main, Less2);
  tcase_add_test(tc_main, Less3);
  tcase_add_test(tc_main, Less4);
  tcase_add_test(tc_main, Less5);
  tcase_add_test(tc_main, Less6);
  tcase_add_test(tc_main, Less7);
  tcase_add_test(tc_main, Less8);
  tcase_add_test(tc_main, Less9);
  tcase_add_test(tc_main, Less10);
  tcase_add_test(tc_main, Less11);
  tcase_add_test(tc_main, Less12);
  tcase_add_test(tc_main, Less13);
  tcase_add_test(tc_main, Less_or_equal1);
  tcase_add_test(tc_main, Less_or_equal2);
  tcase_add_test(tc_main, Less_or_equal3);
  tcase_add_test(tc_main, Less_or_equal4);
  tcase_add_test(tc_main, Less_or_equal5);
  tcase_add_test(tc_main, Less_or_equal6);
  tcase_add_test(tc_main, Less_or_equal7);
  tcase_add_test(tc_main, Less_or_equal8);
  tcase_add_test(tc_main, Less_or_equal9);
  tcase_add_test(tc_main, Less_or_equal10);
  tcase_add_test(tc_main, Less_or_equal11);
  tcase_add_test(tc_main, Less_or_equal12);
  tcase_add_test(tc_main, Greater1);
  tcase_add_test(tc_main, Greater2);
  tcase_add_test(tc_main, Greater3);
  tcase_add_test(tc_main, Greater4);
  tcase_add_test(tc_main, Greater5);
  tcase_add_test(tc_main, Greater6);
  tcase_add_test(tc_main, Greater7);
  tcase_add_test(tc_main, Greater8);
  tcase_add_test(tc_main, Greater9);
  tcase_add_test(tc_main, Greater10);
  tcase_add_test(tc_main, Greater11);
  tcase_add_test(tc_main, Greater12);
  tcase_add_test(tc_main, Greater_or_equal1);
  tcase_add_test(tc_main, Greater_or_equal2);
  tcase_add_test(tc_main, Greater_or_equal3);
  tcase_add_test(tc_main, Greater_or_equal4);
  tcase_add_test(tc_main, Greater_or_equal5);
  tcase_add_test(tc_main, Greater_or_equal6);
  tcase_add_test(tc_main, Greater_or_equal7);
  tcase_add_test(tc_main, Greater_or_equal8);
  tcase_add_test(tc_main, Greater_or_equal9);
  tcase_add_test(tc_main, Greater_or_equal10);
  tcase_add_test(tc_main, Greater_or_equal11);
  tcase_add_test(tc_main, Greater_or_equal12);
  tcase_add_test(tc_main, Equal1);
  tcase_add_test(tc_main, Equal2);
  tcase_add_test(tc_main, Equal3);
  tcase_add_test(tc_main, Equal4);
  tcase_add_test(tc_main, Equal5);
  tcase_add_test(tc_main, Not_equal1);
  tcase_add_test(tc_main, Not_equal2);
  tcase_add_test(tc_main, Not_equal3);
  tcase_add_test(tc_main, Not_equal4);
  tcase_add_test(tc_main, Not_equal5);
  tcase_add_test(tc_main, Not_equal6);

  tcase_add_test(tc_main, int_to_decimal);

  tcase_add_test(tc_main, decimal_to_int1);
  tcase_add_test(tc_main, decimal_to_int2);
  tcase_add_test(tc_main, decimal_to_int3);
  tcase_add_test(tc_main, decimal_to_int4);
  tcase_add_test(tc_main, decimal_to_int5);
  tcase_add_test(tc_main, decimal_to_int6);
  tcase_add_test(tc_main, decimal_to_int7);
  tcase_add_test(tc_main, decimal_to_int8);

  tcase_add_test(tc_main, mod1);
  tcase_add_test(tc_main, mod2);
  tcase_add_test(tc_main, mod3);
  tcase_add_test(tc_main, mod4);
  tcase_add_test(tc_main, mod4_1);
  tcase_add_test(tc_main, mod5);
  tcase_add_test(tc_main, mod6);
  tcase_add_test(tc_main, mod7);
  tcase_add_test(tc_main, mod8);
  tcase_add_test(tc_main, mod9);
  tcase_add_test(tc_main, mod10);
  srunner_run_all(sr, CK_ENV);
  srunner_free(sr);

  return 0;
}
