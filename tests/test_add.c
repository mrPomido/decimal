#include "../tests_includes/s21_tests.h"

START_TEST(test_add_simple) {
    struct {
        int simple_decimal1;
        int simple_decimal2;
    } test_cases[] = {
        {0x5, 0x8},
        {580, 98807487},
        {58798700, 98807487},
        {0, 654498797},
        {775604, 0}
    };

    for (size_t i = 0; i < sizeof(test_cases) / sizeof(test_cases[0]); ++i) {
        int res = test_cases[i].simple_decimal1 + test_cases[i].simple_decimal2;
        char res_to_str[50];
        sprintf(res_to_str, "%d", res);

        s21_decimal decimal1 = {{test_cases[i].simple_decimal1, 0, 0, 0}};
        s21_decimal decimal2 = {{test_cases[i].simple_decimal2, 0, 0, 0}};
        s21_decimal result;
        s21_add(decimal1, decimal2, &result);

        ck_assert_str_eq(decimal_to_string(result), res_to_str);
    }
}
END_TEST

START_TEST(test_add_simple_neg) {
    struct {
        int simple_decimal1;
        int simple_decimal2;
        unsigned int flag1;
        unsigned int flag2;
        const char *expected_result;
    } cases[] = {
        {-775604,  56578,  0x80000000, 0, "702026"},
        {-775604, -56578, 0x80000000, 0x80000000, "-832182"},
        { 775604, -56578, 0, 0x80000000, "719026"},
    };

    for (size_t i = 0; i < sizeof(cases) / sizeof(cases[0]); i++) {
        int simple_decimal1 = cases[i].simple_decimal1;
        int simple_decimal2 = cases[i].simple_decimal2;
        int res = simple_decimal1 + simple_decimal2;
        char res_to_str[50];
        sprintf(res_to_str, "%d", res);

        s21_decimal decimal1 = {{abs(simple_decimal1), 0, 0, cases[i].flag1}};
        s21_decimal decimal2 = {{abs(simple_decimal2), 0, 0, cases[i].flag2}};
        s21_decimal result;
        s21_add(decimal1, decimal2, &result);

        ck_assert_str_eq(decimal_to_string(result), res_to_str);
    }
}
END_TEST

START_TEST(test_add_simple_check_code_combined) {
    struct {
        s21_decimal decimal1;
        s21_decimal decimal2;
    } cases[] = {
        {{{0x5, 0, 0, 0}}, {{0x8, 0, 0, 0}}},
        {{{85070, 0, 0, 0}}, {{798, 0, 0, 0}}},
        {{{0, 0, 0, 0}}, {{798, 0, 0, 0}}},
        {{{86798, 0, 0, 0}}, {{0, 0, 0, 0}}},
        {{{86798, 0, 0, 0x80000000}}, {{0, 0, 0, 0}}},
        {{{0, 0, 0, 0}}, {{484456, 0, 0, 0x80000000}}},
        {{{845664, 0, 0, 0x80000000}}, {{484456, 0, 0, 0x80000000}}},
    };

    for (size_t i = 0; i < sizeof(cases) / sizeof(cases[0]); i++) {
        s21_decimal result;
        int code = s21_add(cases[i].decimal1, cases[i].decimal2, &result);

        ck_assert_int_eq(code, 0);
    }
}
END_TEST

START_TEST(test_add_simple_float_equal_small_pow_combined) {
    struct {
        double simple_decimal1;
        double simple_decimal2;
        s21_decimal decimal1;
        s21_decimal decimal2;
    } cases[] = {
        {77.56, 589.12, {{7756, 0, 0, 0x20000}}, {{58912, 0, 0, 0x20000}}},
        {0.56, 0.12, {{56, 0, 0, 0x20000}}, {{12, 0, 0, 0x20000}}},
        {0.56, 58798.12, {{56, 0, 0, 0x20000}}, {{5879812, 0, 0, 0x20000}}},
        {549879.55, 0.12, {{54987955, 0, 0, 0x20000}}, {{12, 0, 0, 0x20000}}},
    };

    for (size_t i = 0; i < sizeof(cases) / sizeof(cases[0]); i++) {
        double res = cases[i].simple_decimal1 + cases[i].simple_decimal2;
        char res_to_str[50];
        sprintf(res_to_str, "%.2f", res);

        s21_decimal result;
        s21_add(cases[i].decimal1, cases[i].decimal2, &result);

        ck_assert_str_eq(decimal_to_string(result), res_to_str);
    }
}
END_TEST

