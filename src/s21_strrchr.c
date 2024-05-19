#include "s21_string.h"

char *s21_strrchr(const char *str, int c) {
  const char *found, *p;
  char *r_value;
  c = (unsigned char)c;
  if (c != '\0') {
    found = S21_NULL;
    while ((p = s21_strchr(str, c)) != S21_NULL) {
      found = p;
      str = p + 1;
    }
    r_value = (char *)found;
  } else
    r_value = s21_strchr(str, '\0');
  return r_value;
}