#include "s21_string.h"

// Функция atoi в языке программирования Си используется для приведения строки в
// числовой вид. printf

int s21_atoi(const char *str) {
  int res = 0;
  int sign = 1;
  int overflow = 0;

  while (*str == ' ') str++;

  if (*str == '-') {
    str++;
    sign = -1;
  }

  if (*str == '+') {
    str++;
  }

  while (*str && *str >= '0' && *str <= '9') {
    res = res * 10 + (*str - '0');
    if (res < 0) {
      overflow = 1;
      break;
    }
    str++;
  }
  if (overflow)
    res = sign > 0 ? s21_INT32_MAX : s21_INT32_MIN;
  else
    res *= sign;

  return res;
}
