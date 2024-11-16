#include "../tests_includes/s21_tests.h"

START_TEST(test_sub_simple) {
  s21_decimal decimal1[] = {
    {{0x5, 0, 0, 0}},
    {{580, 0, 0, 0}},
    {{58798700, 0, 0, 0}},
    {{0, 0, 0, 0}},
    {{775604, 0, 0, 0}}
  };

  s21_decimal decimal2[] = {
    {{0x8, 0, 0, 0}},
    {{98807487, 0, 0, 0}},
    {{98807487, 0, 0, 0}},
    {{654498797, 0, 0, 0}},
    {{0, 0, 0, 0}}
  };

  char *expected_results[] = {
    "-3",
    "-98806907",
    "-40008787",
    "-654498797",
    "775604"
  };

  s21_decimal result;
  int num_tests = sizeof(decimal1) / sizeof(decimal1[0]);

  for (int i = 0; i < num_tests; i++) {
    s21_sub(decimal1[i], decimal2[i], &result);
    ck_assert_str_eq(decimal_to_string(result), expected_results[i]);
  }
}
END_TEST

START_TEST(test_sub_simple_neg) {
  s21_decimal decimal1[] = {
    {{775604, 0, 0, 0x80000000}},
    {{775604, 0, 0, 0x80000000}},
    {{775604, 0, 0, 0}}
  };

  s21_decimal decimal2[] = {
    {{56578, 0, 0, 0}},
    {{56578, 0, 0, 0x80000000}},
    {{56578, 0, 0, 0x80000000}}
  };

  char *expected_results[] = {
    "-832182",
    "-719026",
    "832182"
  };

  s21_decimal result;
  int num_tests = sizeof(decimal1) / sizeof(decimal1[0]);

  for (int i = 0; i < num_tests; i++) {
    s21_sub(decimal1[i], decimal2[i], &result);
    ck_assert_str_eq(decimal_to_string(result), expected_results[i]);
  }
}
END_TEST



START_TEST(test_sub_simple_check_code) {
  // Массивы входных данных
  s21_decimal decimal1[] = {
    {{0x5, 0, 0, 0}},
    {{85070, 0, 0, 0}},
    {{0, 0, 0, 0}},
    {{86798, 0, 0, 0}},
    {{86798, 0, 0, 0x80000000}},
    {{0, 0, 0, 0}},
    {{845664, 0, 0, 0x80000000}}
  };

  s21_decimal decimal2[] = {
    {{0x8, 0, 0, 0}},
    {{798, 0, 0, 0}},
    {{798, 0, 0, 0}},
    {{0, 0, 0, 0}},
    {{0, 0, 0, 0}},
    {{484456, 0, 0, 0x80000000}},
    {{484456, 0, 0, 0x80000000}}
  };

  int expected_codes[] = {
    0, 0, 0, 0, 0, 0, 0
  };

  s21_decimal result;
  int num_tests = sizeof(decimal1) / sizeof(decimal1[0]);

  for (int i = 0; i < num_tests; i++) {
    int code = s21_sub(decimal1[i], decimal2[i], &result);
    ck_assert_int_eq(code, expected_codes[i]);
  }
}
END_TEST


START_TEST(test_sub_simple_float_equal_small_pow) {
  // Массивы входных данных
  s21_decimal decimal1[] = {
    {{7756, 0, 0, 0x20000}},
    {{56, 0, 0, 0x20000}},
    {{56, 0, 0, 0x20000}},
    {{54987955, 0, 0, 0x20000}}
  };

  s21_decimal decimal2[] = {
    {{58912, 0, 0, 0x20000}},
    {{12, 0, 0, 0x20000}},
    {{5879812, 0, 0, 0x20000}},
    {{12, 0, 0, 0x20000}}
  };

  // Ожидаемые строковые результаты
  char *expected_results[] = {
    "-511.56",
    "0.44",
    "-58797.56",
    "549879.43"
  };

  s21_decimal result;
  int num_tests = sizeof(decimal1) / sizeof(decimal1[0]);

  for (int i = 0; i < num_tests; i++) {
    s21_sub(decimal1[i], decimal2[i], &result);
    ck_assert_str_eq(decimal_to_string(result), expected_results[i]);
  }
}
END_TEST