START_TEST(test_add_simple_float_neg_equal_small_pow_combined) {
    struct {
        double simple_decimal1;
        double simple_decimal2;
        s21_decimal decimal1;
        s21_decimal decimal2;
    } cases[] = {
        {-549879.55, 0.12, {{54987955, 0, 0, 0x80020000}}, {{12, 0, 0, 0x20000}}},
        {549879.55, -0.12, {{54987955, 0, 0, 0x20000}}, {{12, 0, 0, 0x80020000}}},
        {-549879.55, -0.12, {{54987955, 0, 0, 0x80020000}}, {{12, 0, 0, 0x80020000}}},
    };

    for (size_t i = 0; i < sizeof(cases) / sizeof(cases[0]); i++) {
        double res = cases[i].simple_decimal1 + cases[i].simple_decimal2;
        char res_to_str[50];
        sprintf(res_to_str, "%.2f", res);

        s21_decimal result;
        s21_add(cases[i].decimal1, cases[i].decimal2, &result);

        ck_assert_str_eq(decimal_to_string(result), res_to_str);
    }
}
END_TEST

START_TEST(test_add_simple_float_diff_small_pow_combined) {
    struct {
        double simple_decimal1;
        double simple_decimal2;
        s21_decimal decimal1;
        s21_decimal decimal2;
        const char *format;
    } cases[] = {
        {78.569874, 9.48, {{78569874, 0, 0, 0x60000}}, {{948, 0, 0, 0x20000}}, "%.6f"},
        {78.569874, 9.48224568, {{78569874, 0, 0, 0x60000}}, {{948224568, 0, 0, 0x80000}}, "%.8f"},
        {-78.569874, 9.48224568, {{78569874, 0, 0, 0x80060000}}, {{948224568, 0, 0, 0x80000}}, "%.8f"},
    };

    for (size_t i = 0; i < sizeof(cases) / sizeof(cases[0]); i++) {
        double res = cases[i].simple_decimal1 + cases[i].simple_decimal2;
        char res_to_str[50];
        sprintf(res_to_str, cases[i].format, res);

        s21_decimal result;
        s21_add(cases[i].decimal1, cases[i].decimal2, &result);

        ck_assert_str_eq(decimal_to_string(result), res_to_str);
    }
}
END_TEST

START_TEST(test_add_decimal_combined) {
    struct {
        int decimal1[3];
        int decimal2[3];
        const char *res_to_str;
    } cases[] = {
        {{0b100001000, 0b1110011100, 0b10001}, {0b1011111001111, 0b1111000011100011, 0b1111111111}, "19184614105484231710935"},
        {{0b10111110001000, 0b1110011100, 0b100111101}, {0b1011110001001111, 0b111001000011100011, 0b1111100011111}, "152812828914308037536727"},
        {{0b1000011111000, 0b11100, 0b101}, {0b101001111, 0b1111100011, 0b111111001}, "9407839481985622872647"}
    };

    for (size_t i = 0; i < sizeof(cases) / sizeof(cases[0]); i++) {
        s21_decimal decimal1 = {{cases[i].decimal1[0], cases[i].decimal1[1], cases[i].decimal1[2], 0}};
        s21_decimal decimal2 = {{cases[i].decimal2[0], cases[i].decimal2[1], cases[i].decimal2[2], 0}};
        s21_decimal result;
        s21_add(decimal1, decimal2, &result);

        ck_assert_str_eq(decimal_to_string(result), cases[i].res_to_str);
    }
}
END_TEST

