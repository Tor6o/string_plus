#include "s21_string.h"

char *s21_strcpy(char *dest, const char *src) {
  char *ptr = dest;
  while (*src != '\0' && dest) {
    *dest = *src;
    dest++;
    src++;
  }
  if (dest) {
    *dest = '\0';
  }
  return ptr;
}
