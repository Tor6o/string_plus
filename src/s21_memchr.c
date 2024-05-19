#include "s21_string.h"

void *s21_memchr(const void *str, int c, size_t n) {
  char *s = (char *)str;
  unsigned int i = 0;

  for (; s + i != NULL && i < n; i++) {
    if (c == *(s + i)) return s + i;
  }
  return S21_NULL;
}
