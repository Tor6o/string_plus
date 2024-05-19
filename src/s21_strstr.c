#include "s21_string.h"

char *s21_strstr(const char *haystack, const char *needle) {
  size_t n = s21_strlen(needle);
  char *r_value;

  while (*haystack && s21_memcmp(haystack, needle, n)) {
    haystack++;
  }
  if (!s21_memcmp(haystack, needle, n))
    r_value = (char *)haystack;
  else
    r_value = 0;
  return r_value;
}
