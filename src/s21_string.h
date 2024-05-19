#ifndef SRC_S21_STRING_H_
#define SRC_S21_STRING_H_

#include <limits.h>
#include <locale.h>
#include <math.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>

#define S21_NULL ((void *)0)
#define s21_size_t unsigned long
#define UNSIGNED_MAX 4294967295

typedef struct {
  char flag[10];
  int width;
  int accuracy;
  char type;
} spec;

char *s21_reverse(char *str);
int s21_sprintf(char *str, const char *format, ...);
int searchModifiersForString(int x, const char *format, spec *config,
                             va_list *params);
int insertStringBySpecifier(char *str, char symbol, spec config,
                            va_list *params);
int setBaseAccuracyValue(int accuracy, int symbol);

int s21_ctos(char *str, va_list *params, char *flag, int accuracy, char type);
char *s21_conf(char *str, spec config, char symbol);
char *s21_stos(char *str, va_list *params, int accuracy, char type);
char *s21_ptoa(char *str, int *variable);
char *s21_itoa(char *str, int number, int accuracy, char *flag);
char *s21_itoa_long(char *str, long int number, int accuracy, char *flag);
char *s21_itoa_short(char *str, short int number, int accuracy, char *flag);
char *s21_gtoa_long(char *str, long double number, int accuracy, char *flag,
                    int symbol);
char *s21_gtoa(char *str, double number, int accuracy, char *flag, int symbol);
char *s21_ftoa_long(char *str, long double number, int afterpoint, char *flag,
                    int kostyl_2);
char *s21_ftoa(char *str, double number, int afterpoint, char *flag,
               int kostyl_2);
char *s21_utoa(char *str, unsigned int number, int format, int accuracy,
               char *flag);
char *s21_utoa_long(char *str, unsigned long int number, int format,
                    int accuracy, char *flag);
char *s21_utoa_short(char *str, unsigned short int number, int format,
                     int accuracy, char *flag);
char *s21_ntoa_long(char *str, long double number, int accuracy, char *flag,
                    int symbol, int kostyl_2);
char *s21_ntoa(char *str, double number, int accuracy, char *flag, int symbol,
               int kostyl_2);

void *s21_memchr(const void *str, int c, s21_size_t n);
int s21_memcmp(const void *str1, const void *str2, s21_size_t n);
void *s21_memcpy(void *dest, const void *src, s21_size_t n);
void *s21_memmove(void *dest, const void *src, s21_size_t n);

void *s21_memset(void *str, int c, s21_size_t n);
char *s21_strcat(char *dest, const char *src);
char *s21_strncat(char *dest, const char *src, s21_size_t n);
char *s21_strchr(const char *string, int c);

int s21_strcmp(const char *str1, const char *str2);
int s21_strncmp(const char *str1, const char *str2, s21_size_t n);

char *s21_strcpy(char *dest, const char *src);
char *s21_strncpy(char *dest, const char *src, s21_size_t n);

s21_size_t s21_strcspn(const char *str1, const char *str2);
char *s21_strerror(int errorNumber);
s21_size_t s21_strlen(const char *str);
char *s21_strpbrk(const char *str1, const char *str2);

char *s21_strrchr(const char *str1, int c);
s21_size_t s21_strspn(const char *str1, const char *str2);
char *s21_strstr(const char *haystack, const char *needle);
char *s21_strtok(char *str, const char *delim);

void *s21_to_upper(const char *str);
void *s21_to_lower(const char *str);
void *s21_insert(const char *src, const char *str, size_t start_index);
void *s21_trim(const char *src, const char *trim_chars);

#endif