START_TEST(test_sub_simple_float_neg_equal_small_pow) {
  // Массивы входных данных
  s21_decimal decimal1[] = {
    {{54987955, 0, 0, 0x80020000}},
    {{54987955, 0, 0, 0x20000}},
    {{54987955, 0, 0, 0x80020000}}
  };

  s21_decimal decimal2[] = {
    {{12, 0, 0, 0x20000}},
    {{12, 0, 0, 0x80020000}},
    {{12, 0, 0, 0x80020000}}
  };

  // Ожидаемые строковые результаты
  char *expected_results[] = {
    "-549879.67",
    "549879.67",
    "-549879.43"
  };

  s21_decimal result;
  int num_tests = sizeof(decimal1) / sizeof(decimal1[0]);

  for (int i = 0; i < num_tests; i++) {
    s21_sub(decimal1[i], decimal2[i], &result);
    ck_assert_str_eq(decimal_to_string(result), expected_results[i]);
  }
}
END_TEST

START_TEST(test_sub_simple_float_diff_small_pow) {
  // Массивы входных данных
  s21_decimal decimal1[] = {
    {{78569874, 0, 0, 0x60000}},
    {{78569874, 0, 0, 0x60000}}
  };

  s21_decimal decimal2[] = {
    {{948, 0, 0, 0x20000}},
    {{948224568, 0, 0, 0x80000}}
  };

  // Ожидаемые строковые результаты
  char *expected_results[] = {
    "69.089874",
    "69.08762832"
  };

  s21_decimal result;
  int num_tests = sizeof(decimal1) / sizeof(decimal1[0]);

  for (int i = 0; i < num_tests; i++) {
    s21_sub(decimal1[i], decimal2[i], &result);
    ck_assert_str_eq(decimal_to_string(result), expected_results[i]);
  }
}
END_TEST

START_TEST(test_sub_simple_float_neg_diff_small_pow) {
  double simple_decimal1 = -78.569874;
  double simple_decimal2 = 9.48224568;
  double res = simple_decimal1 - simple_decimal2;
  char res_to_str[50];
  sprintf(res_to_str, "%.8f", res);

  s21_decimal decimal1 = {{78569874, 0, 0, 0x80060000}};
  s21_decimal decimal2 = {{948224568, 0, 0, 0x80000}};
  s21_decimal result;
  s21_sub(decimal1, decimal2, &result);

  ck_assert_str_eq(decimal_to_string(result), res_to_str);
}
END_TEST

// START_TEST(test_sub_decimal1) {
//   int decimal1_1 = 0b100001000;
//   int decimal1_2 = 0b1110011100;
//   int decimal1_3 = 0b10001;

//   int decimal2_1 = 0b1011111001111;
//   int decimal2_2 = 0b1111000011100011;
//   int decimal2_3 = 0b1111111111;

//   char res_to_str[50] = "-18557424799041007392455";

//   s21_decimal decimal1 = {{decimal1_1, decimal1_2, decimal1_3, 0}};
//   s21_decimal decimal2 = {{decimal2_1, decimal2_2, decimal2_3, 0}};
//   s21_decimal result;
//   s21_sub(decimal1, decimal2, &result);

//   ck_assert_str_eq(decimal_to_string(result), res_to_str);
// }
// END_TEST

// START_TEST(test_sub_decimal2) {
//   int decimal1_1 = 0b10111110001000;
//   int decimal1_2 = 0b1110011100;
//   int decimal1_3 = 0b100111101;

//   int decimal2_1 = 0b1011110001001111;
//   int decimal2_2 = 0b111001000011100011;
//   int decimal2_3 = 0b1111100011111;

//   char res_to_str[50] = "-141117593163639082224839";

//   s21_decimal decimal1 = {{decimal1_1, decimal1_2, decimal1_3, 0}};
//   s21_decimal decimal2 = {{decimal2_1, decimal2_2, decimal2_3, 0}};
//   s21_decimal result;
//   s21_sub(decimal1, decimal2, &result);

//   ck_assert_str_eq(decimal_to_string(result), res_to_str);
// }
// END_TEST

// START_TEST(test_sub_decimal3) {
//   int decimal1_1 = 0b1000011111000;
//   int decimal1_2 = 0b11100;
//   int decimal1_3 = 0b101;

//   int decimal2_1 = 0b101001111;
//   int decimal2_2 = 0b1111100011;
//   int decimal2_3 = 0b111111001;

