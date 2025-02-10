#include "s21_string.h"

// Копирует n символов из src в dest.

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  char *s1 = (char *)dest;
  const char *s2 = (char *)src;
  if (dest != s21_NULL && src != s21_NULL) {
    for (unsigned int i = 0; i < n; i++) s1[i] = s2[i];
  }
  return s1;
}