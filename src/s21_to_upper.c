#include <string.h>

#include "s21_string.h"

void *s21_to_upper(const char *str) {
  if (!str) return S21_NULL;
  s21_size_t str_len = strlen(str);
  char *ptr = calloc(str_len + 1, sizeof(char));
  for (s21_size_t i = 0; i < str_len; i++)
    ptr[i] = str[i] - ((str[i] >= 'a' && str[i] <= 'z') ? 32 : 0);
  return ptr;
}