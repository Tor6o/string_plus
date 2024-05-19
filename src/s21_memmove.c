#include "s21_string.h"

void *s21_memmove(void *dest, const void *src, s21_size_t n) {
  char *p = dest;
  unsigned char *p_copy = (unsigned char *)src;
  unsigned char *p_copy_end = (unsigned char *)src + n;
  unsigned char *tmp_arr;
  tmp_arr = (unsigned char *)malloc(n * sizeof(unsigned char));
  for (int i = 0; p_copy < p_copy_end; i++, p_copy++) {
    tmp_arr[i] = *p_copy;
  }
  p_copy -= n;
  for (int i = 0; p_copy < p_copy_end; i++, p++, p_copy++) {
    *p = tmp_arr[i];
  }
  free(tmp_arr);
  return dest;
}