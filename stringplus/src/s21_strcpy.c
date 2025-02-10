#include "s21_string.h"

// Функция стандартной библиотеки языка программирования Си для копирования
// нуль-терминированной строки в заданный буфер.

char *s21_strcpy(char *dest, const char *src) {
  char *source = dest;
  while ((*dest++ = *src++) != '\0') continue;
  return source;
}
