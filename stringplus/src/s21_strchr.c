#include "s21_string.h"

// Выполняет поиск первого вхождения символа c (беззнаковый тип) в строке, на
// которую указывает аргумент str.

char *s21_strchr(const char *string, int c) {
  char *result = s21_NULL;
  while ((*string != '\0') && (*string != c)) {
    string++;
  }
  if (*string == c) {
    result = (char *)string;
  }
  return result;
}