START_TEST(test_add_decimal_overbig_combined) {
    struct {
        int decimal1[3];
        int decimal2[3];
        int expected_code;
        const char *expected_str;
    } cases[] = {
        {{0b11111111111111111111111100001000, 0b11111111111111111111111100001000, 0b11111111111111111111111100001000},
         {0b1011111001111, 0b1111000011100011, 0b1111111111},
         1, NULL},
        {{0b11111111111111111111111100001000, 0b11111111111111111111111100001000, 0b11111111111111111111111100001000},
         {0b101111111111111001111, 0b111100001111111111100011, 0b1111111111111111111},
         1, NULL},
        {{0b11111111111111111111111111111111, 0b11111111111111111111111100001000, 0b11111111111111111111111100001000},
         {0b101111111111111001111, 0b111100001111111111100011, 0b1111111111111111111},
         1, NULL},
        {{0b11111111111111111111111111111111, 0b11111111111111111111111111111111, 0b11111111111111111111111111111111},
         {0b11111111111111111111111111111111, 0b11111111111111111111111111111111, 0b11111111111111111111111111111111},
         1, NULL},
        {{0b11111111111111111111111111111111, 0b11111111111111111111111111111111, 0b11111111111111111111111111111111},
         {0, 0, 0},
         0, "-79228162514264337593543950335"}
    };

    for (size_t i = 0; i < sizeof(cases) / sizeof(cases[0]); i++) {
        s21_decimal decimal1 = {{cases[i].decimal1[0], cases[i].decimal1[1], cases[i].decimal1[2], (i == 4 ? 0x80000000 : 0)}};
        s21_decimal decimal2 = {{cases[i].decimal2[0], cases[i].decimal2[1], cases[i].decimal2[2], 0}};
        s21_decimal result;
        int code = s21_add(decimal1, decimal2, &result);

        if (cases[i].expected_str) {
            ck_assert_str_eq(decimal_to_string(result), cases[i].expected_str);
        } else {
            ck_assert_int_eq(code, cases[i].expected_code);
        }
    }
}
END_TEST

START_TEST(test_add_decimal_overbig_combined_neg) {
    struct {
        int decimal1[3];
        int decimal2[3];
        int expected_code;
        int sign;
    } cases[] = {
        {{0b11111111111111111111111111111111, 0b11111111111111111111111100001000, 0b11111111111111111111111100001000},
         {0b101111111111111001111, 0b111100001111111111100011, 0b1111111111111111111},
         2, 0x80000000},
        {{0b11111111111111111111111111111111, 0b11111111111111111111111111111111, 0b11111111111111111111111111111111},
         {0b11111111111111111111111111111111, 0b11111111111111111111111111111111, 0b11111111111111111111111111111111},
         2, 0x80000000}
    };

    for (size_t i = 0; i < sizeof(cases) / sizeof(cases[0]); i++) {
        s21_decimal decimal1 = {{cases[i].decimal1[0], cases[i].decimal1[1], cases[i].decimal1[2], cases[i].sign}};
        s21_decimal decimal2 = {{cases[i].decimal2[0], cases[i].decimal2[1], cases[i].decimal2[2], cases[i].sign}};
        s21_decimal result;
        int code = s21_add(decimal1, decimal2, &result);
        ck_assert_int_eq(code, cases[i].expected_code);
    }
}
END_TEST

START_TEST(test_add_decimal_big1_neg) {
  int decimal1_1 = 0b11111111111111111111111111111111;
  int decimal1_2 = 0b11111111111111111111111100001000;
  int decimal1_3 = 0b11111111111111111111111100001000;

  int decimal2_1 = 0b101111111111111001111;
  int decimal2_2 = 0b111100001111111111100011;
  int decimal2_3 = 0b1111111111111111111;

  char res_to_str[50] = "-79218486569740542021904891952";

  s21_decimal decimal1 = {{decimal1_1, decimal1_2, decimal1_3, 0x80000000}};
  s21_decimal decimal2 = {{decimal2_1, decimal2_2, decimal2_3, 0}};
  s21_decimal result;
  s21_add(decimal1, decimal2, &result);

  ck_assert_str_eq(decimal_to_string(result), res_to_str);
}
END_TEST

