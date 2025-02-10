#ifndef SRC_S21_STRING_H_
#define SRC_S21_STRING_H_

#include <math.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdlib.h>
#include <wchar.h>

#include "s21_sprintf.h"
#include "s21_sscanf.h"

#define BUFF_SIZE 4096
#define s21_INT32_MAX 2147483647
#define s21_INT32_MIN -2147483648
#define BUFFERSIZE 1024
#define EPS 0.000001f

typedef long unsigned int s21_size_t;
typedef long unsigned s21_size_t;
typedef long unsigned int s21_size_t;

#define s21_NULL ((void *)0)
#define S21_NULL ((void *)0)

void *s21_memchr(const void *str, int c, s21_size_t n);

int s21_memcmp(const void *str1, const void *str2, s21_size_t n);
void *s21_memcpy(void *dest, const void *src, s21_size_t n);
void *s21_memmove(void *dest, const void *src, s21_size_t n);
void *s21_memset(void *str, int c, s21_size_t n);
char *s21_strcat(char *dest, const char *src);
char *s21_strncat(char *dest, const char *src, s21_size_t n);
char *s21_strchr(const char *str, int c);
int s21_strcmp(const char *str1, const char *str2);
int s21_strncmp(const char *str1, const char *str2, s21_size_t n);
char *s21_strcpy(char *dest, const char *src);
char *s21_strncpy(char *dest, const char *src, s21_size_t n);
s21_size_t s21_strcspn(const char *str1, const char *str2);
char *s21_strerror(int errnum);
s21_size_t s21_strlen(const char *str);
char *s21_strpbrk(const char *str1, const char *str2);
char *s21_strrchr(const char *str, int c);
s21_size_t s21_strspn(const char *str1, const char *str2);
char *s21_strstr(const char *haystack, const char *needle);
char *s21_strtok(char *str, const char *delim);
char *convert(unsigned int num, int base);
int s21_sscanf(const char *str, const char *fmt, ...);
int s21_atoi(const char *str);
int s21_antoi(const char *str, s21_size_t n);
long long int s21_atol(const char *string);
long double s21_atof_sscanf(const char *string, int *err);
long double s21_atof(const char *string);
void *s21_to_upper(const char *str);
void *s21_to_lower(const char *str);
void *s21_insert(const char *src, const char *str, s21_size_t start_index);
void *s21_trim(const char *src, const char *trim_chars);
s21_size_t s21_find_start_index(const char *src, const char *trim_chars);
s21_size_t s21_find_end_index(const char *src, const char *trim_chars);

#endif  // S21_STRING_H_