//   char res_to_str[50] = "-9223372041008009179223";

//   s21_decimal decimal1 = {{decimal1_1, decimal1_2, decimal1_3, 0}};
//   s21_decimal decimal2 = {{decimal2_1, decimal2_2, decimal2_3, 0}};
//   s21_decimal result;
//   s21_sub(decimal1, decimal2, &result);

//   ck_assert_str_eq(decimal_to_string(result), res_to_str);
// }
// END_TEST


START_TEST(test_sub_decimal) {
    s21_decimal decimal1[] = {
        {{0b100001000, 0b1110011100, 0b10001, 0}},
        {{0b10111110001000, 0b1110011100, 0b100111101, 0}},
        {{0b1000011111000, 0b11100, 0b101, 0}}
    };

    s21_decimal decimal2[] = {
        {{0b1011111001111, 0b1111000011100011, 0b1111111111, 0}},
        {{0b1011110001001111, 0b111001000011100011, 0b1111100011111, 0}},
        {{0b101001111, 0b1111100011, 0b111111001, 0}}
    };

    char *expected_results[] = {
        "-18557424799041007392455",
        "-141117593163639082224839",
        "-9223372041008009179223"
    };

    s21_decimal result;
    int num_tests = sizeof(decimal1) / sizeof(decimal1[0]);

    for (int i = 0; i < num_tests; i++) {
        s21_sub(decimal1[i], decimal2[i], &result);
        ck_assert_str_eq(decimal_to_string(result), expected_results[i]);
    }
}
END_TEST




START_TEST(test_sub_decimal_overbig1) {
  int decimal1_1 = 0b11111111111111111111111100001000;
  int decimal1_2 = 0b11111111111111111111111100001000;
  int decimal1_3 = 0b11111111111111111111111100001000;

  int decimal2_1 = 0b1011111001111;
  int decimal2_2 = 0b1111000011100011;
  int decimal2_3 = 0b1111111111;

  s21_decimal decimal1 = {{decimal1_1, decimal1_2, decimal1_3, 0x80000000}};
  s21_decimal decimal2 = {{decimal2_1, decimal2_2, decimal2_3, 0}};
  s21_decimal result;
  int code = s21_sub(decimal1, decimal2, &result);
  ck_assert_int_eq(code, 2);
}
END_TEST

START_TEST(test_sub_decimal_overbig2) {
  int decimal1_1 = 0b11111111111111111111111100001000;
  int decimal1_2 = 0b11111111111111111111111100001000;
  int decimal1_3 = 0b11111111111111111111111100001000;

  int decimal2_1 = 0b101111111111111001111;
  int decimal2_2 = 0b111100001111111111100011;
  int decimal2_3 = 0b1111111111111111111;

  s21_decimal decimal1 = {{decimal1_1, decimal1_2, decimal1_3, 0x80000000}};
  s21_decimal decimal2 = {{decimal2_1, decimal2_2, decimal2_3, 0}};
  s21_decimal result;
  int code = s21_sub(decimal1, decimal2, &result);
  ck_assert_int_eq(code, 2);
}
END_TEST

START_TEST(test_sub_decimal_overbig3) {
  int decimal1_1 = 0b11111111111111111111111111111111;
  int decimal1_2 = 0b11111111111111111111111100001000;
  int decimal1_3 = 0b11111111111111111111111100001000;

  int decimal2_1 = 0b101111111111111001111;
  int decimal2_2 = 0b111100001111111111100011;
  int decimal2_3 = 0b1111111111111111111;

  s21_decimal decimal1 = {{decimal1_1, decimal1_2, decimal1_3, 0x80000000}};
  s21_decimal decimal2 = {{decimal2_1, decimal2_2, decimal2_3, 0}};
  s21_decimal result;
  int code = s21_sub(decimal1, decimal2, &result);
  ck_assert_int_eq(code, 2);
}
END_TEST

START_TEST(test_sub_decimal_overbig4) {
  int decimal1_1 = 0b11111111111111111111111111111111;
  int decimal1_2 = 0b11111111111111111111111111111111;
  int decimal1_3 = 0b11111111111111111111111111111111;

  int decimal2_1 = 0b11111111111111111111111111111111;
  int decimal2_2 = 0b11111111111111111111111111111111;
  int decimal2_3 = 0b11111111111111111111111111111111;

  s21_decimal decimal1 = {{decimal1_1, decimal1_2, decimal1_3, 0x80000000}};
  s21_decimal decimal2 = {{decimal2_1, decimal2_2, decimal2_3, 0}};
  s21_decimal result;
  int code = s21_sub(decimal1, decimal2, &result);
  ck_assert_int_eq(code, 2);
}
END_TEST

