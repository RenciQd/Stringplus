#include "s21_sscanf.h"

#include "s21_string.h"

// int sscanf(const char *str, const char *format, ...) - считывает
// форматированный ввод из строки.

// где:

// str − Это С-строка, которую функция обрабатывает в качестве источника для
// извлечения данных; format −  это С-строка, содержащая один или несколько
// следующих элементов: пробельный символ,
//  непробельный символ и спецификаторы формата.
//  Спецификатор формата для печатающих функций следует прототипу:
//  %[флаги][ширина][.точность][длина]спецификатор. Спецификатор формата для
//  сканирующих функций следует прототипу: %[*][ширина][длина]спецификатор.

void delete_spaces(const char **string) {
  const char *p_str = *string;
  while (s21_strchr(SPACE_SYM, *p_str) != s21_NULL && *p_str != '\0') p_str++;
  *string = p_str;
}

char is_digit(char c) { return c >= '0' && c <= '9'; }

const char *scan_specifier(const char *format, s_tok *spec, bool *err_flag) {
  s_tok flag = {0, -1, 0, 0};
  if (*format == '*') {
    flag.no_assign = 1;
    format++;
  }
  if (is_digit(*format)) {
    flag.widht = 0;
    while (is_digit(*format)) {
      flag.widht = flag.widht * 10 + s21_ctoi(*format);
      format++;
    }
  }
  if (s21_strchr("hLl", *format) != s21_NULL) {
    if (*format == 'l' && *(format + 1) == 'l') {
      flag.length = 'L';
      format += 2;
    } else {
      flag.length = *format;
      format++;
    }
  }
  if (s21_strchr("cdieEfgGosuxXpn%%", *format) != s21_NULL) {
    flag.spec = *format;
    format++;
  } else {
    *err_flag = false;
  }
  *spec = flag;

  return format;
}

bool char_to_mem(const char **str, s_tok *flag, va_list *args, bool *err_flag) {
  bool result = 0;
  const char *p_str = *str;
  if (flag->no_assign == 0) {
    char *var = va_arg(*args, char *);
    *var = *p_str;
    result = 1;
  }
  if (flag->widht >= 1) {
    p_str += flag->widht;
  } else if (flag->widht == 0) {
    *err_flag = false;
  } else {
    p_str++;
  }
  *str = p_str;
  return result;
}

bool string_to_mem(const char **str, s_tok *flag, va_list *args) {
  const char *p_str = *str;
  int res = 0;
  char *var;
  if (flag->no_assign == 0) {
    var = va_arg(*args, char *);
  } else {
    var = s21_NULL;
  }
  while (s21_strchr(SPACE_SYM, *p_str) == s21_NULL && *p_str &&
         flag->widht != 0) {
    if (flag->no_assign == 0) *var = *p_str;
    var++;
    p_str++;
    (flag->widht)--;
  }
  if (flag->no_assign == 0) *var = '\0';
  if (flag->no_assign == 0) {
    res = p_str != *str;
  }
  *str = p_str;
  return res;
}

bool check_sign(int *widht, const char **str) {
  const char *p_str = *str;
  int sign = 0;
  if (*widht != 0) {
    if (*p_str == '-' || *p_str == '+') {
      if (*p_str == '-') {
        sign = 1;
      }
      p_str++;
      (*widht)--;
    }
  }
  *str = p_str;
  return sign;
}

int s21_ctoi(char h) {
  int res = 0;
  if (h >= 'a' && h <= 'f')
    res = h - 'a' + 10;
  else if (h >= 'A' && h <= 'F')
    res = h - 'A' + 10;
  else if (h >= '0' && h <= '9')
    res = h - '0';
  return res;
}

int check_base(const char *str) {
  int base = 10;
  if (*str == '0' && (*(str + 1) == 'x' || *(str + 1) == 'X')) {
    base = 16;
  } else if (*str == '0') {
    base = 8;
  }
  return base;
}