START_TEST(test_add_decimal_big2_neg) {
  int decimal1_1 = 0b11111111111111111111111111111111;
  int decimal1_2 = 0b11111111111111111111111100001000;
  int decimal1_3 = 0b11111111111111111111111100001000;

  int decimal2_1 = 0b101111111111111001111;
  int decimal2_2 = 0b111100001111111111100011;
  int decimal2_3 = 0b1111111111111111111;

  char res_to_str[50] = "79218486569740542021904891952";

  s21_decimal decimal1 = {{decimal1_1, decimal1_2, decimal1_3, 0}};
  s21_decimal decimal2 = {{decimal2_1, decimal2_2, decimal2_3, 0x80000000}};
  s21_decimal result;
  s21_add(decimal1, decimal2, &result);

  ck_assert_str_eq(decimal_to_string(result), res_to_str);
}
END_TEST

START_TEST(test_add_decimal) {
    typedef struct {
        int decimal1_1;
        int decimal1_2;
        int decimal1_3;
        int decimal2_1;
        int decimal2_2;
        int decimal2_3;
        const char *expected_result;
    } AddDecimalTestParams;

    AddDecimalTestParams test_cases[] = {
        {0b0, 0b0, 0b0, 0b0, 0b0, 0b0, "0"},
        {0b0, 0b0, 0b11111111111111111111111111111111, 0b0, 0b0, 0b0, "79228162495817593519834398720"},
        {0b11111111111111111111111111111111, 0b11111111111111111111111111111111, 0b11111111111111111111111111111111,
         0b0, 0b0, 0b0, "79228162514264337593543950335"},
        {0b0, 0b0, 0b0, 0b11111111111111111111111111111111, 0b11111111111111111111111111111111, 0b11111111111111111111111111111111,
         "79228162514264337593543950335"},
        {0b1, 0b0, 0b0, 0b0, 0b0, 0b0, "1"}
    };

    for (size_t i = 0; i < sizeof(test_cases) / sizeof(test_cases[0]); i++) {
        AddDecimalTestParams test_case = test_cases[i];
        s21_decimal decimal1 = {{test_case.decimal1_1, test_case.decimal1_2, test_case.decimal1_3, 0}};
        s21_decimal decimal2 = {{test_case.decimal2_1, test_case.decimal2_2, test_case.decimal2_3, 0}};
        s21_decimal result;
        s21_add(decimal1, decimal2, &result);

        ck_assert_str_eq(decimal_to_string(result), test_case.expected_result);
    }
}
END_TEST

