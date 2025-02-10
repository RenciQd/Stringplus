#include "s21_string.h"

// Выполняет поиск первого вхождения символа c (беззнаковый тип) в первых n
// байтах строки, на которую указывает аргумент str.

void *s21_memchr(const void *str, int c, s21_size_t n) {
  unsigned char *byte = (unsigned char *)str;
  int matched = 0;
  while (n-- > 0) {
    if (*byte == c) {
      matched = 1;
      break;
    }
    byte++;
  }
  return (matched) ? byte : S21_NULL;
}