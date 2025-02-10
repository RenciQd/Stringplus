#include "s21_string.h"

// Копирует до n символов из строки, на которую указывает src, в dest.

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  char *dest_begin = dest;
  s21_size_t src_length = s21_strlen(src);
  for (s21_size_t i = 0; i < n; i++) {
    if (i >= src_length) {
      dest[i] = '\0';
    } else {
      dest[i] = src[i];
    }
  }
  return dest_begin;
}
