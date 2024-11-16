#ifndef S21_DECIMAL_H
#define S21_DECIMAL_H

#include <limits.h>
#include <locale.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct s21_decimal {
  unsigned int bits[4];
} s21_decimal;

typedef struct big_decimal {
  s21_decimal decimals[2];
} big_decimal;

#define MAX_FLOAT_TO_CONVERT 79228157791897854723898736640.0f
#define MIN_FLOAT_TO_CONVERT \
  0.00000000000000000000000000010000000031710768509710513471352647538147514756461109f

static const s21_decimal zero_val = {{0, 0, 0, 0}};
static const s21_decimal one_val = {{1, 0, 0, 0}};
static const s21_decimal ten_val = {{10, 0, 0, 0}};
static const s21_decimal max_val = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
static const s21_decimal zero_dot_five_val = {{5, 0, 0, 0x10000}};
static const s21_decimal min_val = {{0x1, 0x0, 0x0, 0x1C0000}};
static const s21_decimal max_int_val = {{0x7FFFFFFF, 0x0, 0x0, 0x0}};
static const s21_decimal min_int_val = {{0x80000000, 0x0, 0x0, 0x80000000}};

static const s21_decimal ten_pows[39] = {
    [0] = {{0x1, 0x0, 0x0, 0x0}},
    [1] = {{0xA, 0x0, 0x0, 0x0}},
    [2] = {{0x64, 0x0, 0x0, 0x0}},
    [3] = {{0x3E8, 0x0, 0x0, 0x0}},
    [4] = {{0x2710, 0x0, 0x0, 0x0}},
    [5] = {{0x186A0, 0x0, 0x0, 0x0}},
    [6] = {{0xF4240, 0x0, 0x0, 0x0}},
    [7] = {{0x989680, 0x0, 0x0, 0x0}},
    [8] = {{0x5F5E100, 0x0, 0x0, 0x0}},
    [9] = {{0x3B9ACA00, 0x0, 0x0, 0x0}},
    [10] = {{0x540BE400, 0x2, 0x0, 0x0}},
    [11] = {{0x4876E800, 0x17, 0x0, 0x0}},
    [12] = {{0xD4A51000, 0xE8, 0x0, 0x0}},
    [13] = {{0x4E72A000, 0x918, 0x0, 0x0}},
    [14] = {{0x107A4000, 0x5AF3, 0x0, 0x0}},
    [15] = {{0xA4C68000, 0x38D7E, 0x0, 0x0}},
    [16] = {{0x6FC10000, 0x2386F2, 0x0, 0x0}},
    [17] = {{0x5D8A0000, 0x1634578, 0x0, 0x0}},
    [18] = {{0xA7640000, 0xDE0B6B3, 0x0, 0x0}},
    [19] = {{0x89E80000, 0x8AC72304, 0x0, 0x0}},
    [20] = {{0x63100000, 0x6BC75E2D, 0x5, 0x0}},
    [21] = {{0xDEA00000, 0x35C9ADC5, 0x36, 0x0}},
    [22] = {{0xB2400000, 0x19E0C9BA, 0x21E, 0x0}},
    [23] = {{0xF6800000, 0x2C7E14A, 0x152D, 0x0}},
    [24] = {{0xA1000000, 0x1BCECCED, 0xD3C2, 0x0}},
    [25] = {{0x4A000000, 0x16140148, 0x84595, 0x0}},
    [26] = {{0xE4000000, 0xDCC80CD2, 0x52B7D2, 0x0}},
    [27] = {{0xE8000000, 0x9FD0803C, 0x33B2E3C, 0x0}},
    [28] = {{0x10000000, 0x3E250261, 0x204FCE5E, 0x0}},
    [29] = {{0xA0000000, 0x6D7217CA, 0x431E0FAE, 0x1}},
    [30] = {{0x40000000, 0x4674EDEA, 0x9F2C9CD0, 0xC}},
    [31] = {{0x80000000, 0xC0914B26, 0x37BE2022, 0x7E}},
    [32] = {{0x0, 0x85ACEF81, 0x2D6D415B, 0x4EE}},
    [33] = {{0x0, 0x38C15B0A, 0xC6448D93, 0x314D}},
    [34] = {{0x0, 0x378D8E64, 0xBEAD87C0, 0x1ED09}},
    [35] = {{0x0, 0x2B878FE8, 0x72C74D82, 0x134261}},
    [36] = {{0x0, 0xB34B9F10, 0x7BC90715, 0xC097CE}},
    [37] = {{0x0, 0xF436A0, 0xD5DA46D9, 0x785EE10}},
    [38] = {{0x0, 0x98A2240, 0x5A86C47A, 0x4B3B4CA8}}};

