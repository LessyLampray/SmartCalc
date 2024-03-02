
#include <check.h>

#include "s21_SmartCalc.h"
#define ACCURACY 1e-7
#define OKK 0
#define ERO 1

START_TEST(s21_simple_calc1) {
  double result = 0.0;
  char input_string[256] = "5+3+2+5+5+1+2+3+4+5+6+7+8+9";
  int check = OKK;
  check = SmartCalc(input_string, &result, 0);
  ck_assert_double_eq_tol(result, 65, ACCURACY);
  ck_assert_int_eq(check, OKK);
}

START_TEST(s21_simple_calc2) {
  double result = 0.0;
  char input_string[256] = "5-3-2-5-5-1-2-3-4-5-6-7-8-9";
  int check = OKK;
  check = SmartCalc(input_string, &result, 0);
  ck_assert_double_eq_tol(result, -55, ACCURACY);
  ck_assert_int_eq(check, OKK);
}

START_TEST(s21_simple_calc3) {
  double result = 0.0;
  char input_string[256] = "5143*1213*24532/1213/1445";
  int check = OKK;
  check = SmartCalc(input_string, &result, 0);
  ck_assert_double_eq_tol(result, 87313.5474048, ACCURACY);
  ck_assert_int_eq(check, OKK);
}

START_TEST(s21_simple_calc4) {
  double result = 0.0;
  char input_string[256] = "12345679*9";
  int check = OKK;
  check = SmartCalc(input_string, &result, 0);
  ck_assert_double_eq_tol(result, 111111111, ACCURACY);
  ck_assert_int_eq(check, OKK);
}

START_TEST(s21_simple_calc5) {
  double result = 0.0;
  char input_string[256] =
      "1.23456789+2.34567890-3.45678901*4.56789012/5.67890123";
  int check = OKK;
  check = SmartCalc(input_string, &result, 0);
  ck_assert_double_eq_tol(result, 0.79973842646, ACCURACY);
  ck_assert_int_eq(check, OKK);
}

START_TEST(s21_simple_calc6) {
  double result = 0.0;
  char input_string[256] = "5";
  int check = OKK;
  check = SmartCalc(input_string, &result, 0);
  ck_assert_double_eq_tol(result, 5, ACCURACY);
  ck_assert_int_eq(check, OKK);
}

START_TEST(s21_simple_calc7) {
  double result = 0.0;
  char input_string[256] = "2^3^2";
  int check = OKK;
  check = SmartCalc(input_string, &result, 0);
  ck_assert_double_eq_tol(result, 512, ACCURACY);
  ck_assert_int_eq(check, OKK);
}

START_TEST(s21_simple_calc8) {
  double result = 0.0;
  char input_string[256] = "5*X";
  int check = OKK;
  check = SmartCalc(input_string, &result, 6);
  ck_assert_double_eq_tol(result, 30, ACCURACY);
  ck_assert_int_eq(check, OKK);
}

START_TEST(s21_simple_calc9) {
  double result = 0.0;
  char input_string[256] = "2^X^X";
  int check = OKK;
  check = SmartCalc(input_string, &result, 3);
  ck_assert_double_eq_tol(result, 134217728, ACCURACY);
  ck_assert_int_eq(check, OKK);
}

START_TEST(s21_simple_calc10) {
  double result = 0.0;
  char input_string[256] = "2+X/X-X*(X%X)";
  int check = OKK;
  check = SmartCalc(input_string, &result, 3);
  ck_assert_double_eq_tol(result, 3, ACCURACY);
  ck_assert_int_eq(check, OKK);
}

Suite *s21_simple_calc(void) {
  Suite *s = suite_create("\033[46m-=s21_simple_calc=-\033[0m");
  TCase *tc = tcase_create("calc_tc");
  tcase_add_test(tc, s21_simple_calc1);
  tcase_add_test(tc, s21_simple_calc2);
  tcase_add_test(tc, s21_simple_calc3);
  tcase_add_test(tc, s21_simple_calc4);
  tcase_add_test(tc, s21_simple_calc5);
  tcase_add_test(tc, s21_simple_calc6);
  tcase_add_test(tc, s21_simple_calc7);
  tcase_add_test(tc, s21_simple_calc8);
  tcase_add_test(tc, s21_simple_calc9);
  tcase_add_test(tc, s21_simple_calc10);
  suite_add_tcase(s, tc);
  return s;
}

START_TEST(s21_hard_calc1) {
  double result = 0.0;
  char input_string[256] =
      "15/(7-(1+1))*3-(2+(1+1))*15/(7-(200+1))*3-(2+(1+1))*(15/"
      "(7-(1+1))*3-(2+(1+1))+15/(7-(1+1))*3-(2+(1+1)))";
  int check = OKK;
  check = SmartCalc(input_string, &result, 0);
  ck_assert_double_eq_tol(result, -30.0721649, ACCURACY);
  ck_assert_int_eq(check, OKK);
}

START_TEST(s21_hard_calc2) {
  double result = 0.0;
  char input_string[256] = "cos(2-sin(3+0.26*7+1))";
  int check = OKK;
  check = SmartCalc(input_string, &result, 0);
  ck_assert_double_eq_tol(result, -0.7681865, ACCURACY);
  ck_assert_int_eq(check, OKK);
}

START_TEST(s21_hard_calc3) {
  double result = 0.0;
  char input_string[256] = "10*(-5+log(2+(9/3)))";
  int check = OKK;
  check = SmartCalc(input_string, &result, 0);
  ck_assert_double_eq_tol(result, -43.0102999, ACCURACY);
  ck_assert_int_eq(check, OKK);
}

START_TEST(s21_hard_calc6) {
  double result = 0.0;
  char input_string[256] = "sin(sin(sin(sin(sin(90)))))";
  int check = OKK;
  check = SmartCalc(input_string, &result, 0);
  ck_assert_double_eq_tol(result, 0.6023926, ACCURACY);
  ck_assert_int_eq(check, OKK);
}

Suite *s21_hard_calc(void) {
  Suite *s = suite_create("\033[46m-=s21_hard_calc=-\033[0m");
  TCase *tc = tcase_create("calc_tc");
  tcase_add_test(tc, s21_hard_calc1);
  tcase_add_test(tc, s21_hard_calc2);
  tcase_add_test(tc, s21_hard_calc3);
  tcase_add_test(tc, s21_hard_calc6);
  suite_add_tcase(s, tc);
  return s;
}

int main() {
  int failed = 0;
  Suite *s21_smart_calc_test[] = {s21_simple_calc(), s21_hard_calc(), NULL};

  for (int i = 0; s21_smart_calc_test[i] != NULL; i++) {
    SRunner *sr = srunner_create(s21_smart_calc_test[i]);

    srunner_run_all(sr, CK_NORMAL);

    failed += srunner_ntests_failed(sr);
    srunner_free(sr);
  }

  printf("========= FAILED: %d =========\n", failed);

  return failed == 0 ? 0 : 1;
}
