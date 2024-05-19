#include "s21_string.h"

s21_size_t lastChar(const char *str1, const char *str2);

void *s21_trim(const char *src, const char *trim_char) {
  char *result = S21_NULL;

  if (src == S21_NULL) {
    return S21_NULL;
  }
  s21_size_t length = s21_strlen(src);
  char default_chars[10] = " \t\n\v\r\f\0";

  if (trim_char == S21_NULL || s21_strlen(trim_char) == 0) {
    trim_char = default_chars;
  }
  s21_size_t firstTrimChar = s21_strspn(src, trim_char);
  s21_size_t lastTrimChar = lastChar(src, trim_char);
  if (length != firstTrimChar) {
    result = calloc(length - firstTrimChar - lastTrimChar + 1, sizeof(char));
  } else {
    result = calloc(1, sizeof(char));
  }
  if (result != S21_NULL) {
    if (length != firstTrimChar) {
      for (s21_size_t i = 0; i < length - firstTrimChar - lastTrimChar; i++) {
        result[i] = src[i + firstTrimChar];
      }
      result[length - firstTrimChar - lastTrimChar] = '\0';
    } else {
      result[0] = '\0';
    }
  }
  return result;
}

s21_size_t lastChar(const char *str1, const char *str2) {
  s21_size_t str1len = s21_strlen(str1);
  s21_size_t str2len = s21_strlen(str2);
  int move = 0;
  int result = 0;

  for (int i = (int)str1len - 1; i > -1 && move == 0; i--) {
    int reverse_res = 0;

    for (s21_size_t j = 0; j < str2len && reverse_res == 0; j++) {
      if (str1[i] == str2[j]) {
        reverse_res++;
      }
    }

    if (reverse_res == 0) {
      move++;
      result--;
    }

    result++;
  }

  return result;
}