/*-----------------Функции по проекту---------------*/

// Arithmetic Operators
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

// Comparison Operators
int s21_is_less(s21_decimal, s21_decimal);
int s21_is_less_or_equal(s21_decimal, s21_decimal);
int s21_is_greater(s21_decimal, s21_decimal);
int s21_is_greater_or_equal(s21_decimal, s21_decimal);
int s21_is_equal(s21_decimal, s21_decimal);
int s21_is_not_equal(s21_decimal, s21_decimal);

// Convertors and parsers
int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

// Other functions
int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);

/*---------------------Вспомогательные функции---------------------*/

//Арифметические
int addition(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int subtraction(s21_decimal num1, s21_decimal num2, s21_decimal *result);
int division(big_decimal value_2b, big_decimal res, big_decimal remainder,
             s21_decimal *result);
int multiplication(s21_decimal num1, s21_decimal num2, s21_decimal *result);

//Бинарные
s21_decimal binary_sub(s21_decimal num1, s21_decimal num2);
big_decimal binary_sub_big(big_decimal num1, big_decimal num2);
s21_decimal binary_add(s21_decimal num1, s21_decimal num2);
big_decimal binary_add_big(big_decimal num1, big_decimal num2);
s21_decimal binary_xor(s21_decimal num1, s21_decimal num2);
s21_decimal binary_and(s21_decimal num1, s21_decimal num2);
big_decimal binary_mul(s21_decimal num1, s21_decimal num2);
big_decimal binary_mul_big(big_decimal num1, s21_decimal num2);
s21_decimal binary_not(s21_decimal num);
s21_decimal binary_div(s21_decimal num1, s21_decimal num2,
                       s21_decimal *remainder);
big_decimal binary_div_big(big_decimal num1, big_decimal num2,
                           big_decimal *remainder);
int binary_compare(s21_decimal num1, s21_decimal num2);
int binary_compare_big(big_decimal num1, big_decimal num2);
int binary_equal_zero(s21_decimal num);
s21_decimal binary_shift_right_one(s21_decimal num);
s21_decimal binary_shift_right(s21_decimal num, int shift);
big_decimal binary_shift_right_big(big_decimal num, int shift);
s21_decimal binary_shift_left_one(s21_decimal num);
s21_decimal binary_shift_left(s21_decimal num, int shift);
big_decimal binary_shift_left_big(big_decimal num, int shift);

//Геттеры
int get_sign(s21_decimal num);
int get_scale(s21_decimal num);
int get_shift_to_decimal(big_decimal num);
int check_max_bit(s21_decimal num);

//Сеттеры
void set_sign(s21_decimal *num, int sign);
void set_scale(s21_decimal *num, int scale);
int set_bit_int(int number, int index);
s21_decimal set_bit(s21_decimal num, int index);

//Булевы
int is_correct_decimal(s21_decimal num);
int bit_is_on(s21_decimal num, int index);
int bit_is_on_int(int number, int index);

//Конверторы
big_decimal decimal_to_big_decimal(s21_decimal num);
int float_exp_from_string(char *str);
s21_decimal float_string_to_decimal(char *str);
s21_decimal decimal_from_char(char c);

//Печать
/*void print_decimal(s21_decimal num);
void print_binary(unsigned int num);
void print_big_decimal(big_decimal num);*/

//Другие
void scaling(s21_decimal value_1, s21_decimal value_2, big_decimal *value_1b,
             big_decimal *value_2b, int scale1, int scale2);  // масштабирование
s21_decimal abs_val(s21_decimal num);                         // модуль
s21_decimal remove_trailing_zeros(s21_decimal value);  // удаление нулей в конце
int less(s21_decimal value_1, s21_decimal value_2);  // сравнение
s21_decimal round_banking(s21_decimal integral,
                          s21_decimal fractional);  // банковское округление
int calc_fractional(big_decimal *res, big_decimal value_2b,
                    big_decimal *remainder);  // вычисление дробной части
void decimal_round(s21_decimal *num);  // округление дробной части

#endif