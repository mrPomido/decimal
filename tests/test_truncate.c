#include "../tests_includes/s21_tests.h"

START_TEST(test_truncate) {
  struct {
    int truncate_check;
    s21_decimal truncate_dec;
  } test_cases[] = {
    {5, {{501, 0, 0, 0x20000}}},
    {5, {{571, 0, 0, 0x20000}}},
    {5, {{57185, 0, 0, 0x40000}}},
    {2855, {{285500, 0, 0, 0x20000}}},
    {12, {{12741253, 0, 0, 0x60000}}},
    {5, {{55, 0, 0, 0x10000}}},
    {5, {{54, 0, 0, 0x10000}}},
    {5, {{56, 0, 0, 0x10000}}},
    {5, {{551, 0, 0, 0x20000}}},
    {5, {{549, 0, 0, 0x20000}}},
  };

  for (size_t i = 0; i < sizeof(test_cases) / sizeof(test_cases[0]); i++) {
    int int_from_decimal = 0;
    s21_decimal result;
    
    s21_truncate(test_cases[i].truncate_dec, &result);
    s21_from_decimal_to_int(result, &int_from_decimal);
    
    ck_assert_int_eq(test_cases[i].truncate_check, int_from_decimal);
  }
}
END_TEST

START_TEST(test_truncate_simple_neg) {
  struct {
    int truncate_check;
    s21_decimal truncate_dec;
  } test_cases[] = {
    {-5, {{500, 0, 0, 0x80020000}}},
    {-5, {{516, 0, 0, 0x80020000}}},
    {-52, {{527589, 0, 0, 0x80040000}}},
  };

  for (size_t i = 0; i < sizeof(test_cases) / sizeof(test_cases[0]); i++) {
    int int_from_decimal = 0;
    s21_decimal result;
    
    s21_truncate(test_cases[i].truncate_dec, &result);
    s21_from_decimal_to_int(result, &int_from_decimal);
    
    ck_assert_int_eq(test_cases[i].truncate_check, int_from_decimal);
  }
}
END_TEST

START_TEST(test_truncate_pow1) {
  struct {
    int truncate_check;
    s21_decimal truncate_dec;
  } test_cases[] = {
    {154748, {{15474820, 0, 0, 0x20000}}},
    {154748, {{1547482000, 0, 0, 0x40000}}},
    {12, {{1274125377, 0, 0, 0x80000}}},
    {11, {{1124574253, 0, 0, 0x80000}}},
    {0, {{741253, 0, 0, 0x60000}}},
    {0, {{74125389, 0, 0, 0x80000}}},
    {0, {{74125381, 0, 0, 0x80000}}},
    {0, {{7412538, 0, 0, 0x70000}}},
    {21, {{214741253, 0, 0, 0x70000}}},
    {2, {{27412537, 0, 0, 0x70000}}},
    {-4, {{47412553, 0, 0, 0x80070000}}},
    {-48, {{487412153, 0, 0, 0x80070000}}},
  };

  for (size_t i = 0; i < sizeof(test_cases) / sizeof(test_cases[0]); i++) {
    int int_from_decimal = 0;
    s21_decimal result;
    
    s21_truncate(test_cases[i].truncate_dec, &result);
    s21_from_decimal_to_int(result, &int_from_decimal);
    
    ck_assert_int_eq(test_cases[i].truncate_check, int_from_decimal);
  }
}
END_TEST

