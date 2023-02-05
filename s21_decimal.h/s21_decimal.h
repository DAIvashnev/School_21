#include <limits.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEC_MAX 79228162514264337593543950335

// bits[0], bits[1], bits[2] содержат младшие, средние и старшие 32 бита
// 96-разрядного целого числа соответственно. bits[3] - 0-15 бит - не
// используются равны нулю; 16-23 бит - показатель степени 10; 24-30 бит - не
// используются равны нулю;31-ый бит - знак;

typedef struct {
  int bits[4];
} s21_decimal;

// a larger decimal to overcome overfill issues
typedef struct {
  int bits[6];
} s21_super_decimal;

// Convertions
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

int from_super_to_decimal(s21_super_decimal sresult, s21_decimal *result,
                          int scale, int sign);
void s21_dec_to_super(s21_decimal first, s21_super_decimal *super);

int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal source, int *dst);
// Comparison
int s21_is_equal(s21_decimal first, s21_decimal second);
int s21_is_not_equal(s21_decimal first, s21_decimal second);
int s21_is_less(s21_decimal, s21_decimal);
int s21_is_less_or_equal(s21_decimal first, s21_decimal second);

int s21_is_greater(s21_decimal first, s21_decimal second);
int s21_is_greater_or_equal(s21_decimal first, s21_decimal second);
int is_zero(s21_decimal value);
int is_super_zero(s21_super_decimal value);

int s21_is_super_equal(s21_super_decimal first, s21_super_decimal second);
int s21_is_super_less_or_equal(s21_super_decimal first,
                               s21_super_decimal second);
int s21_is_super_less(s21_super_decimal first, s21_super_decimal second);

int s21_is_incorrect(s21_decimal check);
// Init
void s21_init_decimal(s21_decimal *dst);
void s21_init_super_decimal(s21_super_decimal *dst);

void s21_adjust_scale(s21_super_decimal *first, s21_super_decimal *second,
                      int *scale_1, int *scale_2);
void s21_copy_dec(s21_decimal *dst, s21_decimal src);

// Bitwise operations
int s21_left_shift(s21_decimal *dst, int times);
void s21_right_shift(s21_decimal *dst, int times);
s21_decimal s21_or_dec(s21_decimal dst, s21_decimal add);
s21_decimal s21_and_dec(s21_decimal dst, s21_decimal add);
s21_decimal s21_xor_dec(s21_decimal dst, s21_decimal add);
s21_decimal s21_and_dec_inverted(s21_decimal dst, s21_decimal add);

void s21_right_super_shift(s21_super_decimal *dst, int times);
int s21_left_super_shift(s21_super_decimal *dst, int times);
s21_super_decimal s21_super_xor_dec(s21_super_decimal dst,
                                    s21_super_decimal add);
s21_super_decimal s21_super_and_dec(s21_super_decimal dst,
                                    s21_super_decimal add);
s21_super_decimal s21_super_and_dec_inverted(s21_super_decimal dst,
                                             s21_super_decimal add);

// Multiplication and division by 10
int s21_mul_10_dec(s21_decimal *dst);
void s21_dev_10_dec(s21_decimal *n);

int s21_mul_10_super_dec(s21_super_decimal *dst);
int s21_div_10_super(s21_super_decimal *dst);

// Arythmetics
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_add_super(s21_super_decimal value_1, s21_super_decimal value_2,
                  s21_super_decimal *result);
int s21_add_equal(s21_decimal value_1, s21_decimal value_2,
                  s21_decimal *result);

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub_super_equal(s21_super_decimal value_1, s21_super_decimal value_2,
                        s21_super_decimal *result);
int s21_sub_equal(s21_decimal value_1, s21_decimal value_2,
                  s21_decimal *result);
int s21_div_super(s21_super_decimal value_1, s21_super_decimal value_2,
                  s21_super_decimal *result);

int s21_mul_super(s21_super_decimal value_1, s21_super_decimal value_2,
                  s21_super_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
// Prints
void print_dec(s21_decimal x);
void print_super_dec(s21_super_decimal x);
void print_dec_binary(s21_decimal x);
void print_int_binary(unsigned int x);

// Bit setting and getting
int compare_bits(s21_decimal x, s21_decimal n);
int get_bit(s21_decimal x, int i);
void set_bit(s21_decimal *x, int i);
void clear_bit(s21_decimal *x, int i);
int get_bit_super(s21_super_decimal x, int i);

void setscale(s21_decimal *src, int scale);
int getscale(s21_decimal src);
void setsign(s21_decimal *value, int sign);
unsigned int getsign(s21_decimal src);
int checkinf(s21_decimal value);
// Other functions
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_floor(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);
int s21_bank_round_for_sub(s21_super_decimal svalue_1,
                           s21_super_decimal sresult, int scale_diff,
                           s21_decimal *result);