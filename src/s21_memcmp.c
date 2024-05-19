#include "s21_string.h"

int s21_memcmp(const void *str1, const void *str2, size_t n) {
  char *s1 = (char *)str1;
  char *s2 = (char *)str2;
  unsigned int i;

  for (i = 0; i < n && s1 + i != NULL && s2 + i != S21_NULL &&
              ((unsigned char)s1[i] == (unsigned char)s2[i]);
       i++) {
  }

  return ((unsigned char)(s1[i]) - (unsigned char)(s2[i])) * (i < n);
}