START_TEST(test_truncate_pow2) {
  struct {
    int truncate_check;
    s21_decimal truncate_dec;
  } test_cases[] = {
    {-4588524, {{458852474, 0, 0, 0x80020000}}},
    {145885, {{14588574, 0, 0, 0x20000}}},
    {145885, {{1458857, 0, 0, 0x10000}}},
    {145885254, {{1458852547, 0, 0, 0x10000}}},
    {-145885254, {{1458852547, 0, 0, 0x80010000}}},
    {0, {{0, 0, 0, 0x0000000}}},
    {0, {{1, 0, 0, 0x20000}}},
    {0, {{1, 0, 0, 0x80020000}}},
    {0, {{1, 0, 0, 0x40000}}},
    {100000, {{1000000001, 0, 0, 0x40000}}},
    {0, {{1, 0, 0, 0x80040000}}},
    {100, {{1002, 0, 0, 0x10000}}},
    {0, {{1, 0, 0, 0x80000}}},
  };

  for (size_t i = 0; i < sizeof(test_cases) / sizeof(test_cases[0]); i++) {
    int int_from_decimal = 0;
    s21_decimal result;
    
    s21_truncate(test_cases[i].truncate_dec, &result);
    s21_from_decimal_to_int(result, &int_from_decimal);
    
    ck_assert_int_eq(test_cases[i].truncate_check, int_from_decimal);
  }
}
END_TEST

START_TEST(test_truncate_simple_check_code) {
  s21_decimal test_inputs[] = {
    {{1, 0, 0, 0x80000}},
    {{1000000001, 0, 0, 0x80040000}},
    {{1, 0, 0, 0x20000}},
    {{458741253, 0, 0, 0x80070000}},
    {{214741253, 0, 0, 0x70000}},
    {{74125389, 0, 0, 0x80000}},
    {{1124574253, 0, 0, 0x80000}},
    {{0, 0, 0, 0}},
    {{0, 0, 0, 0x80000}},
    {{2741253, 0, 0, 0x70000}},
    {{1, 0, 0, 0x20000}}
  };

  int expected_results[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

  s21_decimal result;
  int num_tests = sizeof(test_inputs) / sizeof(test_inputs[0]);

  for (int i = 0; i < num_tests; i++) {
    int res = s21_truncate(test_inputs[i], &result);
    ck_assert_int_eq(res, expected_results[i]);
  }
}
END_TEST

START_TEST(test_error1) {
  // степень 255 (показатель степени должен быть от 0 до 28)

  int decimal1_1 = 0b111;
  int decimal1_2 = 0b111;
  int decimal1_3 = 0b111;
  int decimal1_4 = 0b00000000111111110000000000000000;

  s21_decimal result;
  s21_decimal truncate_dec = {{decimal1_1, decimal1_2, decimal1_3, decimal1_4}};

  int res = s21_truncate(truncate_dec, &result);

  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(test_error2) {
  // биты 0-15 не нули
  // биты 24-30 не нули

  int decimal1_1 = 0b111;
  int decimal1_2 = 0b111;
  int decimal1_3 = 0b111;
  int decimal1_4 = 0b01100000000111000000000000000011;

  s21_decimal result;
  s21_decimal truncate_dec = {{decimal1_1, decimal1_2, decimal1_3, decimal1_4}};

  int res = s21_truncate(truncate_dec, &result);

  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(test_error3) {
  // все единицы

  int decimal1_1 = 0b111;
  int decimal1_2 = 0b111;
  int decimal1_3 = 0b111;
  int decimal1_4 = 0b11111111111111111111111111111111;

  s21_decimal result;
  s21_decimal truncate_dec = {{decimal1_1, decimal1_2, decimal1_3, decimal1_4}};

  int res = s21_truncate(truncate_dec, &result);

  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(test_error_result_is_null) {
  s21_decimal truncate_dec = {{0, 0, 0, 0}};

  int res = s21_truncate(truncate_dec, NULL);
  ck_assert_int_eq(res, 1);
}

END_TEST

Suite *suite_truncate(void) {
  Suite *s = suite_create("suite_truncate");
  TCase *tc = tcase_create("add_tc");
  tcase_add_test(tc, test_truncate);
  tcase_add_test(tc, test_truncate_simple_neg);
  tcase_add_test(tc, test_truncate_pow1);
  tcase_add_test(tc, test_truncate_pow2);
  tcase_add_test(tc, test_truncate_simple_check_code);
  tcase_add_test(tc, test_error1);
  tcase_add_test(tc, test_error2);
  tcase_add_test(tc, test_error3);
  tcase_add_test(tc, test_error_result_is_null);
  suite_add_tcase(s, tc);
  return s;
}