START_TEST(test_sub_decimal_overbig5) {
  int decimal1_1 = 0b11111111111111111111111111111111;
  int decimal1_2 = 0b11111111111111111111111111111111;
  int decimal1_3 = 0b11111111111111111111111111111111;

  int decimal2_1 = 0b0;
  int decimal2_2 = 0b0;
  int decimal2_3 = 0b0;
  char res_to_str[] = "-79228162514264337593543950335";

  s21_decimal decimal1 = {{decimal1_1, decimal1_2, decimal1_3, 0x80000000}};
  s21_decimal decimal2 = {{decimal2_1, decimal2_2, decimal2_3, 0}};
  s21_decimal result;
  s21_sub(decimal1, decimal2, &result);
  ck_assert_str_eq(decimal_to_string(result), res_to_str);
}
END_TEST








START_TEST(test_sub_decimal_overbig1_neg) {
  int decimal1_1 = 0b11111111111111111111111111111111;
  int decimal1_2 = 0b11111111111111111111111100001000;
  int decimal1_3 = 0b11111111111111111111111100001000;

  int decimal2_1 = 0b101111111111111001111;
  int decimal2_2 = 0b111100001111111111100011;
  int decimal2_3 = 0b1111111111111111111;

  s21_decimal decimal1 = {{decimal1_1, decimal1_2, decimal1_3, 0x80000000}};
  s21_decimal decimal2 = {{decimal2_1, decimal2_2, decimal2_3, 0}};
  s21_decimal result;
  int code = s21_sub(decimal1, decimal2, &result);

  ck_assert_int_eq(code, 2);
}
END_TEST

START_TEST(test_sub_decimal_overbig2_neg) {
  int decimal1_1 = 0b11111111111111111111111111111111;
  int decimal1_2 = 0b11111111111111111111111111111111;
  int decimal1_3 = 0b11111111111111111111111111111111;

  int decimal2_1 = 0b11111111111111111111111111111111;
  int decimal2_2 = 0b11111111111111111111111111111111;
  int decimal2_3 = 0b11111111111111111111111111111111;

  s21_decimal decimal1 = {{decimal1_1, decimal1_2, decimal1_3, 0x80000000}};
  s21_decimal decimal2 = {{decimal2_1, decimal2_2, decimal2_3, 0}};
  s21_decimal result;
  int code = s21_sub(decimal1, decimal2, &result);
  ck_assert_int_eq(code, 2);
}
END_TEST

START_TEST(test_sub_decimal_big1_neg) {
  int decimal1_1 = 0b11111111111111111111111111111111;
  int decimal1_2 = 0b11111111111111111111111100001000;
  int decimal1_3 = 0b11111111111111111111111100001000;

  int decimal2_1 = 0b101111111111111001111;
  int decimal2_2 = 0b111100001111111111100011;
  int decimal2_3 = 0b1111111111111111111;

  s21_decimal decimal1 = {{decimal1_1, decimal1_2, decimal1_3, 0x80000000}};
  s21_decimal decimal2 = {{decimal2_1, decimal2_2, decimal2_3, 0}};
  s21_decimal result;
  int code = s21_sub(decimal1, decimal2, &result);

  ck_assert_int_eq(code, 2);
}
END_TEST

START_TEST(test_sub_decimal_big2_neg) {
  int decimal1_1 = 0b11111111111111111111111111111111;
  int decimal1_2 = 0b11111111111111111111111100001000;
  int decimal1_3 = 0b11111111111111111111111100001000;

  int decimal2_1 = 0b101111111111111001111;
  int decimal2_2 = 0b111100001111111111100011;
  int decimal2_3 = 0b1111111111111111111;

  s21_decimal decimal1 = {{decimal1_1, decimal1_2, decimal1_3, 0x80000000}};
  s21_decimal decimal2 = {{decimal2_1, decimal2_2, decimal2_3, 0}};
  s21_decimal result;
  int code = s21_sub(decimal1, decimal2, &result);

  ck_assert_int_eq(code, 2);
}
END_TEST