bool s21_checkinf(int widht, const char **str) {
  const char *p_str = *str;
  int isinf = 0;
  if (widht == -1 || widht >= 3) {
    if ((*p_str == 'I' || *p_str == 'i') &&
        (*(p_str + 1) == 'N' || *(p_str + 1) == 'n') &&
        (*(p_str + 2) == 'F' || *(p_str + 2) == 'f')) {
      isinf = 1;
    }
  }
  return isinf;
}

bool s21_checknan(int widht, const char **str) {
  const char *p_str = *str;
  int isnan = 0;
  if (widht == -1 || widht >= 3) {
    if ((*p_str == 'N' || *p_str == 'n') &&
        (*(p_str + 1) == 'A' || *(p_str + 1) == 'a') &&
        (*(p_str + 2) == 'N' || *(p_str + 2) == 'n')) {
      isnan = 1;
    }
  }
  return isnan;
}

bool ui_to_mem(const char **str, s_tok *flag, va_list *args, int base,
               bool *err_flag) {
  char num_sys[] = "0123456789ABCDEFabcdef";
  int res = 0;
  bool overload = false;
  ullint next_num = 0, num = 0;

  int sign = check_sign(&flag->widht, str);
  const char *p_str = *str;

  if (base == 0) base = check_base(*str);
  if (base == 10) num_sys[10] = '\0';
  if (base == 8) num_sys[8] = '\0';

  if (base == 16 && *p_str == '0' &&
      (*(p_str + 1) == 'x' || *(p_str + 1) == 'X')) {
    p_str += 2;
    res = 1;
  }
  while (s21_strchr(num_sys, *p_str) != s21_NULL && flag->widht && *p_str) {
    num = next_num;
    next_num = num * base + s21_ctoi(*p_str);
    if (next_num < num)
      overload = true;
    else
      num = next_num;
    p_str++;
    flag->widht--;
    res = 1;
  }
  if (res == 0) *err_flag = false;
  *str = p_str;
  if (overload) {
    if (sign && 0) {
      num = LLONG_MIN;
    } else {
      num = ULLONG_MAX;
    }
  } else if (res) {
    if (sign) num = -num;
  }
  if (flag->no_assign == 0 && res) {
    uinteger *var = va_arg(*args, uinteger *);
    *var = num;
  } else {
    res = 0;
  }
  return res;
}

bool us_to_mem(const char **str, s_tok *flag, va_list *args, int base,
               bool *err_flag) {
  char num_sys[] = "0123456789ABCDEFabcdef";
  int res = 0;
  bool overload = false;
  ullint next_num = 0, num = 0;

  int sign = check_sign(&flag->widht, str);
  const char *p_str = *str;

  if (base == 0) base = check_base(*str);
  if (base == 10) num_sys[10] = '\0';
  if (base == 8) num_sys[8] = '\0';

  if (base == 16 && *p_str == '0' &&
      (*(p_str + 1) == 'x' || *(p_str + 1) == 'X')) {
    p_str += 2;
    res = 1;
  }
  while (s21_strchr(num_sys, *p_str) != s21_NULL && flag->widht && *p_str) {
    num = next_num;
    next_num = num * base + s21_ctoi(*p_str);
    if (next_num < num)
      overload = true;
    else
      num = next_num;
    p_str++;
    flag->widht--;
    res = 1;
  }
  if (res == 0) *err_flag = false;
  *str = p_str;
  if (overload) {
    if (sign && 0) {
      num = LLONG_MIN;
    } else {
      num = ULLONG_MAX;
    }
  } else if (res) {
    if (sign) num = -num;
  }
  if (flag->no_assign == 0 && res) {
    ushint *var = va_arg(*args, ushint *);
    *var = num;
  } else {
    res = 0;
  }
  return res;
}

