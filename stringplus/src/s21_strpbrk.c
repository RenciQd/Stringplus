#include "s21_string.h"

// Находит первый символ в строке str1, который соответствует любому символу,
// указанному в str2.

char *s21_strpbrk(const char *str1, const char *str2) {
  s21_size_t i;
  char *res = s21_NULL;
  for (i = 0; i < s21_strlen(str2); i++) {
    char *ptr = s21_strchr(str1, str2[i]);
    if (ptr != s21_NULL) {
      res = ptr;
      break;
    }
  }
  return res;
}