START_TEST(test_add_decimal_oversmall) {
    typedef struct {
        int decimal1_1;
        int decimal1_2;
        int decimal1_3;
        int decimal1_4;
        int decimal2_1;
        int decimal2_2;
        int decimal2_3;
        int decimal2_4;
        const char *expected_result;
        int expected_code;
    } AddDecimalTestParams;

    AddDecimalTestParams test_cases[] = {
        {0b1, 0b0, 0b0, 0b10000000000111000000000000000000, 0b0, 0b0, 0b0, 0b0, "-0.0000000000000000000000000001", 0},
        {0b1, 0b0, 0b0, 0b111000000000000000000, 0b0, 0b0, 0b0, 0b0, "0.0000000000000000000000000001", 0},
        {0b1, 0b0, 0b0, 0b10000000000111000000000000000000, 0b1, 0b0, 0b0, 0b00000000000111000000000000000000, "0", 0},
        {0b1, 0b0, 0b0, 0b10000000000111000000000000000000, 0b1, 0b0, 0b0, 0b10000000000111000000000000000000, "-0.0000000000000000000000000002", 0},
        {0b111111, 0b0, 0b0, 0b00000000000111000000000000000000, 0b111, 0b0, 0b0, 0b10000000000111000000000000000000, "0.0000000000000000000000000056", 0},
        {0b111111, 0b0, 0b0, 0b00000000001111000000000000000000, 0b111, 0b0, 0b0, 0b10000000000111000000000000000000, "", 4}
    };

    for (size_t i = 0; i < sizeof(test_cases) / sizeof(test_cases[0]); i++) {
        AddDecimalTestParams test_case = test_cases[i];
        s21_decimal decimal1 = {{test_case.decimal1_1, test_case.decimal1_2, test_case.decimal1_3, test_case.decimal1_4}};
        s21_decimal decimal2 = {{test_case.decimal2_1, test_case.decimal2_2, test_case.decimal2_3, test_case.decimal2_4}};
        s21_decimal result;
        int code = s21_add(decimal1, decimal2, &result);

        if (test_case.expected_code == 0) {
            ck_assert_str_eq(decimal_to_string(result), test_case.expected_result);
        } else {
            ck_assert_int_eq(code, test_case.expected_code);
        }
    }
}
END_TEST

START_TEST(test_add_decimal_smallpow) {
    typedef struct {
        int decimal1_1;
        int decimal1_2;
        int decimal1_3;
        int decimal1_4;
        int decimal2_1;
        int decimal2_2;
        int decimal2_3;
        int decimal2_4;
        const char *expected_result;
    } AddDecimalTestParams;

    AddDecimalTestParams test_cases[] = {
        {0b11111111111111111111111111111111, 0b11111111111111111111111111111111, 0b11111111111111111111111111111111, 0b00000000000111000000000000000000,
         0b1, 0b0, 0b0, 0b10000000000111000000000000000000, "7.9228162514264337593543950334"},
        {0b11111111111111111111111111111111, 0b11111111111111111111111111111111, 0b11111111111111111111111111111111, 0b00000000000111000000000000000000,
         0b1, 0b0, 0b0, 0b00000000000111000000000000000000, "7.922816251426433759354395034"},
        {0b11111111111111111111111111111110, 0b11111111111111111111111111111111, 0b11111111111111111111111111111111, 0b00000000000111000000000000000000,
         0b1, 0b0, 0b0, 0b00000000000111000000000000000000, "7.9228162514264337593543950335"},
        {0b11111111111111111111111111111111, 0b11111111111111111111111111111111, 0b11111111111111111111111111111111, 0b00000000000111000000000000000000,
         0b11111111111111111111111111111111, 0b0, 0b0, 0b00000000000111000000000000000000, "7.922816251426433759783891763"},
        {0b11111111111111111111111111111111, 0b11111111111111111111111111111111, 0b11111111111111111111111111111111, 0b00000000000111000000000000000000,
         0b11111111111111111111111111111111, 0b11111111111111111111111111111111, 0b11111111111111111111111111111111, 0b00000000000111000000000000000000, "15.845632502852867518708790067"}
    };

    for (size_t i = 0; i < sizeof(test_cases) / sizeof(test_cases[0]); i++) {
        AddDecimalTestParams test_case = test_cases[i];
        s21_decimal decimal1 = {{test_case.decimal1_1, test_case.decimal1_2, test_case.decimal1_3, test_case.decimal1_4}};
        s21_decimal decimal2 = {{test_case.decimal2_1, test_case.decimal2_2, test_case.decimal2_3, test_case.decimal2_4}};
        s21_decimal result;
        s21_add(decimal1, decimal2, &result);

        ck_assert_str_eq(decimal_to_string(result), test_case.expected_result);
    }
}
END_TEST

START_TEST(test_error_result_is_null) {
  s21_decimal decimal1 = {{0, 0, 0, 0}};
  s21_decimal decimal2 = {{0x1, 0, 0, 0}};
  int code = s21_add(decimal1, decimal2, NULL);

  ck_assert_int_eq(code, 4);
}
END_TEST