bool ul_to_mem(const char **str, s_tok *flag, va_list *args, int base,
               bool *err_flag) {
  char num_sys[] = "0123456789ABCDEFabcdef";
  int res = 0;
  bool overload = false;
  ullint next_num = 0, num = 0;

  int sign = check_sign(&flag->widht, str);
  const char *p_str = *str;

  if (base == 0) base = check_base(*str);
  if (base == 10) num_sys[10] = '\0';
  if (base == 8) num_sys[8] = '\0';

  if (base == 16 && *p_str == '0' &&
      (*(p_str + 1) == 'x' || *(p_str + 1) == 'X')) {
    p_str += 2;
    res = 1;
  }
  while (s21_strchr(num_sys, *p_str) != s21_NULL && flag->widht && *p_str) {
    num = next_num;
    next_num = num * base + s21_ctoi(*p_str);
    if (next_num < num)
      overload = true;
    else
      num = next_num;
    p_str++;
    flag->widht--;
    res = 1;
  }
  if (res == 0) *err_flag = false;
  *str = p_str;
  if (overload) {
    if (sign && 0) {
      num = LLONG_MIN;
    } else {
      num = ULLONG_MAX;
    }
  } else if (res) {
    if (sign) num = -num;
  }
  if (flag->no_assign == 0 && res) {
    ulint *var = va_arg(*args, ulint *);
    *var = num;
  } else {
    res = 0;
  }
  return res;
}

bool ull_to_mem(const char **str, s_tok *flag, va_list *args, int base,
                bool *err_flag) {
  char num_sys[] = "0123456789ABCDEFabcdef";
  int res = 0;
  bool overload = false;
  ullint next_num = 0, num = 0;

  int sign = check_sign(&flag->widht, str);
  const char *p_str = *str;

  if (base == 0) base = check_base(*str);
  if (base == 10) num_sys[10] = '\0';
  if (base == 8) num_sys[8] = '\0';

  if (base == 16 && *p_str == '0' &&
      (*(p_str + 1) == 'x' || *(p_str + 1) == 'X')) {
    p_str += 2;
    res = 1;
  }
  while (s21_strchr(num_sys, *p_str) != s21_NULL && flag->widht && *p_str) {
    num = next_num;
    next_num = num * base + s21_ctoi(*p_str);
    if (next_num < num)
      overload = true;
    else
      num = next_num;
    p_str++;
    flag->widht--;
    res = 1;
  }
  if (res == 0) *err_flag = false;
  *str = p_str;
  if (overload) {
    if (sign && 0) {
      num = LLONG_MIN;
    } else {
      num = ULLONG_MAX;
    }
  } else if (res) {
    if (sign) num = -num;
  }
  if (flag->no_assign == 0 && res) {
    ullint *var = va_arg(*args, ullint *);
    *var = num;
  } else {
    res = 0;
  }
  return res;
}

bool int_to_mem(const char **str, s_tok *flag, va_list *args, int base,
                bool *err_flag) {
  char num_sys[] = "0123456789ABCDEFabcdef";
  int res = 0;
  bool overload = false;
  llint next_num = 0, num = 0;

  int sign = check_sign(&flag->widht, str);
  const char *p_str = *str;

  if (base == 0) base = check_base(*str);
  if (base == 10) num_sys[10] = '\0';
  if (base == 8) num_sys[8] = '\0';

  if (base == 16 && *p_str == '0' &&
      (*(p_str + 1) == 'x' || *(p_str + 1) == 'X')) {
    p_str += 2;
    res = 1;
  }
  while (s21_strchr(num_sys, *p_str) != s21_NULL && flag->widht && *p_str) {
    num = next_num;
    next_num = num * base + s21_ctoi(*p_str);
    if (next_num < num)
      overload = true;
    else
      num = next_num;
    p_str++;
    flag->widht--;
    res = 1;
  }
  if (res == 0) *err_flag = false;
  *str = p_str;
  if (overload) {
    if (sign && 1) {
      num = LLONG_MIN;
    } else {
      num = LLONG_MAX;
    }
  } else if (res) {
    if (sign) num = -num;
  }
  if (flag->no_assign == 0 && res) {
    integer *var = va_arg(*args, integer *);
    *var = num;
  } else {
    res = 0;
  }
  return res;
}

