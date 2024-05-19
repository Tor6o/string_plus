#include "s21_string.h"

s21_size_t s21_strspn(const char *str1, const char *str2) {
  s21_size_t result = 0;
  s21_size_t len1 = s21_strlen(str1);
  s21_size_t len2 = s21_strlen(str2);
  s21_size_t j;
  int flag = 0;

  for (s21_size_t i = 0; i < len1 && (!flag); i++) {
    flag = 0;
    for (j = 0; j < len2 && str1[i] != str2[j]; j++) {
    }
    if (str1[i] != str2[j])
      flag = 1;
    else
      result++;
  }
  return result;
}