START_TEST(test_error1) {
  // степень 255 (показатель степени должен быть от 0 до 28)
  int decimal1_1 = 0b111;
  int decimal1_2 = 0b111;
  int decimal1_3 = 0b111;
  int decimal1_4 = 0b00000000111111110000000000000000;

  int decimal2_1 = 0b111;
  int decimal2_2 = 0b111;
  int decimal2_3 = 0b111;
  int decimal2_4 = 0b00000000000111000000000000000000;

  s21_decimal decimal1 = {{decimal1_1, decimal1_2, decimal1_3, decimal1_4}};
  s21_decimal decimal2 = {{decimal2_1, decimal2_2, decimal2_3, decimal2_4}};
  s21_decimal result;
  int code = s21_add(decimal1, decimal2, &result);

  ck_assert_int_eq(code, 4);
}
END_TEST

START_TEST(test_error2) {
  // биты 0-15 не нули
  // биты 24-30 не нули
  int decimal1_1 = 0b111;
  int decimal1_2 = 0b111;
  int decimal1_3 = 0b111;
  int decimal1_4 = 0b01100000000111000000000000000011;

  int decimal2_1 = 0b111;
  int decimal2_2 = 0b111;
  int decimal2_3 = 0b111;
  int decimal2_4 = 0b00000000000111000000000000000000;

  s21_decimal decimal1 = {{decimal1_1, decimal1_2, decimal1_3, decimal1_4}};
  s21_decimal decimal2 = {{decimal2_1, decimal2_2, decimal2_3, decimal2_4}};
  s21_decimal result;
  int code = s21_add(decimal1, decimal2, &result);

  ck_assert_int_eq(code, 4);
}
END_TEST

START_TEST(test_error3) {
  // все единицы
  int decimal1_1 = 0b111;
  int decimal1_2 = 0b111;
  int decimal1_3 = 0b111;
  int decimal1_4 = 0b11111111111111111111111111111111;

  int decimal2_1 = 0b111;
  int decimal2_2 = 0b111;
  int decimal2_3 = 0b111;
  int decimal2_4 = 0b11111111111111111111111111111111;

  s21_decimal decimal1 = {{decimal1_1, decimal1_2, decimal1_3, decimal1_4}};
  s21_decimal decimal2 = {{decimal2_1, decimal2_2, decimal2_3, decimal2_4}};
  s21_decimal result;
  int code = s21_add(decimal1, decimal2, &result);

  ck_assert_int_eq(code, 4);
}
END_TEST

Suite *suite_add(void) {
  Suite *s = suite_create("suite_add");
  TCase *tc = tcase_create("add_tc");

  tcase_add_test(tc, test_add_simple);
  tcase_add_test(tc, test_add_simple_neg);
  tcase_add_test(tc, test_add_simple_check_code_combined);
  tcase_add_test(tc, test_add_simple_float_equal_small_pow_combined);
  tcase_add_test(tc, test_add_simple_float_neg_equal_small_pow_combined);
  tcase_add_test(tc, test_add_simple_float_diff_small_pow_combined);
  tcase_add_test(tc, test_add_decimal_combined);
  tcase_add_test(tc, test_add_decimal_overbig_combined);
  tcase_add_test(tc, test_add_decimal_overbig_combined_neg);
  tcase_add_test(tc, test_add_decimal_big1_neg);
  tcase_add_test(tc, test_add_decimal_big2_neg);
  tcase_add_test(tc, test_add_decimal);
  tcase_add_test(tc, test_add_decimal_oversmall);
  tcase_add_test(tc, test_add_decimal_smallpow);
  tcase_add_test(tc, test_error_result_is_null);
  tcase_add_test(tc, test_error1);
  tcase_add_test(tc, test_error2);
  tcase_add_test(tc, test_error3);

  suite_add_tcase(s, tc);
  return s;
}