bool ishort_to_mem(const char **str, s_tok *flag, va_list *args, int base,
                   bool *err_flag) {
  char num_sys[] = "0123456789";
  int res = 0;
  bool overload = false;
  llint next_num = 0, num = 0;

  int sign = check_sign(&flag->widht, str);
  const char *p_str = *str;

  if (base == 0) base = check_base(*str);
  if (base == 10) num_sys[10] = '\0';
  if (base == 8) num_sys[8] = '\0';

  if (base == 16 && *p_str == '0' &&
      (*(p_str + 1) == 'x' || *(p_str + 1) == 'X')) {
    p_str += 2;
    res = 1;
  }
  while (s21_strchr(num_sys, *p_str) != s21_NULL && flag->widht && *p_str) {
    num = next_num;
    next_num = num * base + s21_ctoi(*p_str);
    if (next_num < num)
      overload = true;
    else
      num = next_num;
    p_str++;
    flag->widht--;
    res = 1;
  }
  if (res == 0) *err_flag = false;
  *str = p_str;
  if (overload) {
    if (sign && 1) {
      num = LLONG_MIN;
    } else {
      num = LLONG_MAX;
    }
  } else if (res) {
    if (sign) num = -num;
  }
  if (flag->no_assign == 0 && res) {
    shint *var = va_arg(*args, shint *);
    *var = num;
  } else {
    res = 0;
  }
  return res;
}

bool ilong_to_mem(const char **str, s_tok *flag, va_list *args, int base,
                  bool *err_flag) {
  char num_sys[] = "0123456789ABCDEFabcdef";
  int res = 0;
  bool overload = false;
  llint next_num = 0, num = 0;

  int sign = check_sign(&flag->widht, str);
  const char *p_str = *str;

  if (base == 0) base = check_base(*str);
  if (base == 10) num_sys[10] = '\0';
  if (base == 8) num_sys[8] = '\0';

  if (base == 16 && *p_str == '0' &&
      (*(p_str + 1) == 'x' || *(p_str + 1) == 'X')) {
    p_str += 2;
    res = 1;
  }
  while (s21_strchr(num_sys, *p_str) != s21_NULL && flag->widht && *p_str) {
    num = next_num;
    next_num = num * base + s21_ctoi(*p_str);
    if (next_num < num)
      overload = true;
    else
      num = next_num;
    p_str++;
    flag->widht--;
    res = 1;
  }
  if (res == 0) *err_flag = false;
  *str = p_str;
  if (overload) {
    if (sign && 1) {
      num = LLONG_MIN;
    } else {
      num = LLONG_MAX;
    }
  } else if (res) {
    if (sign) num = -num;
  }
  if (flag->no_assign == 0 && res) {
    loint *var = va_arg(*args, loint *);
    *var = num;
  } else {
    res = 0;
  }
  return res;
}

bool illong_to_mem(const char **str, s_tok *flag, va_list *args, int base,
                   bool *err_flag) {
  char num_sys[] = "0123456789ABCDEFabcdef";
  int res = 0;
  bool overload = false;
  llint next_num = 0, num = 0;

  int sign = check_sign(&flag->widht, str);
  const char *p_str = *str;

  if (base == 0) base = check_base(*str);
  if (base == 10) num_sys[10] = '\0';
  if (base == 8) num_sys[8] = '\0';

  if (base == 16 && *p_str == '0' &&
      (*(p_str + 1) == 'x' || *(p_str + 1) == 'X')) {
    p_str += 2;
    res = 1;
  }
  while (s21_strchr(num_sys, *p_str) != s21_NULL && flag->widht && *p_str) {
    num = next_num;
    next_num = num * base + s21_ctoi(*p_str);
    if (next_num < num)
      overload = true;
    else
      num = next_num;
    p_str++;
    flag->widht--;
    res = 1;
  }
  if (res == 0) *err_flag = false;
  *str = p_str;
  if (overload) {
    if (sign && 1) {
      num = LLONG_MIN;
    } else {
      num = LLONG_MAX;
    }
  } else if (res) {
    if (sign) num = -num;
  }
  if (flag->no_assign == 0 && res) {
    llint *var = va_arg(*args, llint *);
    *var = num;
  } else {
    res = 0;
  }
  return res;
}