START_TEST(test_sub_decimal_zero1) {
  int decimal1_1 = 0b0;
  int decimal1_2 = 0b0;
  int decimal1_3 = 0b0;

  int decimal2_1 = 0b0;
  int decimal2_2 = 0b0;
  int decimal2_3 = 0b0;

  char res_to_str[50] = "0";

  s21_decimal decimal1 = {{decimal1_1, decimal1_2, decimal1_3, 0}};
  s21_decimal decimal2 = {{decimal2_1, decimal2_2, decimal2_3, 0}};
  s21_decimal result;
  s21_sub(decimal1, decimal2, &result);

  ck_assert_str_eq(decimal_to_string(result), res_to_str);
}
END_TEST

START_TEST(test_sub_decimal_zero2) {
  int decimal1_1 = 0b0;
  int decimal1_2 = 0b0;
  int decimal1_3 = 0b11111111111111111111111111111111;

  int decimal2_1 = 0b0;
  int decimal2_2 = 0b0;
  int decimal2_3 = 0b0;

  char res_to_str[50] = "79228162495817593519834398720";

  s21_decimal decimal1 = {{decimal1_1, decimal1_2, decimal1_3, 0}};
  s21_decimal decimal2 = {{decimal2_1, decimal2_2, decimal2_3, 0}};
  s21_decimal result;
  s21_sub(decimal1, decimal2, &result);

  ck_assert_str_eq(decimal_to_string(result), res_to_str);
}
END_TEST

START_TEST(test_sub_decimal_zero3) {
  int decimal1_1 = 0b11111111111111111111111111111111;
  int decimal1_2 = 0b11111111111111111111111111111111;
  int decimal1_3 = 0b11111111111111111111111111111111;

  int decimal2_1 = 0b0;
  int decimal2_2 = 0b0;
  int decimal2_3 = 0b0;

  char res_to_str[50] = "79228162514264337593543950335";

  s21_decimal decimal1 = {{decimal1_1, decimal1_2, decimal1_3, 0}};
  s21_decimal decimal2 = {{decimal2_1, decimal2_2, decimal2_3, 0}};
  s21_decimal result;
  s21_sub(decimal1, decimal2, &result);

  ck_assert_str_eq(decimal_to_string(result), res_to_str);
}
END_TEST

START_TEST(test_sub_decimal_zero4) {
  int decimal1_1 = 0b0;
  int decimal1_2 = 0b0;
  int decimal1_3 = 0b0;

  int decimal2_1 = 0b11111111111111111111111111111111;
  int decimal2_2 = 0b11111111111111111111111111111111;
  int decimal2_3 = 0b11111111111111111111111111111111;

  char res_to_str[50] = "-79228162514264337593543950335";

  s21_decimal decimal1 = {{decimal1_1, decimal1_2, decimal1_3, 0}};
  s21_decimal decimal2 = {{decimal2_1, decimal2_2, decimal2_3, 0}};
  s21_decimal result;
  s21_sub(decimal1, decimal2, &result);

  ck_assert_str_eq(decimal_to_string(result), res_to_str);
}
END_TEST

START_TEST(test_sub_decimal_zero5) {
  int decimal1_1 = 0b1;
  int decimal1_2 = 0b0;
  int decimal1_3 = 0b0;

  int decimal2_1 = 0b0;
  int decimal2_2 = 0b0;
  int decimal2_3 = 0b0;

  char res_to_str[50] = "1";

  s21_decimal decimal1 = {{decimal1_1, decimal1_2, decimal1_3, 0}};
  s21_decimal decimal2 = {{decimal2_1, decimal2_2, decimal2_3, 0}};
  s21_decimal result;
  s21_sub(decimal1, decimal2, &result);

  ck_assert_str_eq(decimal_to_string(result), res_to_str);
}
END_TEST

