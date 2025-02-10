#include "s21_string.h"

// Выполняет поиск последнего вхождения символа c (беззнаковый тип) в строке, на
// которую указывает аргумент str.

char *s21_strrchr(const char *str, int c) {
  char i = c;
  char *res = s21_NULL;
  for (; *str != '\0'; str++) {
    if (*str == i) {
      res = (char *)str;
    }
  }
  if (res == s21_NULL) {
    res = (char *)str;
  }
  return *res == c ? (char *)res : s21_NULL;
}