bool float_to_mem(const char **str, s_tok *flag, va_list *args,
                  bool *err_flag) {
  long double res_float = 0;
  int res = 0;
  long double f_pow = 0.1;

  int exp_pow = 0;
  int exp_res = 0;

  int sign = check_sign(&flag->widht, str);
  const char *p_str = *str;

  if (s21_checkinf(flag->widht, str)) {
    res_float = 1.0 / 0.0;
    p_str += 3;
    res = 1;
  } else if (s21_checknan(flag->widht, str)) {
    res_float = 0.0 / 0.0;
    p_str += 3;
    res = 1;
  } else {
    if (is_digit(*p_str) && *p_str) {
      res = 1;
      while (is_digit(*p_str) && *p_str && flag->widht) {
        res_float = res_float * 10 + s21_ctoi(*p_str);
        p_str++;
        flag->widht--;
      }
    }

    if (*p_str == '.' && *err_flag && flag->widht) {
      p_str++;
      if (is_digit(*p_str) && *p_str && flag->widht) {
        flag->widht--;
        res = 1;
        while (is_digit(*p_str) && *p_str && flag->widht) {
          res_float += f_pow * s21_ctoi(*p_str);
          f_pow /= 10;
          p_str++;
          flag->widht--;
        }
      } else if (p_str - *str == 1)
        *err_flag = false;
    }
    if ((*p_str == 'e' || *p_str == 'E') && *err_flag) {
      res = 1;
      p_str++;
      flag->widht--;
      int exp_neg = check_sign(&flag->widht, &p_str);
      bool overload = false;
      if (is_digit(*p_str)) {
        while (is_digit(*p_str) && flag->widht && *p_str) {
          int next = exp_pow;
          next = exp_pow * 10 + s21_ctoi(*p_str);
          if (next < exp_pow) {
            exp_pow = -1;
            overload = true;
          } else {
            exp_pow = next;
            p_str++;
            flag->widht--;
            exp_res = 1;
          }
        }
      }
      if (exp_res == 1 && !overload)
        res_float *= pow(10, exp_neg ? -exp_pow : exp_pow);
    }
  }
  if (flag->no_assign) res = 0;

  *str = p_str;
  if (sign) res_float = -res_float;
  if (flag->no_assign == 0 && res) {
    float *var = va_arg(*args, float *);
    *var = res_float;
  }
  return res;
}

