#include "s21_string.h"

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  const char *p1 = str1;
  const char *p2 = str2;
  int res = 0;
  int flag = 0;
  s21_size_t step = 0;
  while ((*p1 != '\0' || *p2 != '\0') && step != n && (flag != 1)) {
    if ((*p1 - *p2) != 0) {
      res = *p1 - *p2;
      flag = 1;
    }
    p1++;
    p2++;
    step++;
  }
  return res;
}