START_TEST(test_sub_decimal_oversmall1) {
  int decimal1_1 = 0b1;
  int decimal1_2 = 0b0;
  int decimal1_3 = 0b0;
  int decimal1_4 = 0b10000000000111000000000000000000;

  int decimal2_1 = 0b0;
  int decimal2_2 = 0b0;
  int decimal2_3 = 0b0;
  int decimal2_4 = 0b0;

  char res_to_str[50] = "-0.0000000000000000000000000001";

  s21_decimal decimal1 = {{decimal1_1, decimal1_2, decimal1_3, decimal1_4}};
  s21_decimal decimal2 = {{decimal2_1, decimal2_2, decimal2_3, decimal2_4}};
  s21_decimal result;
  s21_sub(decimal1, decimal2, &result);

  ck_assert_str_eq(decimal_to_string(result), res_to_str);
}
END_TEST

START_TEST(test_sub_decimal_oversmall2) {
  int decimal1_1 = 0b1;
  int decimal1_2 = 0b0;
  int decimal1_3 = 0b0;
  int decimal1_4 = 0b111000000000000000000;

  int decimal2_1 = 0b0;
  int decimal2_2 = 0b0;
  int decimal2_3 = 0b0;
  int decimal2_4 = 0b0;

  char res_to_str[50] = "0.0000000000000000000000000001";

  s21_decimal decimal1 = {{decimal1_1, decimal1_2, decimal1_3, decimal1_4}};
  s21_decimal decimal2 = {{decimal2_1, decimal2_2, decimal2_3, decimal2_4}};
  s21_decimal result;
  s21_sub(decimal1, decimal2, &result);

  ck_assert_str_eq(decimal_to_string(result), res_to_str);
}
END_TEST

START_TEST(test_sub_decimal_oversmall3) {
  int decimal1_1 = 0b1;
  int decimal1_2 = 0b0;
  int decimal1_3 = 0b0;
  int decimal1_4 = 0b10000000000111000000000000000000;

  int decimal2_1 = 0b1;
  int decimal2_2 = 0b0;
  int decimal2_3 = 0b0;
  int decimal2_4 = 0b00000000000111000000000000000000;

  char res_to_str[50] = "-0.0000000000000000000000000002";

  s21_decimal decimal1 = {{decimal1_1, decimal1_2, decimal1_3, decimal1_4}};
  s21_decimal decimal2 = {{decimal2_1, decimal2_2, decimal2_3, decimal2_4}};
  s21_decimal result;
  s21_sub(decimal1, decimal2, &result);

  ck_assert_str_eq(decimal_to_string(result), res_to_str);
}
END_TEST

START_TEST(test_sub_decimal_oversmall4) {
  int decimal1_1 = 0b1;
  int decimal1_2 = 0b0;
  int decimal1_3 = 0b0;
  int decimal1_4 = 0b10000000000111000000000000000000;

  int decimal2_1 = 0b1;
  int decimal2_2 = 0b0;
  int decimal2_3 = 0b0;
  int decimal2_4 = 0b10000000000111000000000000000000;

  char res_to_str[50] = "0";

  s21_decimal decimal1 = {{decimal1_1, decimal1_2, decimal1_3, decimal1_4}};
  s21_decimal decimal2 = {{decimal2_1, decimal2_2, decimal2_3, decimal2_4}};
  s21_decimal result;
  s21_sub(decimal1, decimal2, &result);

  ck_assert_str_eq(decimal_to_string(result), res_to_str);
}
END_TEST

START_TEST(test_sub_decimal_oversmall5) {
  int decimal1_1 = 0b111111;
  int decimal1_2 = 0b0;
  int decimal1_3 = 0b0;
  int decimal1_4 = 0b00000000000111000000000000000000;

  int decimal2_1 = 0b111;
  int decimal2_2 = 0b0;
  int decimal2_3 = 0b0;
  int decimal2_4 = 0b10000000000111000000000000000000;

  char res_to_str[50] = "0.0000000000000000000000000070";

  s21_decimal decimal1 = {{decimal1_1, decimal1_2, decimal1_3, decimal1_4}};
  s21_decimal decimal2 = {{decimal2_1, decimal2_2, decimal2_3, decimal2_4}};
  s21_decimal result;
  s21_sub(decimal1, decimal2, &result);

  ck_assert_str_eq(decimal_to_string(result), res_to_str);
}
END_TEST

