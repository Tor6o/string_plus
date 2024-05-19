#include "s21_string.h"

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  s21_size_t i = 0;
  int flag = 0;
  while (i != n) {
    if (*(src + i) != '\0' && flag == 0) {
      *(dest + i) = *(src + i);
    } else {
      flag = 1;
    }
    if (flag != 0) {
      *(dest + i) = '\0';
    }
    i++;
  }
  return dest;
}
