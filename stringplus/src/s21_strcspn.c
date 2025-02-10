#include "s21_string.h"

// Вычисляет длину начального сегмента str1, который полностью состоит из
// символов, не входящих в str2.

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  const char *tmp = str1;
  s21_size_t counter_1 = 0;
  s21_size_t counter_2 = s21_strlen(str1);
  while (*str2 != '\0') {
    while (*str1 != '\0') {
      if (*str1 != *str2) {
        str1++;
        counter_1++;
      } else {
        break;
      }
    }
    str2++;
    if (counter_1 <= counter_2) {
      counter_2 = counter_1;
      counter_1 = 0;
    }
    counter_1 = 0;
    str1 = tmp;
  }
  return counter_2;
}
