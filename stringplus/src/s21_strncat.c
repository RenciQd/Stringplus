#include "s21_string.h"

// Добавляет строку, на которую указывает src, в конец строки, на которую
// указывает dest, длиной до n символов.

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  s21_size_t i, j;
  for (i = 0; dest[i] != '\0'; i++) {
  }
  for (j = 0; j < n; j++) {
    dest[i + j] = src[j];
  }
  dest[i + j] = '\0';
  return dest;
}