START_TEST(test_sub_decimal_oversmall6) {
  int decimal1_1 = 0b111111;
  int decimal1_2 = 0b0;
  int decimal1_3 = 0b0;
  int decimal1_4 = 0b00000000001111000000000000000000;  // pow is bigger that 28

  int decimal2_1 = 0b111;
  int decimal2_2 = 0b0;
  int decimal2_3 = 0b0;
  int decimal2_4 = 0b10000000000111000000000000000000;

  s21_decimal decimal1 = {{decimal1_1, decimal1_2, decimal1_3, decimal1_4}};
  s21_decimal decimal2 = {{decimal2_1, decimal2_2, decimal2_3, decimal2_4}};
  s21_decimal result;
  int code = s21_sub(decimal1, decimal2, &result);

  ck_assert_int_eq(code, 4);
}
END_TEST

START_TEST(test_sub_decimal_smallpow1) {
  int decimal1_1 = 0b11111111111111111111111111111111;
  int decimal1_2 = 0b11111111111111111111111111111111;
  int decimal1_3 = 0b11111111111111111111111111111111;
  int decimal1_4 = 0b00000000000111000000000000000000;

  int decimal2_1 = 0b1;
  int decimal2_2 = 0b0;
  int decimal2_3 = 0b0;
  int decimal2_4 = 0b10000000000111000000000000000000;

  char res_to_str[50] = "7.922816251426433759354395034";

  s21_decimal decimal1 = {{decimal1_1, decimal1_2, decimal1_3, decimal1_4}};
  s21_decimal decimal2 = {{decimal2_1, decimal2_2, decimal2_3, decimal2_4}};
  s21_decimal result;
  s21_sub(decimal1, decimal2, &result);

  ck_assert_str_eq(decimal_to_string(result), res_to_str);
}
END_TEST

START_TEST(test_sub_decimal_smallpow2) {
  int decimal1_1 = 0b11111111111111111111111111111111;
  int decimal1_2 = 0b11111111111111111111111111111111;
  int decimal1_3 = 0b11111111111111111111111111111111;
  int decimal1_4 = 0b00000000000111000000000000000000;

  int decimal2_1 = 0b1;
  int decimal2_2 = 0b0;
  int decimal2_3 = 0b0;
  int decimal2_4 = 0b00000000000111000000000000000000;

  char res_to_str[50] = "7.9228162514264337593543950334";

  s21_decimal decimal1 = {{decimal1_1, decimal1_2, decimal1_3, decimal1_4}};
  s21_decimal decimal2 = {{decimal2_1, decimal2_2, decimal2_3, decimal2_4}};
  s21_decimal result;
  s21_sub(decimal1, decimal2, &result);

  ck_assert_str_eq(decimal_to_string(result), res_to_str);
}
END_TEST

START_TEST(test_sub_decimal_smallpow3) {
  int decimal1_1 = 0b11111111111111111111111111111110;
  int decimal1_2 = 0b11111111111111111111111111111111;
  int decimal1_3 = 0b11111111111111111111111111111111;
  int decimal1_4 = 0b00000000000111000000000000000000;

  int decimal2_1 = 0b1;
  int decimal2_2 = 0b0;
  int decimal2_3 = 0b0;
  int decimal2_4 = 0b00000000000111000000000000000000;

  char res_to_str[50] = "7.9228162514264337593543950333";

  s21_decimal decimal1 = {{decimal1_1, decimal1_2, decimal1_3, decimal1_4}};
  s21_decimal decimal2 = {{decimal2_1, decimal2_2, decimal2_3, decimal2_4}};
  s21_decimal result;
  s21_sub(decimal1, decimal2, &result);

  ck_assert_str_eq(decimal_to_string(result), res_to_str);
}
END_TEST

START_TEST(test_sub_decimal_smallpow4) {
  int decimal1_1 = 0b11111111111111111111111111111111;
  int decimal1_2 = 0b11111111111111111111111111111111;
  int decimal1_3 = 0b11111111111111111111111111111111;
  int decimal1_4 = 0b00000000000111000000000000000000;

  int decimal2_1 = 0b11111111111111111111111111111111;
  int decimal2_2 = 0b0;
  int decimal2_3 = 0b0;
  int decimal2_4 = 0b00000000000111000000000000000000;

  char res_to_str[50] = "7.9228162514264337589248983040";

  s21_decimal decimal1 = {{decimal1_1, decimal1_2, decimal1_3, decimal1_4}};
  s21_decimal decimal2 = {{decimal2_1, decimal2_2, decimal2_3, decimal2_4}};
  s21_decimal result;
  s21_sub(decimal1, decimal2, &result);

  ck_assert_str_eq(decimal_to_string(result), res_to_str);
}
END_TEST

