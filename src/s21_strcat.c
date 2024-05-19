#include "s21_string.h"

char *s21_strcat(char *dest, const char *src) {
  int length = s21_strlen(dest);
  int i = 0;
  while (src[i] != '\0') {
    dest[length] = src[i];
    i++;
    length++;
  }
  dest[length] = '\0';
  return dest;
}
