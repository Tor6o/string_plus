#include "s21_string.h"

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  s21_size_t i, length = s21_strlen(str1);
  for (i = 0; i < length && (s21_strchr(str2, str1[i]) == S21_NULL); i++) {
  }
  return i;
}