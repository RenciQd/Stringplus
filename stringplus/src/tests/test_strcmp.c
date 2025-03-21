#include "../tests_includes/s21_tests.h"

START_TEST(Heloboba_Heloboba) {
  char a[] = "Heloboba";
  char b[] = "Heloboba";

  int got = s21_strcmp(a, b);
  int expected = strcmp(a, b);

  if (got > 1) got = 1;
  if (expected > 1) expected = 1;

  if (got < -1) got = -1;
  if (expected < -1) expected = -1;

  ck_assert_int_eq(got, expected);
}
END_TEST

START_TEST(HEloboba_Heloboba) {
  char a[] = "HEloboba";
  char b[] = "Heloboba";

  int got = s21_strcmp(a, b);
  int expected = strcmp(a, b);

  if (got > 1) got = 1;
  if (expected > 1) expected = 1;

  if (got < -1) got = -1;
  if (expected < -1) expected = -1;

  ck_assert_int_eq(got, expected);
}
END_TEST

START_TEST(Hel0boba_Helob0ba) {
  char a[] = "Hel0boba";
  char b[] = "Helob0ba";

  int got = s21_strcmp(a, b);
  int expected = strcmp(a, b);

  if (got > 1) got = 1;
  if (expected > 1) expected = 1;

  if (got < -1) got = -1;
  if (expected < -1) expected = -1;

  ck_assert_int_eq(got, expected);
}
END_TEST

START_TEST(Heloboba_) {
  char a[] = "Heloboba";
  char b[] = "";

  int got = s21_strcmp(a, b);
  int expected = strcmp(a, b);

  if (got > 1) got = 1;
  if (expected > 1) expected = 1;

  if (got < -1) got = -1;
  if (expected < -1) expected = -1;

  ck_assert_int_eq(got, expected);
}
END_TEST

START_TEST(_Heloboba) {
  char a[] = "";
  char b[] = "Heloboba";

  int got = s21_strcmp(a, b);
  int expected = strcmp(a, b);

  if (got > 1) got = 1;
  if (expected > 1) expected = 1;

  if (got < -1) got = -1;
  if (expected < -1) expected = -1;

  ck_assert_int_eq(got, expected);
}
END_TEST

START_TEST(Heloboba) {
  char a[] = "L(8)L";
  char b[] = "L(8)L";

  int got = s21_strcmp(a, b);
  int expected = strcmp(a, b);

  if (got > 1) got = 1;
  if (expected > 1) expected = 1;

  if (got < -1) got = -1;
  if (expected < -1) expected = -1;

  ck_assert_int_eq(got, expected);
}
END_TEST

START_TEST(empty) {
  char a[] = "";
  char b[] = "";

  int got = s21_strcmp(a, b);
  int expected = strcmp(a, b);

  if (got > 1) got = 1;
  if (expected > 1) expected = 1;

  if (got < -1) got = -1;
  if (expected < -1) expected = -1;

  ck_assert_int_eq(got, expected);
}
END_TEST

START_TEST(only_num) {
  char a[] = "1234567890";
  char b[] = "1234567890";

  int got = s21_strcmp(a, b);
  int expected = strcmp(a, b);

  if (got > 1) got = 1;
  if (expected > 1) expected = 1;

  if (got < -1) got = -1;
  if (expected < -1) expected = -1;

  ck_assert_int_eq(got, expected);
}
END_TEST

START_TEST(strcmp_1) {
  char s1[] = "Andrey";
  char s2[] = "Andrey";
  int n1 = strcmp(s1, s2);
  n1 = n1 > 0 ? 1 : n1 == 0 ? 0 : -1;
  int n2 = s21_strcmp(s1, s2);
  n2 = n2 > 0 ? 1 : n2 == 0 ? 0 : -1;
  ck_assert_int_eq(n1, n2);
}
END_TEST

START_TEST(strcmp_2) {
  char s1[] = "Andrey";
  char s2[] = "Roma";
  int n1 = strcmp(s1, s2);
  n1 = n1 > 0 ? 1 : n1 == 0 ? 0 : -1;
  int n2 = s21_strcmp(s1, s2);
  n2 = n2 > 0 ? 1 : n2 == 0 ? 0 : -1;
  ck_assert_int_eq(n1, n2);
}
END_TEST

START_TEST(strcmp_3) {
  char s1[] = "";
  char s2[] = "";
  int n1 = strcmp(s1, s2);
  n1 = n1 > 0 ? 1 : n1 == 0 ? 0 : -1;
  int n2 = s21_strcmp(s1, s2);
  n2 = n2 > 0 ? 1 : n2 == 0 ? 0 : -1;
  ck_assert_int_eq(n1, n2);
}
END_TEST

START_TEST(strcmp_4) {
  char s1[] = "u";
  char s2[] = "\0";
  int n1 = strcmp(s1, s2);
  n1 = n1 > 0 ? 1 : n1 == 0 ? 0 : -1;
  int n2 = s21_strcmp(s1, s2);
  n2 = n2 > 0 ? 1 : n2 == 0 ? 0 : -1;
  ck_assert_int_eq(n1, n2);
}
END_TEST

START_TEST(strcmp_5) {
  char s1[] = "\0";
  char s2[] = "j";
  int n1 = strcmp(s1, s2);
  n1 = n1 > 0 ? 1 : n1 == 0 ? 0 : -1;
  int n2 = s21_strcmp(s1, s2);
  n2 = n2 > 0 ? 1 : n2 == 0 ? 0 : -1;
  ck_assert_int_eq(n1, n2);
}
END_TEST

START_TEST(strcmp_6) {
  char s1[] = "\0";
  char s2[] = "\0";
  int n1 = strcmp(s1, s2);
  n1 = n1 > 0 ? 1 : n1 == 0 ? 0 : -1;
  int n2 = s21_strcmp(s1, s2);
  n2 = n2 > 0 ? 1 : n2 == 0 ? 0 : -1;
  ck_assert_int_eq(n1, n2);
}
END_TEST

START_TEST(strcmp_7) {
  char s1[] = "shf roma \0 dljfn roma";
  char s2[] = "roma";
  int n1 = strcmp(s1, s2);
  n1 = n1 > 0 ? 1 : n1 == 0 ? 0 : -1;
  int n2 = s21_strcmp(s1, s2);
  n2 = n2 > 0 ? 1 : n2 == 0 ? 0 : -1;
  ck_assert_int_eq(n1, n2);
}
END_TEST

Suite *suite_strcmp(void) {
  Suite *s = suite_create("suite_strcmp");
  TCase *tc = tcase_create("strcmp_tc");

  tcase_add_test(tc, Heloboba_Heloboba);
  tcase_add_test(tc, HEloboba_Heloboba);
  tcase_add_test(tc, Hel0boba_Helob0ba);
  tcase_add_test(tc, Heloboba_);
  tcase_add_test(tc, _Heloboba);
  tcase_add_test(tc, Heloboba);
  tcase_add_test(tc, empty);
  tcase_add_test(tc, only_num);
  tcase_add_test(tc, strcmp_1);
  tcase_add_test(tc, strcmp_2);
  tcase_add_test(tc, strcmp_3);
  tcase_add_test(tc, strcmp_4);
  tcase_add_test(tc, strcmp_5);
  tcase_add_test(tc, strcmp_6);
  tcase_add_test(tc, strcmp_7);

  suite_add_tcase(s, tc);
  return s;
}
