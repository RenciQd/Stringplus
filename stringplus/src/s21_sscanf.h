#ifndef SRC_S21_SSCANF_H_
#define SRC_S21_SSCANF_H_

#include <inttypes.h>
#include <limits.h>
#include <math.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define SPACE_SYM " \n\r\t\v\f"
#define FORMAT_WITWOUT_C "dieEfgGosuxXpn%%"

typedef long double ldouble;
typedef short int shint;
typedef long int loint;
typedef long long int llint;
typedef unsigned short int ushint;
typedef unsigned long int ulint;
typedef unsigned long long int ullint;
typedef int integer;
typedef unsigned int uinteger;

typedef struct sscanf_flags {
  int no_assign;
  int widht;
  char length;
  char spec;
} s_tok;

const char *scan_specifier(const char *format, s_tok *flags, bool *err_flag);
void delete_spaces(const char **string);
void print_spec(s_tok *sp);

int s21_ctoi(char c);
int check_base(const char *str);
char is_digit(char c);

bool check_sign(int *widht, const char **str);
bool s21_checknan(int widht, const char **str);
bool s21_checkinf(int widht, const char **str);
bool string_to_mem(const char **str, s_tok *flag, va_list *args);
bool char_to_mem(const char **str, s_tok *flag, va_list *args, bool *err_flag);
bool ui_to_mem(const char **str, s_tok *flag, va_list *args, int base,
               bool *err_flag);
bool us_to_mem(const char **str, s_tok *flag, va_list *args, int base,
               bool *err_flag);
bool ul_to_mem(const char **str, s_tok *flag, va_list *args, int base,
               bool *err_flag);
bool ull_to_mem(const char **str, s_tok *flag, va_list *args, int base,
                bool *err_flag);
bool int_to_mem(const char **str, s_tok *flag, va_list *args, int base,
                bool *err_flag);
bool ishort_to_mem(const char **str, s_tok *flag, va_list *args, int base,
                   bool *err_flag);
bool ilong_to_mem(const char **str, s_tok *flag, va_list *args, int base,
                  bool *err_flag);
bool illong_to_mem(const char **str, s_tok *flag, va_list *args, int base,
                   bool *err_flag);
bool float_to_mem(const char **str, s_tok *flag, va_list *args, bool *err_flag);
bool s21_strtod(const char **str, s_tok *flag, va_list *args, bool *err_flag);
bool s21_strtold(const char **str, s_tok *flag, va_list *args, bool *err_flag);
bool s21_case(const char *start, const char **str, s_tok *flag, va_list *args,
              bool *err_flag);
int s21_sscanf(const char *str, const char *format, ...);

#endif  //  SRC_S21_SSCANF_H_