bool s21_strtod(const char **str, s_tok *flag, va_list *args, bool *err_flag) {
  long double res_float = 0;
  int res = 0;
  long double f_pow = 0.1;

  int exp_pow = 0;
  int exp_res = 0;

  int sign = check_sign(&flag->widht, str);
  const char *p_str = *str;

  if (s21_checkinf(flag->widht, str)) {
    res_float = 1.0 / 0.0;
    p_str += 3;
    res = 1;
  } else if (s21_checknan(flag->widht, str)) {
    res_float = 0.0 / 0.0;
    p_str += 3;
    res = 1;
  } else {
    if (is_digit(*p_str) && *p_str) {
      res = 1;
      while (is_digit(*p_str) && *p_str && flag->widht) {
        res_float = res_float * 10 + s21_ctoi(*p_str);
        p_str++;
        flag->widht--;
      }
    }

    if (*p_str == '.' && *err_flag && flag->widht) {
      p_str++;
      if (is_digit(*p_str) && *p_str && flag->widht) {
        flag->widht--;
        res = 1;
        while (is_digit(*p_str) && *p_str && flag->widht) {
          res_float += f_pow * s21_ctoi(*p_str);
          f_pow /= 10;
          p_str++;
          flag->widht--;
        }
      } else if (p_str - *str == 1)
        *err_flag = false;
    }
    if ((*p_str == 'e' || *p_str == 'E') && *err_flag) {
      res = 1;
      p_str++;
      flag->widht--;
      int exp_neg = check_sign(&flag->widht, &p_str);
      bool overload = false;
      if (is_digit(*p_str)) {
        while (is_digit(*p_str) && flag->widht && *p_str) {
          int next = exp_pow;
          next = exp_pow * 10 + s21_ctoi(*p_str);
          if (next < exp_pow) {
            exp_pow = -1;
            overload = true;
          } else {
            exp_pow = next;
            p_str++;
            flag->widht--;
            exp_res = 1;
          }
        }
      }
      if (exp_res == 1 && !overload)
        res_float *= pow(10, exp_neg ? -exp_pow : exp_pow);
    }
  }
  if (flag->no_assign) res = 0;

  *str = p_str;
  if (sign) res_float = -res_float;
  if (flag->no_assign == 0 && res) {
    double *var = va_arg(*args, double *);
    *var = res_float;
  }
  return res;
}

bool s21_strtold(const char **str, s_tok *flag, va_list *args, bool *err_flag) {
  long double res_float = 0;
  int res = 0;
  long double f_pow = 0.1;

  int exp_pow = 0;
  int exp_res = 0;

  int sign = check_sign(&flag->widht, str);
  const char *p_str = *str;

  if (s21_checkinf(flag->widht, str)) {
    res_float = 1.0 / 0.0;
    p_str += 3;
    res = 1;
  } else if (s21_checknan(flag->widht, str)) {
    res_float = 0.0 / 0.0;
    p_str += 3;
    res = 1;
  } else {
    if (is_digit(*p_str) && *p_str) {
      res = 1;
      while (is_digit(*p_str) && *p_str && flag->widht) {
        res_float = res_float * 10 + s21_ctoi(*p_str);
        p_str++;
        flag->widht--;
      }
    }

    if (*p_str == '.' && *err_flag && flag->widht) {
      p_str++;
      if (is_digit(*p_str) && *p_str && flag->widht) {
        flag->widht--;
        res = 1;
        while (is_digit(*p_str) && *p_str && flag->widht) {
          res_float += f_pow * s21_ctoi(*p_str);
          f_pow /= 10;
          p_str++;
          flag->widht--;
        }
      } else if (p_str - *str == 1)
        *err_flag = false;
    }
    if ((*p_str == 'e' || *p_str == 'E') && *err_flag) {
      res = 1;
      p_str++;
      flag->widht--;
      int exp_neg = check_sign(&flag->widht, &p_str);
      bool overload = false;
      if (is_digit(*p_str)) {
        while (is_digit(*p_str) && flag->widht && *p_str) {
          int next = exp_pow;
          next = exp_pow * 10 + s21_ctoi(*p_str);
          if (next < exp_pow) {
            exp_pow = -1;
            overload = true;
          } else {
            exp_pow = next;
            p_str++;
            flag->widht--;
            exp_res = 1;
          }
        }
      }
      if (exp_res == 1 && !overload)
        res_float *= pow(10, exp_neg ? -exp_pow : exp_pow);
    }
  }
  if (flag->no_assign) res = 0;

  *str = p_str;
  if (sign) res_float = -res_float;
  if (flag->no_assign == 0 && res) {
    ldouble *var = va_arg(*args, ldouble *);
    *var = res_float;
  }
  return res;
}