START_TEST(test_sub_decimal_smallpow5) {
  int decimal1_1 = 0b11111111111111111111111111111111;
  int decimal1_2 = 0b11111111111111111111111111111111;
  int decimal1_3 = 0b11111111111111111111111111111111;
  int decimal1_4 = 0b10000000000111000000000000000000;

  int decimal2_1 = 0b11111111111111111111111111111111;
  int decimal2_2 = 0b11111111111111111111111111111111;
  int decimal2_3 = 0b11111111111111111111111111111111;
  int decimal2_4 = 0b00000000000111000000000000000000;

  char res_to_str[50] = "-15.845632502852867518708790067";

  s21_decimal decimal1 = {{decimal1_1, decimal1_2, decimal1_3, decimal1_4}};
  s21_decimal decimal2 = {{decimal2_1, decimal2_2, decimal2_3, decimal2_4}};
  s21_decimal result;
  s21_sub(decimal1, decimal2, &result);

  ck_assert_str_eq(decimal_to_string(result), res_to_str);
}
END_TEST

START_TEST(test_error_result_is_null) {
  s21_decimal decimal1 = {{0, 0, 0, 0}};
  s21_decimal decimal2 = {{0x1, 0, 0, 0}};
  int code = s21_sub(decimal1, decimal2, NULL);

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
  int code = s21_sub(decimal1, decimal2, &result);

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
  int code = s21_sub(decimal1, decimal2, &result);

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
  int code = s21_sub(decimal1, decimal2, &result);

  ck_assert_int_eq(code, 4);
}
END_TEST

Suite *suite_sub(void) {
  Suite *s = suite_create("suite_sub");
  TCase *tc = tcase_create("sub_tc");

  tcase_add_test(tc, test_sub_simple);

  tcase_add_test(tc, test_sub_simple_neg);

  tcase_add_test(tc, test_sub_simple_check_code);

  tcase_add_test(tc, test_sub_simple_float_equal_small_pow);

  tcase_add_test(tc, test_sub_simple_float_neg_equal_small_pow);

  tcase_add_test(tc, test_sub_simple_float_diff_small_pow);

  tcase_add_test(tc, test_sub_simple_float_neg_diff_small_pow);

  tcase_add_test(tc, test_sub_decimal);


  tcase_add_test(tc, test_sub_decimal_overbig1);
  tcase_add_test(tc, test_sub_decimal_overbig2);
  tcase_add_test(tc, test_sub_decimal_overbig3);
  tcase_add_test(tc, test_sub_decimal_overbig4);
  tcase_add_test(tc, test_sub_decimal_overbig5);


  tcase_add_test(tc, test_sub_decimal_overbig1_neg);
  tcase_add_test(tc, test_sub_decimal_overbig2_neg);


  tcase_add_test(tc, test_sub_decimal_big1_neg);
  tcase_add_test(tc, test_sub_decimal_big2_neg);


  tcase_add_test(tc, test_sub_decimal_zero1);
  tcase_add_test(tc, test_sub_decimal_zero2);
  tcase_add_test(tc, test_sub_decimal_zero3);
  tcase_add_test(tc, test_sub_decimal_zero4);
  tcase_add_test(tc, test_sub_decimal_zero5);


  tcase_add_test(tc, test_sub_decimal_oversmall1);
  tcase_add_test(tc, test_sub_decimal_oversmall2);
  tcase_add_test(tc, test_sub_decimal_oversmall3);
  tcase_add_test(tc, test_sub_decimal_oversmall4);
  tcase_add_test(tc, test_sub_decimal_oversmall5);
  tcase_add_test(tc, test_sub_decimal_oversmall6);


  tcase_add_test(tc, test_sub_decimal_smallpow1);
  tcase_add_test(tc, test_sub_decimal_smallpow2);
  tcase_add_test(tc, test_sub_decimal_smallpow3);
  tcase_add_test(tc, test_sub_decimal_smallpow4);
  tcase_add_test(tc, test_sub_decimal_smallpow5);


  tcase_add_test(tc, test_error_result_is_null);


  tcase_add_test(tc, test_error1);
  tcase_add_test(tc, test_error2);
  tcase_add_test(tc, test_error3);

  suite_add_tcase(s, tc);
  return s;
}