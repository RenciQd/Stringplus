#include "s21_string.h"

// Возвращает новую строку, в которой указанная строка (str)
//  вставлена в указанную позицию (start_index) в данной строке (src).
//  В случае какой-либо ошибки следует вернуть значение NULL

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  s21_size_t lensrc = 0;
  s21_size_t lenstr = 0;

  if (src != s21_NULL)
    lensrc = s21_strlen(src);
  else
    lensrc = 0;
  if (str != s21_NULL)
    lenstr = s21_strlen(str);
  else
    lenstr = 0;

  s21_size_t len = lensrc + lenstr;

  char *res =
      (start_index > lensrc) ? s21_NULL : (char *)calloc(len + 1, sizeof(char));

  if (res) {
    for (s21_size_t i = 0; i < len; i++) {
      if (i < start_index)
        res[i] = src[i];
      else if (i < start_index + lenstr)
        res[i] = str[i - start_index];
      else
        res[i] = src[i - lenstr];
    }
    res[lensrc + lenstr] = '\0';
  }
  return (void *)res;
}