bool s21_case(const char *start, const char **str, s_tok *flag, va_list *args,
              bool *err_flag) {
  bool success = 0;
  switch (flag->spec) {
    case 'c':
      success = char_to_mem(str, flag, args, err_flag);
      break;
    case 's':
      success = string_to_mem(str, flag, args);
      break;
    case 'd':
      if (flag->length == 'h')
        success = ishort_to_mem(str, flag, args, 10, err_flag);
      else if (flag->length == 'l')
        success = ilong_to_mem(str, flag, args, 10, err_flag);
      else if (flag->length == 'L')
        success = illong_to_mem(str, flag, args, 10, err_flag);
      else
        success = int_to_mem(str, flag, args, 10, err_flag);
      break;
    case 'u':
      if (flag->length == 'h')
        success = us_to_mem(str, flag, args, 10, err_flag);
      else if (flag->length == 'l')
        success = ul_to_mem(str, flag, args, 10, err_flag);
      else if (flag->length == 'L')
        success = ull_to_mem(str, flag, args, 10, err_flag);
      else
        success = ui_to_mem(str, flag, args, 10, err_flag);
      break;
    case 'i':
      if (flag->length == 'h')
        success = ishort_to_mem(str, flag, args, 0, err_flag);
      else if (flag->length == 'l')
        success = ilong_to_mem(str, flag, args, 0, err_flag);
      else if (flag->length == 'L')
        success = illong_to_mem(str, flag, args, 0, err_flag);
      else
        success = int_to_mem(str, flag, args, 0, err_flag);
      break;
    case 'o':
      if (flag->length == 'h')
        success = us_to_mem(str, flag, args, 8, err_flag);
      else if (flag->length == 'l')
        success = ul_to_mem(str, flag, args, 8, err_flag);
      else if (flag->length == 'L')
        success = ull_to_mem(str, flag, args, 8, err_flag);
      else
        success = ui_to_mem(str, flag, args, 8, err_flag);
      break;
    case 'x':
    case 'X':
      if (flag->length == 'h')
        success = us_to_mem(str, flag, args, 16, err_flag);
      else if (flag->length == 'l')
        success = ul_to_mem(str, flag, args, 16, err_flag);
      else if (flag->length == 'L')
        success = ull_to_mem(str, flag, args, 16, err_flag);
      else
        success = ui_to_mem(str, flag, args, 16, err_flag);
      break;
    case 'p':
      success = ull_to_mem(str, flag, args, 16, err_flag);
      break;
    case 'e':
    case 'E':
    case 'f':
    case 'g':
    case 'G':
      if (flag->length == 'l')
        success = s21_strtod(str, flag, args, err_flag);
      else if (flag->length == 'L')
        success = s21_strtold(str, flag, args, err_flag);
      else
        success = float_to_mem(str, flag, args, err_flag);
      break;
    case 'n':;
      int *n = va_arg(*args, int *);
      *n = *str - start;
      break;
    case '%':
      (*str)++;
      break;
  }
  return success;
}

int s21_sscanf(const char *str, const char *format, ...) {
  const char *start = str;
  int count_success = 0;
  va_list(args);
  va_start(args, format);
  bool err_flag = true;
  while (*format && err_flag) {
    if (*format == *str && s21_strchr(SPACE_SYM, *format) == s21_NULL &&
        *format != '%') {
      format++;
      str++;
      continue;
    } else if (s21_strchr(SPACE_SYM, *format) != s21_NULL) {
      delete_spaces(&format);
      delete_spaces(&str);
      continue;
    } else if (*format == '%') {
      s_tok spec;
      format = scan_specifier(++format, &spec, &err_flag);
      if (!err_flag) {
        continue;
      }
      if (spec.spec != 'c' || (spec.spec == 'c' && spec.widht > 0)) {
        delete_spaces(&str);
      }
      if (!*str && count_success == 0) {
        count_success = -!count_success;
      } else {
        if (*str) {
          count_success += s21_case(start, &str, &spec, &args, &err_flag);
        }
      }
    } else {
      err_flag = false;
    }
  }
  va_end(args);
  return count_success;
}