#include <check.h>
#include <stdio.h>
#include <string.h>

#include "s21_string.h"

#define BUFF_SIZE 512

#if defined(__linux__)
#define PLATFORM_NAME "LINUX"
#elif defined(__APPLE__)
#define PLATFORM_NAME "MAC"
#endif

START_TEST(s21_memchr_tests_case) {
  char *str = "string";
  char *str1 = "0123456789";
  char *str2 = "Hello world";
  ck_assert_str_eq(memchr(str, 's', 6), s21_memchr(str, 's', 6));
  ck_assert_str_eq(memchr(str, 'g', 100), s21_memchr(str, 'g', 100));
  ck_assert_str_eq(memchr(str1, '6', 10), s21_memchr(str1, '6', 10));
  ck_assert_str_eq(memchr(str2, 101, 10), s21_memchr(str2, 101, 10));
  ck_assert_pstr_eq(memchr(str2, 'a', 10), s21_memchr(str2, 'a', 10));
}
END_TEST

START_TEST(s21_memcmp_tests_case) {
  char *str = "Hello world";
  char *str1 = "Hello world";
  ck_assert_int_eq(memcmp(str, str1, 2), s21_memcmp(str, str1, 2));

  str = "Hellaworld";
  str1 = "Helloworld";
  ck_assert_int_eq(memcmp(str, str1, 10), s21_memcmp(str, str1, 10));

  str = "Hello\0wo\0ld";
  str1 = "Hello\0wo\0ld";
  ck_assert_int_eq(memcmp(str, str1, 6), s21_memcmp(str, str1, 6));

  str = "Helo\0wo\0ld";
  str1 = "Hello\0wo\0ld";
  ck_assert_int_eq(memcmp(str, str1, 8), s21_memcmp(str, str1, 8));

  str = "Hello\0w2\0ld";
  str1 = "Hello\0wo\0ld";
  ck_assert_int_eq(memcmp(str, str1, 8), s21_memcmp(str, str1, 8));

  str = "\0Hallo\0w2\0ld";
  str1 = "\0Hello\0wo\0ld";
  ck_assert_int_eq(memcmp(str, str1, 6), s21_memcmp(str, str1, 6));

  str = "\0\0\0";
  str1 = "\0\0\0";
  ck_assert_int_eq(memcmp(str, str1, 2), s21_memcmp(str, str1, 2));

  str = "\0";
  str1 = "\0";
  ck_assert_int_eq(memcmp(str, str1, 0), s21_memcmp(str, str1, 0));

  str = "";
  str1 = "";
  ck_assert_int_eq(memcmp(str, str1, 1), s21_memcmp(str, str1, 1));

  str = "\0";
  str1 = " ";
  ck_assert_int_eq(memcmp(str, str1, 0), s21_memcmp(str, str1, 0));
}
END_TEST

START_TEST(s21_memcpy_tests_case) {
  char dest1[15] = "1234567890";
  char dest2[15] = "1234567890";
  char src[10] = "asdfdads";
  memcpy(dest1, src, 10);
  s21_memcpy(dest2, src, 10);
  ck_assert_str_eq(dest1, dest2);

  char dest12[15] = "1234567890";
  char dest22[15] = "1234567890";
  memcpy(dest12, src, 1);
  s21_memcpy(dest22, src, 1);
  ck_assert_str_eq(dest1, dest2);

  memcpy(S21_NULL, S21_NULL, 1);
  s21_memcpy(S21_NULL, S21_NULL, 1);
  ck_assert_str_eq(dest1, dest2);
}
END_TEST

START_TEST(s21_memmove_tests_case_1) {
#ifdef __APPLE__
  char dest1[15] = "sfdsf";
  char dest2[15] = "sdfsdf";
  char src[15] = "kjshnfljk";
  size_t chek_dest = 0;
  memmove(dest1, src, 15);
  s21_memmove(dest2, src, 15);
  ck_assert_mem_eq(dest1, dest2, chek_dest);
#else
  char dest1[15] = "sfdsf";
  char dest2[15] = "sdfsdf";
  char src[15] = "kjshnfljk";
  memmove(dest1, src, 15);
  s21_memmove(dest2, src, 15);
  ck_assert_str_eq(dest1, dest2);
#endif
}
END_TEST

START_TEST(s21_memmove_tests_case_2) {
  char src[200] = "";
  char src2[200] = "";
  size_t copy_kByte = 0;
  char *res = src;
  char *expected = src2;
  s21_memmove(res, src, copy_kByte);
  memmove(expected, src2, copy_kByte);
  ck_assert_str_eq(res, expected);
}
END_TEST

START_TEST(s21_memmove_tests_case_3) {
  char src[200] = "";
  char src2[200] = "";
  size_t copy_kByte = 0;
  char res[200] = "i hate memcmp";
  char expected[200] = "i hate memcmp";
  s21_memmove(res, src, copy_kByte);
  memmove(expected, src2, copy_kByte);
  ck_assert_str_eq(res, expected);
}
END_TEST

START_TEST(s21_memmove_S21_NULLdest_tests) {
  char src[200] = "";
  char src2[200] = "";
  size_t copy_kByte = 0;
  char *res = S21_NULL;
  char *expected = S21_NULL;
  s21_memmove(res, src, copy_kByte);
  memmove(expected, src2, copy_kByte);
  ck_assert_pstr_eq(res, expected);
}
END_TEST

START_TEST(s21_memmove_S21_NULLsrc_tests) {
  char *src = S21_NULL;
  char *src2 = S21_NULL;
  size_t copy_kByte = 0;
  char res[200] = "i hate memcmp";
  char expected[200] = "i hate memcmp";
  s21_memmove(res, src, copy_kByte);
  memmove(expected, src2, copy_kByte);
  ck_assert_pstr_eq(res, expected);
}
END_TEST

START_TEST(s21_memmove_dest_lower_src_tests) {
  char str1[] = "Banana", str3[] = "Banana";
  char str2[] = "Apple", str4[] = "Apple";
  ck_assert_pstr_eq(s21_memmove(str3, str4, sizeof(str4)),
                    memmove(str1, str2, sizeof(str2)));
}
END_TEST

START_TEST(s21_memmove_tests_case_4) {
  char src[200] = "Hate";
  char src2[200] = "Hate";
  size_t copy_kByte = 4;
  char res[200] = "i hate verter";
  char expected[200] = "i hate verter";
  s21_memmove(res + 5, src, copy_kByte);
  memmove(expected + 5, src2, copy_kByte);
  ck_assert_str_eq(res, expected);
}
END_TEST

START_TEST(s21_memset_tests_case) {
  char dest1[15] = "1234567890";
  char dest2[15] = "1234567890";
  memset(dest1, '1', 10);
  s21_memset(dest2, '1', 10);
  ck_assert_str_eq(dest1, dest2);
}
END_TEST

START_TEST(s21_strchr_tests_case) {
  char *str = "Hello world";
  ck_assert_str_eq(strchr(str, 'e'), s21_strchr(str, 'e'));
  ck_assert_str_eq(strchr(str, 'H'), s21_strchr(str, 'H'));
  ck_assert_str_eq(strchr(str, '\0'), s21_strchr(str, '\0'));

  str = "01234";
  ck_assert_str_eq(strchr(str, '0'), s21_strchr(str, '0'));
  ck_assert_str_eq(strchr(str, '4'), s21_strchr(str, '4'));
}
END_TEST

START_TEST(s21_strlen_tests_case) {
  char str1[] = "abc.defghij.kl";
  char str2[] = "./i";
  char str3[] = "abc.defghij.kl  addsa adsasd";
  char str4[] =
      "dajskljasd asd isadlj j dasdouisadousd ioas d,jads lkjaklsdj aei a ";
  ck_assert_int_eq(strlen(str1), s21_strlen(str1));
  ck_assert_int_eq(strlen(str2), s21_strlen(str2));
  ck_assert_int_eq(strlen(str3), s21_strlen(str3));
  ck_assert_int_eq(strlen(str4), s21_strlen(str4));
}
END_TEST

START_TEST(s21_strcpy_tests_case) {
  char dest1[15] = "1234567890";
  char dest2[15] = "1234567890";
  char src[10] = "abcdsfsda";
  strcpy(dest1, src);
  s21_strcpy(dest2, src);
  ck_assert_str_eq(dest1, dest2);
}
END_TEST

START_TEST(s21_strncpy_tests_case) {
  char dest1[15] = "";
  char dest2[15] = "";
  char src[15] = "ljkamfdng";
  s21_strncpy(dest2, src, 3);
  strncpy(dest1, src, 15);
  s21_strncpy(dest2, src, 15);
  ck_assert_str_eq(dest1, dest2);
}
END_TEST

START_TEST(s21_strcmp_tests_case) {
  char *str = "Hello world";
  char *str1 = "Hello world";
  ck_assert_int_eq(strcmp(str, str1), s21_strcmp(str, str1));

  char *a = "Hellaworld";
  char *b = "Helloworld";
  int got = s21_strcmp(a, b);
  int expected = strcmp(a, b);

  if (got > 1) got = 1;
  if (expected > 1) expected = 1;

  if (got < -1) got = -1;
  if (expected < -1) expected = -1;

  ck_assert_int_eq(got, expected);

  str = "Hello\0wo\0ld";
  str1 = "Hello\0wo\0ld";
  ck_assert_int_eq(strcmp(str, str1), s21_strcmp(str, str1));

  a = "Helo\0wo\0ld";
  b = "Hello\0wo\0ld";
  got = s21_strcmp(a, b);
  expected = strcmp(a, b);

  if (got > 1) got = 1;
  if (expected > 1) expected = 1;

  if (got < -1) got = -1;
  if (expected < -1) expected = -1;

  ck_assert_int_eq(got, expected);

  str = "Hello\0w2\0ld";
  str1 = "Hello\0wo\0ld";
  ck_assert_int_eq(strcmp(str, str1), s21_strcmp(str, str1));

  str = "\0Hello\0w2\0ld";
  str1 = "\0Hello\0wo\0ld";
  ck_assert_int_eq(strcmp(str, str1), s21_strcmp(str, str1));

  str = "\0\0\0";
  str1 = "\0\0\0";
  ck_assert_int_eq(strcmp(str, str1), s21_strcmp(str, str1));

  str = "\0";
  str1 = "\0";
  ck_assert_int_eq(strcmp(str, str1), s21_strcmp(str, str1));

  str = "";
  str1 = "";
  ck_assert_int_eq(strcmp(str, str1), s21_strcmp(str, str1));

  a = "\0";
  b = " ";
  got = s21_strcmp(a, b);
  expected = strcmp(a, b);

  if (got > 1) got = 1;
  if (expected > 1) expected = 1;

  if (got < -1) got = -1;
  if (expected < -1) expected = -1;

  ck_assert_int_eq(got, expected);
}
END_TEST

START_TEST(s21_strncmp_tests_case_1) {
  char *str = "Hello world";
  char *str1 = "Hello world";
  ck_assert_int_eq(strncmp(str, str1, 2), s21_strncmp(str, str1, 2));

  str1 = "Hellaworld";
  char *str2 = "Helloworld";
  s21_size_t n_byte = 120;

  int got = s21_strncmp(str1, str2, n_byte);
  int expected = strncmp(str1, str2, n_byte);

  if (got > 1) got = 1;
  if (expected > 1) expected = 1;

  if (got < -1) got = -1;
  if (expected < -1) expected = -1;

  ck_assert_int_eq(got, expected);

  str = "Hello\0wo\0ld";
  str1 = "Hello\0wo\0ld";
  ck_assert_int_eq(strncmp(str, str1, 6), s21_strncmp(str, str1, 6));

  str1 = "Helo\0wo\0ld";
  str2 = "Hello\0wo\0ld";
  n_byte = 8;

  got = s21_strncmp(str1, str2, n_byte);
  expected = strncmp(str1, str2, n_byte);

  if (got > 1) got = 1;
  if (expected > 1) expected = 1;

  if (got < -1) got = -1;
  if (expected < -1) expected = -1;

  ck_assert_int_eq(got, expected);

  str = "Hello\0w2\0ld";
  str1 = "Hello\0wo\0ld";
  ck_assert_int_eq(strncmp(str, str1, 8), s21_strncmp(str, str1, 8));

  str = "\0Hallo\0w2\0ld";
  str1 = "\0Hello\0wo\0ld";
  ck_assert_int_eq(strncmp(str, str1, 15), s21_strncmp(str, str1, 15));

  str = "\0\0\0";
  str1 = "\0\0\0";
  ck_assert_int_eq(strncmp(str, str1, 2), s21_strncmp(str, str1, 2));

  str = "\0";
  str1 = "\0";
  ck_assert_int_eq(strncmp(str, str1, 0), s21_strncmp(str, str1, 0));

  str = "";
  str1 = "";
  ck_assert_int_eq(strncmp(str, str1, 1), s21_strncmp(str, str1, 1));

  str1 = "\0";
  str2 = " ";
  n_byte = 6;

  got = s21_strncmp(str1, str2, n_byte);
  expected = strncmp(str1, str2, n_byte);

  if (got > 1) got = 1;
  if (expected > 1) expected = 1;

  if (got < -1) got = -1;
  if (expected < -1) expected = -1;

  ck_assert_int_eq(got, expected);
}
END_TEST

START_TEST(s21_strstr_tests_case) {
  char *str = "Hello world";
  char *find = "el";
  ck_assert_str_eq(strstr(str, find), s21_strstr(str, find));

  str = "Hello world";
  find = "\0";
  ck_assert_str_eq(strstr(str, find), s21_strstr(str, find));

  str = "Hello world";
  find = "d";
  ck_assert_str_eq(strstr(str, find), s21_strstr(str, find));

  str = "Hello world";
  find = "Hello world";
  ck_assert_str_eq(strstr(str, find), s21_strstr(str, find));

  str = "012345678";
  find = "56";
  ck_assert_str_eq(strstr(str, find), s21_strstr(str, find));

  str = "01234567";
  find = "89";
  ck_assert_pstr_eq(strstr(str, find), s21_strstr(str, find));

  str = "!@#$%^&*(";
  find = "$%";
  ck_assert_str_eq(strstr(str, find), s21_strstr(str, find));
}
END_TEST

START_TEST(s21_strcat_tests_case_1) {
  char str_des1[30] = "Hello world";
  char str_des2[30] = "Hello world";
  char str1[] = "Hello world";
  ck_assert_str_eq(strcat(str_des1, str1), s21_strcat(str_des2, str1));
}
END_TEST

START_TEST(s21_strcat_tests_case_2) {
  char str_des1[30] = "Hello world";
  char str_des2[30] = "Hello world";
  char str1[] = "Helloworld";
  ck_assert_str_eq(strcat(str_des1, str1), s21_strcat(str_des2, str1));
}
END_TEST

START_TEST(s21_strcat_tests_case_3) {
  char str[30] = "Hello\0wo\0ld";
  char str1[] = "Hello\0wo\0ld";
  ck_assert_str_eq(strcat(str, str1), s21_strcat(str, str1));
}
END_TEST

START_TEST(s21_strcat_tests_case_4) {
  char str[30] = "Helo\0wo\0ld";
  char str1[] = "Hello\0wo\0ld";
  ck_assert_str_eq(strcat(str, str1), s21_strcat(str, str1));
}
END_TEST

START_TEST(s21_strcat_tests_case_5) {
  char str[30] = "Hello\0w2\0ld";
  char str1[] = "Hello\0wo\0ld";
  ck_assert_str_eq(strcat(str, str1), s21_strcat(str, str1));
}
END_TEST

START_TEST(s21_strcat_tests_case_6) {
  char str[30] = "\0Hello\0w2\0ld";
  char str1[] = "\0Hello\0wo\0ld";
  ck_assert_str_eq(strcat(str, str1), s21_strcat(str, str1));
}
END_TEST

START_TEST(s21_strcat_tests_case_7) {
  char str[30] = "\0\0\0";
  char str1[] = "\0\0\0";
  ck_assert_str_eq(strcat(str, str1), s21_strcat(str, str1));
}
END_TEST

START_TEST(s21_strcat_tests_case_8) {
  char str[30] = "\0";
  char str1[] = "\0";
  ck_assert_str_eq(strcat(str, str1), s21_strcat(str, str1));
}
END_TEST

START_TEST(s21_strcat_tests_case_9) {
  char str[30] = "";
  char str1[] = "";
  ck_assert_str_eq(strcat(str, str1), s21_strcat(str, str1));
}
END_TEST

START_TEST(s21_strcat_tests_case_10) {
  char str[30] = "\0";
  char str1[] = " ";
  ck_assert_str_eq(strcat(str, str1), s21_strcat(str, str1));
}
END_TEST

START_TEST(s21_strncat_tests_case_1) {
  char str[30] = "Hello world";
  char str1[] = "Hello world";
  ck_assert_str_eq(strncat(str, str1, 5), s21_strncat(str, str1, 5));
}
END_TEST

START_TEST(s21_strncat_tests_case_2) {
  char str[100] = "Hellaworld";
  char str1[] = "Helloworld";
  ck_assert_str_eq(strncat(str, str1, 5), s21_strncat(str, str1, 5));
}
END_TEST

START_TEST(s21_strncat_tests_case_3) {
  char str[30] = "Hello\0wo\0ld";
  char str1[] = "Hello\0wo\0ld";
  ck_assert_str_eq(strncat(str, str1, 0), s21_strncat(str, str1, 0));
}
END_TEST

START_TEST(s21_strncat_tests_case_4) {
  char str[30] = "Helo\0wo\0ld";
  char str1[] = "Hello\0wo\0ld";
  ck_assert_str_eq(strncat(str, str1, 10), s21_strncat(str, str1, 10));
}
END_TEST

START_TEST(s21_strncat_tests_case_5) {
  char str[30] = "Hello\0w2\0ld";
  char str1[] = "Hello\0wo\0ld";
  ck_assert_str_eq(strncat(str, str1, 6), s21_strncat(str, str1, 6));
}
END_TEST

START_TEST(s21_strncat_tests_case_6) {
  char str[30] = "\0Hello\0w2\0ld";
  char str1[] = "\0Hello\0wo\0ld";
  ck_assert_str_eq(strncat(str, str1, 6), s21_strncat(str, str1, 6));
}
END_TEST

START_TEST(s21_strncat_tests_case_7) {
  char str[30] = "\0\0\0";
  char str1[] = "\0\0\0";
  ck_assert_str_eq(strncat(str, str1, 2), s21_strncat(str, str1, 2));
}
END_TEST

START_TEST(s21_strncat_tests_case_8) {
  char str[30] = "\0";
  char str1[] = "\0";
  ck_assert_str_eq(strncat(str, str1, 1), s21_strncat(str, str1, 1));
}
END_TEST

START_TEST(s21_strncat_tests_case_9) {
  char str[30] = "";
  char str1[] = "";
  ck_assert_str_eq(strncat(str, str1, 0), s21_strncat(str, str1, 0));
}
END_TEST

START_TEST(s21_strncat_tests_case_10) {
  char str[30] = "\0";
  char str1[] = " ";
  ck_assert_str_eq(strncat(str, str1, 1), s21_strncat(str, str1, 1));
}
END_TEST

START_TEST(s21_strpbrk_tests_case_1) {
  char *str = "Hello world";
  char *find = "world";
  ck_assert_str_eq(strpbrk(str, find), s21_strpbrk(str, find));
}
END_TEST

START_TEST(s21_strpbrk_tests_case_2) {
  char *str = "Hello world";
  char *find = "H";
  ck_assert_str_eq(strpbrk(str, find), s21_strpbrk(str, find));
}
END_TEST

START_TEST(s21_strpbrk_tests_case_3) {
  char *str = "Hello world";
  char *find = "he";
  ck_assert_str_eq(strpbrk(str, find), s21_strpbrk(str, find));
}
END_TEST

START_TEST(s21_strpbrk_tests_case_4) {
  char *str = "Hello world";
  char *find = "d\n";
  ck_assert_str_eq(strpbrk(str, find), s21_strpbrk(str, find));
}
END_TEST

START_TEST(s21_strpbrk_tests_case_5) {
  char *str = "School21";
  char *find = "21";
  ck_assert_str_eq(strpbrk(str, find), s21_strpbrk(str, find));
}
END_TEST

START_TEST(s21_strrchr_tests_case_1) {
  char *str = "Hello world";
  ck_assert_str_eq(strrchr(str, 'l'), s21_strrchr(str, 'l'));
}
END_TEST

START_TEST(s21_strrchr_tests_case_2) {
  char *str = "Hello world";
  ck_assert_str_eq(strrchr(str, '\0'), s21_strrchr(str, '\0'));
}
END_TEST

START_TEST(s21_strrchr_tests_case_3) {
  char *str = "Hello world";
  ck_assert_str_eq(strrchr(str, 'H'), s21_strrchr(str, 'H'));
}
END_TEST

START_TEST(s21_strrchr_tests_case_4) {
  char *str = "School21";
  ck_assert_str_eq(strrchr(str, '2'), strrchr(str, '2'));
}
END_TEST

START_TEST(s21_strrchr_tests_case_5) {
  char *str = "9990009";
  ck_assert_str_eq(strrchr(str, '9'), s21_strrchr(str, '9'));
}
END_TEST

START_TEST(s21_strcspn_tests_case) {
  char str1[] = "abc.defghij.kl";
  char str2[] = "./i";
  char str3[] = "..abc.defghij.kl  addsa adsasd";
  char str4[] =
      "dajskljasd asd isadlj j dasdouisadousd ioas d,jads lkjaklsdj aei a ";
  char str5[] = ".////iiii/.....////iiiiiid///";
  char str6[] = "";
  ck_assert_int_eq(strcspn(str1, str2), s21_strcspn(str1, str2));
  ck_assert_int_eq(strcspn(str2, str2), s21_strcspn(str2, str2));
  ck_assert_int_eq(strcspn(str3, str2), s21_strcspn(str3, str2));
  ck_assert_int_eq(strcspn(str4, str2), s21_strcspn(str4, str2));
  ck_assert_int_eq(strcspn(str5, str2), s21_strcspn(str5, str2));
  ck_assert_int_eq(strcspn(str1, str6), s21_strcspn(str1, str6));
}
END_TEST

START_TEST(s21_strtok_tests_case) {
  char str5[] = "abc";
  ck_assert_pstr_eq(strtok(S21_NULL, str5), s21_strtok(S21_NULL, str5));

  char str1[] = "abc.defghij.kl.aasdds.aasd";
  char str2[] = ".";
  char str3[] = "abc.defghij.kl.aasdds.aasd";
  ck_assert_str_eq(strtok(str1, str2), s21_strtok(str3, str2));
  ck_assert_str_eq(strtok(S21_NULL, str2), s21_strtok(S21_NULL, str2));
  ck_assert_str_eq(strtok(S21_NULL, str2), s21_strtok(S21_NULL, str2));
  ck_assert_str_eq(strtok(S21_NULL, str2), s21_strtok(S21_NULL, str2));
  ck_assert_str_eq(strtok(S21_NULL, str2), s21_strtok(S21_NULL, str2));
  ck_assert_pstr_eq(strtok(S21_NULL, str2), s21_strtok(S21_NULL, str2));
}
END_TEST

START_TEST(s21_strspn_tests_case) {
  char str1[] = "abc.defghij.kl";
  char str2[] = "./i";
  char str3[] = "..abc.defghij.kl  addsa adsasd";
  char str4[] =
      "dajskljasd asd isadlj j dasdouisadousd ioas d,jads lkjaklsdj aei a ";
  char str5[] = ".////iiii/.....////iiiiiid///";
  char str6[] = "";
  ck_assert_int_eq(strspn(str1, str2), s21_strspn(str1, str2));
  ck_assert_int_eq(strspn(str2, str2), s21_strspn(str2, str2));
  ck_assert_int_eq(strspn(str3, str2), s21_strspn(str3, str2));
  ck_assert_int_eq(strspn(str4, str2), s21_strspn(str4, str2));
  ck_assert_int_eq(strspn(str5, str2), s21_strspn(str5, str2));
  ck_assert_int_eq(strspn(str1, str6), s21_strspn(str1, str6));
}
END_TEST

#if defined(__MAC__) || defined(__APPLE__)
START_TEST(s21_str_strerror_tests_case) {
  if (s21_strcmp(PLATFORM_NAME, "MAC") == 0) {
    for (int i = -10; i < 150; ++i) {
      ck_assert_pstr_eq(s21_strerror(i), strerror(i));
    }
  }
}
END_TEST
#endif

START_TEST(s21_str_to_lower_tests_case) {
  char str1[] = "ONCHLJBaYV";
  char str2[] = "KvCfcdgBBb";
  char str3[] = "czhEwtIGDI";
  char str4[] = "12345678";
  char str5[] = "\0abc";
  void *str;
  str = s21_to_lower(str1);
  ck_assert_pstr_eq(str, "onchljbayv");
  free(str);
  str = s21_to_lower(str2);
  ck_assert_pstr_eq(str, "kvcfcdgbbb");
  free(str);
  str = s21_to_lower(str3);
  ck_assert_pstr_eq(str, "czhewtigdi");
  free(str);
  str = s21_to_lower(str4);
  ck_assert_pstr_eq(str, "12345678");
  free(str);
  str = s21_to_lower(str5);
  ck_assert_pstr_eq(str, "");
  free(str);
}
END_TEST

START_TEST(s21_str_to_upper_tests_case) {
  char str1[] = "ONCHLJBaYV";
  char str2[] = "KvCfcdgBBb";
  char str3[] = "czhEwtIGDI";
  char str4[] = "12345678";
  char str5[] = "\0abc";
  void *str;
  str = s21_to_upper(str1);
  ck_assert_pstr_eq(str, "ONCHLJBAYV");
  free(str);
  str = s21_to_upper(str2);
  ck_assert_pstr_eq(str, "KVCFCDGBBB");
  free(str);
  str = s21_to_upper(str3);
  ck_assert_pstr_eq(str, "CZHEWTIGDI");
  free(str);
  str = s21_to_upper(str4);
  ck_assert_pstr_eq(str, "12345678");
  free(str);
  str = s21_to_upper(str5);
  ck_assert_pstr_eq(str, "");
  free(str);
}
END_TEST

START_TEST(test_simple_int) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "This is a simple value %d";
  int val = 69;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(precise_int) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%.5i";
  int val = 69;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(width_int) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%5d";
  int val = 69;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(minus_width_int) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%-5i";
  int val = 69;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(plus_width_int) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%+12d";
  int val = 69;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(padding_int) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%012i";
  int val = 69;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(star_width_int) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%0*d";
  int val = 69;
  ck_assert_int_eq(s21_sprintf(str1, format, 5, val),
                   sprintf(str2, format, 5, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(star_precision_int) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%0.*i";
  int val = 69;
  ck_assert_int_eq(s21_sprintf(str1, format, 5, val),
                   sprintf(str2, format, 5, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(many_flags_many_ints) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char format[] = "%0.*i %d %4.*i %013d %d";
  int val = 69;
  ck_assert_int_eq(
      s21_sprintf(str1, format, 5, val, -10431, 13, 5311, 0, -581813581),
      sprintf(str2, format, 5, val, -10431, 13, 5311, 0, -581813581));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(flags_long_int) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%+5.31li";
  long int val = 698518581899;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(flags_short_int) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%-16.9hi";
  short int val = 6958;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(flags_another_long_int) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%0.*ld";
  long val = 8581385185;
  ck_assert_int_eq(s21_sprintf(str1, format, 5, val),
                   sprintf(str2, format, 5, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(space_flag_int) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "% d";
  int val = 0;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(unsigned_val) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%u";
  unsigned int val = 14140;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(unsigned_val_width) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%15u";
  unsigned int val = 14140;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(unsigned_val_flags) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%-16u";
  unsigned int val = 14140;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(unsigned_val_precision) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%.51u";
  unsigned int val = 14140;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST
START_TEST(unsigned_val_many_flags) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "% 5.51u";
  unsigned int val = 14140;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST
START_TEST(unsigned_val_short) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%hu";
  unsigned short int val = 14140;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(unsigned_val_long) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%lu";
  unsigned long int val = 949149114140;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(unsigned_val_many) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%lu, %u, %hu, %.5u, %5.u";
  unsigned long int val = 949149114140;
  ck_assert_int_eq(
      s21_sprintf(str1, format, val, 14, 1441, 14414, 9681),
      sprintf(str2, format, val, (unsigned)14, (unsigned short)1441,
              (unsigned)14414, (unsigned)9681));

  ck_assert_str_eq(str1, str2);
}
END_TEST
START_TEST(octal_width) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%15o";
  int val = 14140;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(octal_flags) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%-16o";
  int val = 14140;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(octal_precision) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%.51o";
  int val = 14140;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST
START_TEST(octal_many_flags) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%-5.51o";
  int val = 14140;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(octal_zero) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%o";
  ck_assert_int_eq(s21_sprintf(str1, format, 0), sprintf(str2, format, 0));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(octal_hash) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%#o";
  int val = 57175;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST
START_TEST(octal_short) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%hd";
  short int val = 14140;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(octal_long) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%lo";
  long int val = 949149114140;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(octal_many) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%lo, %o, %ho, %.5o, %5.o";
  long int val = 949149114140;
  ck_assert_int_eq(
      s21_sprintf(str1, format, val, 14, 1441, 14414, 9681),
      sprintf(str2, format, val, (unsigned)14, (unsigned short)1441,
              (unsigned)14414, (unsigned)9681));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(octal) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%lo";
  long int val = 84518;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(unsigned_zero) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%u";
  ck_assert_int_eq(s21_sprintf(str1, format, 0),
                   sprintf(str2, format, (unsigned)0));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(hex_width) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%5x";
  unsigned val = 858158158;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(hex_flags) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%#-10x";
  unsigned val = 858158158;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST
START_TEST(hex_precision) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%.15x";
  unsigned val = 858158158;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST
START_TEST(hex_many) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%#-10x%x%X%#x%#X%5.5x";
  unsigned val = 858158158;
  ck_assert_int_eq(s21_sprintf(str1, format, val, val, val, val, val, val),
                   sprintf(str2, format, val, val, val, val, val, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST
START_TEST(hex_many_flags) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%#-5.10x";
  unsigned val = 858158158;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST
START_TEST(hex_zero) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%#x";
  unsigned val = 0;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST
START_TEST(hex_huge) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%#x";
  unsigned val = 18571;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST
START_TEST(hex_short) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%#hx";
  unsigned short val = 12352;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST
START_TEST(hex_long) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%#lx";
  unsigned long val = 18571757371571;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST
START_TEST(hex_one_longer_width) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%#2x";
  unsigned val = 1;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(hex_two_longer_width) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%#30x";
  unsigned val = 1;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(one_char) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%c";
  char val = 'X';
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST
START_TEST(one_precision) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%.5c";
  char val = 'c';
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(one_width) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%15c";
  char val = 'c';
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(one_many) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%-5.3c%c%c%c%c Hello! ABOBA";
  char val = 'c';
  ck_assert_int_eq(s21_sprintf(str1, format, val, 'c', 'a', 'b', 'b'),
                   sprintf(str2, format, val, 'c', 'a', 'b', 'b'));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(string) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%s";
  char *val = "I LOVE STRINGS AND TESTS AND SCHOOL21 NO JOKE";
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST
START_TEST(string_precision) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%.15s";
  char *val = "I LOVE STRINGS AND TESTS AND SCHOOL21 NO JOKE";
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST
START_TEST(string_width) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%15s";
  char *val = "69 IS MY FAVORITE NUMBER";
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST
START_TEST(string_flags) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%-15.9s";
  char *val = "69 IS MY FAVORITE NUMBER";
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(string_long) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%s";
  char *val =
      "69 IS MY FAVORITE NUMBER THIS IS SUPPOSED TO BE A VERY LONG STRING";
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(string_many) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%s%s%s%s";
  char *val =
      "69 IS MY FAVORITE NUMBER THIS IS SUPPOSED TO BE A VERY LONG STRING";
  char *s1 = "";
  char *s2 = "87418347813748913749871389480913";
  char *s3 = "HAHAABOBASUCKER";
  ck_assert_int_eq(s21_sprintf(str1, format, val, s1, s2, s3),
                   sprintf(str2, format, val, s1, s2, s3));

  ck_assert_str_eq(str1, str2);
}
END_TEST
START_TEST(ptr) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%p";
  ck_assert_int_eq(s21_sprintf(str1, format, format),
                   sprintf(str2, format, format));

  ck_assert_str_eq(str1, str2);
}
END_TEST
START_TEST(ptr_width) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%15p";
  ck_assert_int_eq(s21_sprintf(str1, format, format),
                   sprintf(str2, format, format));

  ck_assert_str_eq(str1, str2);
}
END_TEST
START_TEST(ptr_precision) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%.5p";
  ck_assert_int_eq(s21_sprintf(str1, format, format),
                   sprintf(str2, format, format));

  ck_assert_str_eq(str1, str2);
}
END_TEST
START_TEST(null_ptr) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%p";
  char *ptr = NULL;
  ck_assert_int_eq(s21_sprintf(str1, format, ptr), sprintf(str2, format, ptr));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(string_width_huge) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *val = "kjafdiuhfjahfjdahf";
  char *format = "%120s";
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST
START_TEST(n_specifier) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  int ret = 0;
  char *format = "Hello, my sexy little aboba abobushka abobina %n";
  ck_assert_int_eq(s21_sprintf(str1, format, &ret),
                   sprintf(str2, format, &ret));

  ck_assert_str_eq(str1, str2);
}
END_TEST
START_TEST(float_precision) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%Lf";
  long double val = 513515.131513515151351;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST
START_TEST(float_width) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%10Lf";
  long double val = 15.35;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST
START_TEST(float_precision_zero) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%.0Lf";
  long double val = 15.35;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(float_precision_empty) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%.Lf";
  long double val = 15.35;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST
START_TEST(float_precision_huge) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%.15Lf";
  long double val = 15.35;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(float_precision_huge_negative) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%.15Lf";
  long double val = -15.35581134;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(float_huge) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%Lf";
  long double val = 72537572375.1431341;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST
START_TEST(float_flags) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "% f";
  float val = 0;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST
START_TEST(float_many) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "% .0f %.lf %Lf %f %lf %Lf";
  float val = 0;
  double val1 = 0;
  long double val2 = 3515315.153151;
  float val3 = 5.5;
  double val4 = 9851.51351;
  long double val5 = 95919539159.53151351131;
  ck_assert_int_eq(s21_sprintf(str1, format, val, val1, val2, val3, val4, val5),
                   sprintf(str2, format, val, val1, val2, val3, val4, val5));

  ck_assert_str_eq(str1, str2);
}
END_TEST
// START_TEST(e_precision) {
//   char str1[BUFF_SIZE];
//   char str2[BUFF_SIZE];
//   char *format = "%.17Le";
//   long double val = 15.35;
//   ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format,
//   val));

//   ck_assert_str_eq(str1, str2);
// }
// END_TEST
START_TEST(e_precision_zero) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%.0Le";
  long double val = 15.35;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(e_precision_empty) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%.Le";
  long double val = 15.000009121;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST
START_TEST(e_precision_huge) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%.15Le";
  long double val = 0.000000000000000123;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(e_precision_huge_negative) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%.15Le";
  long double val = -15.35581134;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(e_huge) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%Le";
  long double val = 72537572375.1431341;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST
START_TEST(e_flags) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%015E";
  float val = 0;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST
START_TEST(e_width) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%15e";
  float val = 0;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST
START_TEST(e_many) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "% .0e %.le %Le %e %le %Le";
  float val = 0;
  double val1 = 0;
  long double val2 = 3515315.153151;
  float val3 = 5.5;
  double val4 = 0.094913941;
  long double val5 = 95919539159.53151351131;
  ck_assert_int_eq(s21_sprintf(str1, format, val, val1, val2, val3, val4, val5),
                   sprintf(str2, format, val, val1, val2, val3, val4, val5));

  ck_assert_str_eq(str1, str2);
}
END_TEST
START_TEST(E_int) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%.17LE";
  long double val = 4134121;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST
START_TEST(all_empty) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  ck_assert_int_eq(s21_sprintf(str1, "abc"), sprintf(str2, "abc"));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(empty_format_and_parameters) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(s21_sprintf(str1, "abc"), sprintf(str2, "abc"));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_one_char) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(s21_sprintf(str1, "%c", '\t'), sprintf(str2, "%c", '\t'));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_many_char) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(s21_sprintf(str1, "%c%c%c%c%c", '\t', '\n', '0', 'S', 's'),
                   sprintf(str2, "%c%c%c%c%c", '\t', '\n', '0', 'S', 's'));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_one_string) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(s21_sprintf(str1, "%s", "Drop Sega PLS"),
                   sprintf(str2, "%s", "Drop Sega PLS"));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_many_string) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(
      s21_sprintf(str1, "%s%s%s%s%s", "Drop", " ", "Sega", " ", "PLS"),
      sprintf(str2, "%s%s%s%s%s", "Drop", " ", "Sega", " ", "PLS"));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_one_dec) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(s21_sprintf(str1, "%d", 666), sprintf(str2, "%d", 666));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_many_dec) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(s21_sprintf(str1, "%d%d%d%d", -999, 0, 666, -100),
                   sprintf(str2, "%d%d%d%d", -999, 0, 666, -100));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_one_int) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(s21_sprintf(str1, "%i", -0), sprintf(str2, "%i", -0));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_many_int) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(s21_sprintf(str1, "%i%i%i%i", -999, 0, 666, -100),
                   sprintf(str2, "%i%i%i%i", -999, 0, 666, -100));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_one_float) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(s21_sprintf(str1, "%f", 0.0001),
                   sprintf(str2, "%f", 0.0001));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_many_float) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(
      s21_sprintf(str1, "%f%f%f%f", -999.666, 0.0001, 666.999, -100.001),
      sprintf(str2, "%f%f%f%f", -999.666, 0.0001, 666.999, -100.001));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_one_unsigned_dec) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(s21_sprintf(str1, "%u", 100),
                   sprintf(str2, "%u", (unsigned)100));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_many_unsigned_dec) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(s21_sprintf(str1, "%u%u%u%u", 999, 0, 666, 100),
                   sprintf(str2, "%u%u%u%u", (unsigned)999, (unsigned)0,
                           (unsigned)666, (unsigned)100));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_one_char_with_alignment_left) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(s21_sprintf(str1, "%8c", '\t'), sprintf(str2, "%8c", '\t'));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_one_char_with_alignment_right) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(s21_sprintf(str1, "%-8c", '\t'),
                   sprintf(str2, "%-8c", '\t'));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_many_char_with_alignment) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(
      s21_sprintf(str1, "%3c%-11c%10c%-2c%c", '\t', '\n', '0', 'S', 's'),
      sprintf(str2, "%3c%-11c%10c%-2c%c", '\t', '\n', '0', 'S', 's'));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_one_hex_lower) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  ck_assert_int_eq(s21_sprintf(str1, "%x", (unsigned)INT32_MIN),
                   sprintf(str2, "%x", (unsigned)INT32_MIN));
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(s21_sprintf(str1, "%x", 0), sprintf(str2, "%x", 0));
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(s21_sprintf(str1, "%x", INT32_MAX),
                   sprintf(str2, "%x", INT32_MAX));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_one_hex_upper) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(s21_sprintf(str1, "%X", (unsigned)INT32_MIN),
                   sprintf(str2, "%X", (unsigned)INT32_MIN));
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(s21_sprintf(str1, "%X", 0), sprintf(str2, "%x", 0));
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(s21_sprintf(str1, "%X", INT32_MAX),
                   sprintf(str2, "%X", INT32_MAX));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_many_hex_lower) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(
      s21_sprintf(str1, "%x%x%x%x%x", 12340987, 135, 0, -1230, -123213123),
      sprintf(str2, "%x%x%x%x%x", 12340987, 135, 0, -1230, -123213123));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_many_hex_upper) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(
      s21_sprintf(str1, "%X%X%X%X%X", 12340987, 135, 0, -1230, -123213123),
      sprintf(str2, "%X%X%X%X%X", 12340987, 135, 0, -1230, -123213123));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_one_hex_lower_with_alignment_left) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(s21_sprintf(str1, "%-3x", (unsigned)INT32_MIN),
                   sprintf(str2, "%-3x", (unsigned)INT32_MIN));
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(s21_sprintf(str1, "%-3x", 0), sprintf(str2, "%-3x", 0));
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(s21_sprintf(str1, "%-3x", INT32_MAX),
                   sprintf(str2, "%-3x", INT32_MAX));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_one_hex_lower_with_alignment_right) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(s21_sprintf(str1, "%13x", (unsigned)INT32_MIN),
                   sprintf(str2, "%13x", (unsigned)INT32_MIN));
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(s21_sprintf(str1, "%13x", 0), sprintf(str2, "%13x", 0));
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(s21_sprintf(str1, "%13x", INT32_MAX),
                   sprintf(str2, "%13x", INT32_MAX));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_one_hex_upper_with_alignment_left) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(s21_sprintf(str1, "%-60X", INT32_MIN),
                   sprintf(str2, "%-60X", (unsigned)INT32_MIN));
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(s21_sprintf(str1, "%-60X", 0), sprintf(str2, "%-60X", 0));
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(s21_sprintf(str1, "%-60X", INT32_MAX),
                   sprintf(str2, "%-60X", INT32_MAX));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_one_hex_upper_with_alignment_right) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(s21_sprintf(str1, "%7X", (unsigned)INT32_MIN),
                   sprintf(str2, "%7X", (unsigned)INT32_MIN));
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(s21_sprintf(str1, "%7X", 0), sprintf(str2, "%7X", 0));
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(s21_sprintf(str1, "%7X", INT32_MAX),
                   sprintf(str2, "%7X", INT32_MAX));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_many_hex_lower_with_alignment) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(
      s21_sprintf(str1, "%2x%-7x%9x%11x%0x", 12340987, 100, 0, 1, -666999),
      sprintf(str2, "%2x%-7x%9x%11x%0x", 12340987, 100, 0, 1, -666999));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_many_hex_upper_with_alignment) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  ck_assert_int_eq(
      s21_sprintf(str1, "%2X%-7X%9X%11X%0X", 12340987, 100, 0, 1, -666999),
      sprintf(str2, "%2X%-7X%9X%11X%0X", 12340987, 100, 0, 1, -666999));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_one_hex_with_hashtag) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(s21_sprintf(str1, "%#x", INT32_MIN),
                   sprintf(str2, "%#x", (unsigned)INT32_MIN));
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(s21_sprintf(str1, "%#x", 0), sprintf(str2, "%#x", 0));
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(s21_sprintf(str1, "%#x", INT32_MAX),
                   sprintf(str2, "%#x", INT32_MAX));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_one_hex_upper_with_hashtag) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(s21_sprintf(str1, "%#X", INT32_MIN),
                   sprintf(str2, "%#X", (unsigned)INT32_MIN));
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(s21_sprintf(str1, "%#X", 0), sprintf(str2, "%#X", 0));
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(s21_sprintf(str1, "%#X", INT32_MAX),
                   sprintf(str2, "%#X", INT32_MAX));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_many_hex_lower_with_hashtag_and_alignm) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(
      s21_sprintf(str1, "%#x%#x%3x%#32x%#-1x", 87, 1222224535, -13, -0,
                  123213123),
      sprintf(str2, "%#x%#x%3x%#32x%#-1x", 87, 1222224535, -13, -0, 123213123));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_many_hex_upper_with_hashtag_and_alignm) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(
      s21_sprintf(str1, "%#X%#X%3X%#32X%#-1X", 87, 1222224535, -13, -0,
                  123213123),
      sprintf(str2, "%#X%#X%3X%#32X%#-1X", 87, 1222224535, -13, -0, 123213123));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_one_hex_lower_with_width_star) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(s21_sprintf(str1, "%*x", 11, INT32_MIN),
                   sprintf(str2, "%*x", 11, (unsigned)INT32_MIN));
  ck_assert_str_eq(str1, str2);

  ck_assert_int_eq(s21_sprintf(str1, "%*x", 11, 0),
                   sprintf(str2, "%*x", 11, 0));
  ck_assert_str_eq(str1, str2);

  ck_assert_int_eq(s21_sprintf(str1, "%*x", 11, INT32_MAX),
                   sprintf(str2, "%*x", 11, INT32_MAX));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_one_hex_upper_with_width_star) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(s21_sprintf(str1, "%*X", 11, INT32_MIN),
                   sprintf(str2, "%*X", 11, (unsigned)INT32_MIN));
  ck_assert_str_eq(str1, str2);

  ck_assert_int_eq(s21_sprintf(str1, "%*X", 11, 0),
                   sprintf(str2, "%*X", 11, 0));
  ck_assert_str_eq(str1, str2);

  ck_assert_int_eq(s21_sprintf(str1, "%*X", 11, INT32_MAX),
                   sprintf(str2, "%*X", 11, INT32_MAX));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_many_hex_lower_with_width_star_and_align_and_hashtag) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(s21_sprintf(str1, "%#*x%*x%-12x%3x%*x", 9, 127312897, 0, -1,
                               199, -123978, 3, -1251),
                   sprintf(str2, "%#*x%*x%-12x%3x%*x", 9, 127312897, -0, -1,
                           199, -123978, 3, -1251));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_many_hex_upper_with_width_star) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(s21_sprintf(str1, "%#*X%*X%-12X%3X%*X", 9, 127312897, 0, -1,
                               199, -123978, 3, -1251),
                   sprintf(str2, "%#*X%*X%-12X%3X%*X", 9, 127312897, 0, -1, 199,
                           -123978, 3, -1251));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_one_hex_lower_with_precision) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  int a = s21_sprintf(str1, "%*.6x", 11, 0);
  int b = sprintf(str2, "%*.6x", 11, 0);
  ck_assert_int_eq(a, b);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_one_hex_upper_with_precision) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  int a = s21_sprintf(str1, "%*.6X", 11, INT32_MIN);
  int b = sprintf(str2, "%*.6X", 11, (unsigned)INT32_MIN);
  ck_assert_int_eq(a, b);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_many_hex_lower_with_precision_and_other) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  int a = s21_sprintf(
      str1, "%#3.*x%#3x%-7.*x%#-1.8x%4.3x%#2.15x%*.*x%*.1x%3x%-1x", 3, 126714,
      4444444, 0, 6423235, 0, 666, 999, 13, 5, 419, 9, 41, -41, 33);
  int b = sprintf(str2, "%#3.*x%#3x%-7.*x%#-1.8x%4.3x%#2.15x%*.*x%*.1x%3x%-1x",
                  3, 126714, 4444444, 0, 6423235, 0, 666, 999, 13, 5, 419, 9,
                  41, -41, 33);
  ck_assert_int_eq(a, b);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_many_hex_upper_with_precision_and_other) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(
      s21_sprintf(str1, "%#3.*X%#3x%-7.*X%#-1.8X%4.3X%#2.15x%*.*X%*.1X%3X%-1X",
                  3, -126714, 4444444, 0, 6423235, 0, 666, 999, 13, 5, -419, 9,
                  41, -41, 33),
      sprintf(str2, "%#3.*X%#3x%-7.*X%#-1.8X%4.3X%#2.15x%*.*X%*.1X%3X%-1X", 3,
              -126714, 4444444, 0, 6423235, 0, 666, 999, 13, 5, -419, 9, 41,
              -41, 33));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_one_hex_lower_with_length) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(s21_sprintf(str1, "%hx", -11),
                   sprintf(str2, "%hx", (unsigned short)-11));
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(s21_sprintf(str1, "%hx", 0),
                   sprintf(str2, "%hx", (unsigned short)0));
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(s21_sprintf(str1, "%hx", 11),
                   sprintf(str2, "%hx", (unsigned short)11));
  ck_assert_str_eq(str1, str2);
  long unsigned int val = INT32_MAX;
  ck_assert_int_eq(s21_sprintf(str1, "%lx", val), sprintf(str2, "%lx", val));
  ck_assert_str_eq(str1, str2);
  long unsigned int v = 0;
  ck_assert_int_eq(s21_sprintf(str1, "%lx", v), sprintf(str2, "%lx", v));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_one_hex_upper_with_length) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(s21_sprintf(str1, "%hx", -11),
                   sprintf(str2, "%hx", (unsigned short)-11));
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(s21_sprintf(str1, "%hx", 0),
                   sprintf(str2, "%hx", (unsigned short)0));
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(s21_sprintf(str1, "%hx", 11),
                   sprintf(str2, "%hx", (unsigned short)11));
  ck_assert_str_eq(str1, str2);
  long unsigned int val = INT32_MAX;
  ck_assert_int_eq(s21_sprintf(str1, "%lx", val), sprintf(str2, "%lx", val));
  ck_assert_str_eq(str1, str2);
  long unsigned int v = 0;
  ck_assert_int_eq(s21_sprintf(str1, "%lx", v), sprintf(str2, "%lx", v));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf1) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%10ld";

  ck_assert_int_eq(s21_sprintf(str1, format, 1), sprintf(str2, format, 1));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf2) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%1.1f";

  ck_assert_int_eq(s21_sprintf(str1, format, 1.1), sprintf(str2, format, 1.1));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf3) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%8.3c";

  ck_assert_int_eq(s21_sprintf(str1, format, 'a'), sprintf(str2, format, 'a'));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf4) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%+5.5d aboba";

  int val = 10000;
  int a = s21_sprintf(str1, format, val);
  int b = sprintf(str2, format, val);
  ck_assert_int_eq(a, b);

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf6) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%7.7f";

  ck_assert_int_eq(s21_sprintf(str1, format, 11.123456),
                   sprintf(str2, format, 11.123456));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf7) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%7.4s";

  ck_assert_int_eq(s21_sprintf(str1, format, "aboba floppa"),
                   sprintf(str2, format, "aboba floppa"));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf8) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%6.6u";

  ck_assert_int_eq(s21_sprintf(str1, format, 12341151),
                   sprintf(str2, format, 12341151));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf9) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%li%ld%lu";

  ck_assert_int_eq(s21_sprintf(str1, format, 666666666666, 777, 111),
                   sprintf(str2, format, 666666666666, 777, 111));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf10) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%hi%hd%hu";

  ck_assert_int_eq(s21_sprintf(str1, format, 666, -777, 111),
                   sprintf(str2, format, 666, -777, 111));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf11) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%+li%+lu%+d%+lf";

  ck_assert_int_eq(s21_sprintf(str1, format, -123, 321, -5555, -1213.123),
                   sprintf(str2, format, -123, 321, -5555, -1213.123));

  ck_assert_str_eq(str1, str2);
}
END_TEST

// START_TEST(test_sprintf12) {
//   char str1[BUFF_SIZE];
//   char str2[BUFF_SIZE];
//   char format[] = "%-11.11li%-35.5lu%-3.5ld%33.19Lf";
//   long double k = 333.33213;

//   ck_assert_int_eq(
//       s21_sprintf(str1, format, 66666666666, 5555555555, 44444444444, k),
//       sprintf(str2, format, 66666666666, 5555555555, 44444444444, k));

//   ck_assert_str_eq(str1, str2);
// }
// END_TEST

START_TEST(test_sprintf14) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "% 0.0li% 0.0lu% 0.0ld % 0.0lf";

  ck_assert_int_eq(s21_sprintf(str1, format, 1, 222, 33333333333, -166513.1232),
                   sprintf(str2, format, 1, 222, 33333333333, -166513.1232));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf15) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "% 0.0hi% 0.0hu% 0.0hd % 0.0hf";

  ck_assert_int_eq(s21_sprintf(str1, format, 1, 222, 33333333333, -166513.1232),
                   sprintf(str2, format, 1, 222, 33333333333, -166513.1232));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf16) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "% c";

  ck_assert_int_eq(s21_sprintf(str1, format, 'a'), sprintf(str2, format, 'a'));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf17) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "% s";

  ck_assert_int_eq(s21_sprintf(str1, format, "aboba likes floppa"),
                   sprintf(str2, format, "aboba likes floppa"));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf18) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "% s% c";

  ck_assert_int_eq(s21_sprintf(str1, format, "", 'f'),
                   sprintf(str2, format, "", 'f'));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf19) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%210s";

  ck_assert_int_eq(s21_sprintf(str1, format, "AHHAHAHA\0AHHAHAHAH"),
                   sprintf(str2, format, "AHHAHAHA\0AHHAHAHAH"));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf20) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%-115s";

  ck_assert_int_eq(s21_sprintf(str1, format, "Nick her"),
                   sprintf(str2, format, "Nick her"));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf24) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%+2.1c%+4.2d%+5.4i%+10.2f%+55.55s%+1.1u";

  ck_assert_int_eq(
      s21_sprintf(str1, format, 'f', 21, 42, 666.666,
                  "Lorem ipsum dolor sit amet. Aut quam ducimus.", 11),
      sprintf(str2, format, 'f', 21, 42, 666.666,
              "Lorem ipsum dolor sit amet. Aut quam ducimus.", 11));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf25) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%.f";

  ck_assert_int_eq(s21_sprintf(str1, format, 121.123),
                   sprintf(str2, format, 121.123));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf26) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%%";
  char c = 'a';

  ck_assert_int_eq(s21_sprintf(str1, format, c), sprintf(str2, format, c));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf27) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%%%%%%%%";
  char c = 'a';

  ck_assert_int_eq(s21_sprintf(str1, format, c), sprintf(str2, format, c));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf28) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  int n1;
  int n2;
  int a = s21_sprintf(str1, "%d%n", 123, &n1);
  int b = sprintf(str2, "%d%n", 123, &n2);

  ck_assert_int_eq(a, b);
  ck_assert_int_eq(n1, n2);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf29) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%-.f";

  ck_assert_int_eq(s21_sprintf(str1, format, 111.111),
                   sprintf(str2, format, 111.111));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf30) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%-.1d";

  ck_assert_int_eq(s21_sprintf(str1, format, 111), sprintf(str2, format, 111));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf31) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%e";
  double x = 111;
  ck_assert_int_eq(s21_sprintf(str1, format, x), sprintf(str2, format, x));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf32) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%e%e%e%e";

  ck_assert_int_eq(s21_sprintf(str1, format, 11.111, 222.2222, 666., -555.125),
                   sprintf(str2, format, 11.111, 222.2222, 666., -555.125));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf33) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%Le";
  long double x = 122.1231;

  ck_assert_int_eq(s21_sprintf(str1, format, x), sprintf(str2, format, x));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf35) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%.10e";

  ck_assert_int_eq(s21_sprintf(str1, format, 111.184314818),
                   sprintf(str2, format, 111.184314818));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf36) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%5.3e%3.2e%lf";

  ck_assert_int_eq(s21_sprintf(str1, format, 0.000111, 111.555, 1.999),
                   sprintf(str2, format, 0.000111, 111.555, 1.999));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf37) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%E";

  ck_assert_int_eq(s21_sprintf(str1, format, 0.666666),
                   sprintf(str2, format, 0.666666));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf38) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%E%E%E";

  ck_assert_int_eq(s21_sprintf(str1, format, 0.0000999, 111.9999, 6.666),
                   sprintf(str2, format, 0.0000999, 111.9999, 6.666));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf39) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%e ABOBA %Lf %Lf %Le";
  long double c = 848181;
  long double a = 0.00000001;
  long double b = 1111111.11;
  ck_assert_int_eq(s21_sprintf(str1, format, 123.123, a, b, c),
                   sprintf(str2, format, 123.123, a, b, c));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf40) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%#e Floppa %#E%#f";

  ck_assert_int_eq(s21_sprintf(str1, format, 123.111, 0.0000999, 0.555),
                   sprintf(str2, format, 123.111, 0.0000999, 0.555));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf41) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%.Lf";
  long double a = 7.9418438184;

  ck_assert_int_eq(s21_sprintf(str1, format, a), sprintf(str2, format, a));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf42) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%#5p";
  int a = 5;
  ck_assert_int_eq(s21_sprintf(str1, format, &a), sprintf(str2, format, &a));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf43) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%.5o";

  ck_assert_int_eq(s21_sprintf(str1, format, 12345),
                   sprintf(str2, format, 12345));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf44) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%#5lX";
  long hex = 314818438141;
  ck_assert_int_eq(s21_sprintf(str1, format, hex), sprintf(str2, format, hex));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(g_trailing_zero) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%g";
  double hex = 0.50300;
  ck_assert_int_eq(s21_sprintf(str1, format, hex), sprintf(str2, format, hex));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(g_large) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%g";
  double hex = 5131.43141;
  ck_assert_int_eq(s21_sprintf(str1, format, hex), sprintf(str2, format, hex));

  ck_assert_str_eq(str1, str2);
}
END_TEST
START_TEST(g_small) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%g";
  double hex = 0.123000;
  ck_assert_int_eq(s21_sprintf(str1, format, hex), sprintf(str2, format, hex));

  ck_assert_str_eq(str1, str2);
}
END_TEST
START_TEST(g_precision) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%.5g";
  double hex = 0.123000;
  ck_assert_int_eq(s21_sprintf(str1, format, hex), sprintf(str2, format, hex));

  ck_assert_str_eq(str1, str2);
}
END_TEST
START_TEST(g_precision_zero) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%.0g";
  double hex = 0.123000;
  ck_assert_int_eq(s21_sprintf(str1, format, hex), sprintf(str2, format, hex));

  ck_assert_str_eq(str1, str2);
}
END_TEST
START_TEST(g_precision_missing) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%.g";
  double hex = 0.123000;
  ck_assert_int_eq(s21_sprintf(str1, format, hex), sprintf(str2, format, hex));

  ck_assert_str_eq(str1, str2);
}
END_TEST
START_TEST(g_many_zeroes_in_front) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%.g";
  double hex = 0.0004;
  ck_assert_int_eq(s21_sprintf(str1, format, hex), sprintf(str2, format, hex));

  ck_assert_str_eq(str1, str2);
}
END_TEST
START_TEST(g_one_zero) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%g";
  double hex = 0;
  ck_assert_int_eq(s21_sprintf(str1, format, hex), sprintf(str2, format, hex));

  ck_assert_str_eq(str1, str2);
}
END_TEST
START_TEST(g_zero) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%.5g";
  double hex = 0;
  ck_assert_int_eq(s21_sprintf(str1, format, hex), sprintf(str2, format, hex));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(g_mantiss) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%g";
  double hex = 0.0000005;
  ck_assert_int_eq(s21_sprintf(str1, format, hex), sprintf(str2, format, hex));

  ck_assert_str_eq(str1, str2);
}
END_TEST
START_TEST(g_mantiss_flags) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%5.8g";
  double hex = 0.0000005;
  ck_assert_int_eq(s21_sprintf(str1, format, hex), sprintf(str2, format, hex));

  ck_assert_str_eq(str1, str2);
}
END_TEST
START_TEST(g_short_no_mantiss) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%g";
  double hex = 0.005;
  ck_assert_int_eq(s21_sprintf(str1, format, hex), sprintf(str2, format, hex));

  ck_assert_str_eq(str1, str2);
}
END_TEST
START_TEST(LG) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%LG";
  long double hex = 0.000005;
  ck_assert_int_eq(s21_sprintf(str1, format, hex), sprintf(str2, format, hex));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(g_many) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%LG %g %G %Lg %.5g";
  long double hex = 0.000005;
  double hex1 = 41.1341;
  double hex2 = 848.9000;
  long double hex3 = 0.0843;
  double hex4 = 0.0005;
  double hex5 = 0.8481481;
  ck_assert_int_eq(s21_sprintf(str1, format, hex, hex1, hex2, hex3, hex4, hex5),
                   sprintf(str2, format, hex, hex1, hex2, hex3, hex4, hex5));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(width_char) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "This is a simple wide char %5c";
  char w = 'c';
  int a = s21_sprintf(str1, format, w);
  int b = sprintf(str2, format, w);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(s21_trim_1) {
  char s1[30] = "-?hello, world!";
  char s3[] = "!?-";
  char s4[] = "hello, world";
  char *s2 = s21_trim(s1, s3);
  ck_assert_pstr_eq(s4, s2);
  if (s2) free(s2);
}
END_TEST

START_TEST(s21_trim_2) {
  char s1[30] = "\n \t    ololo";
  char s3[] = " \n\t";
  char *s4 = "ololo";
  char *s2 = s21_trim(s1, s3);
  ck_assert_pstr_eq(s4, s2);
  if (s2) free(s2);
}
END_TEST

START_TEST(s21_trim_3) {
  char *s1 = S21_NULL;
  char s3[] = "";
  char *s4 = S21_NULL;
  char *s2 = s21_trim(s1, s3);
  ck_assert_pstr_eq(s4, s2);
  if (s2) free(s2);
}
END_TEST

START_TEST(s21_trim_4) {
  char s1[30] = "!!!abcdefghij!?!";
  char s3[] = "!?";
  char s4[] = "abcdefghij";
  char *s2 = s21_trim(s1, s3);
  ck_assert_pstr_eq(s4, s2);
  if (s2) free(s2);
}
END_TEST

START_TEST(s21_trim_5) {
  char s1[30] = "abc";
  char s3[] = "333";
  char *s4 = "abc";
  char *s2 = s21_trim(s1, s3);
  ck_assert_pstr_eq(s4, s2);
  if (s2) free(s2);
}
END_TEST

START_TEST(s21_trim_6) {
  char s1[30] = "hello, world!";
  char s3[] = "?!";
  char *s4 = "hello, world";
  char *s2 = s21_trim(s1, s3);
  ck_assert_pstr_eq(s4, s2);
  if (s2) free(s2);
}
END_TEST

START_TEST(s21_trim_7) {
  char *s1 = S21_NULL;
  char *s3 = S21_NULL;
  char *s4 = S21_NULL;
  char *s2 = s21_trim(s1, s3);
  ck_assert_pstr_eq(s4, s2);
  if (s2) free(s2);
}
END_TEST

START_TEST(s21_trim_8) {
  char s1[30] = "";
  char s3[] = "";
  char s4[] = "";
  char *s2 = s21_trim(s1, s3);
  ck_assert_pstr_eq(s4, s2);
  if (s2) free(s2);
}
END_TEST

START_TEST(s21_insert_1) {
  char s1[30] = "hello, world!";
  char s3[] = "hELLO, WORLD!";
  char s4[] = "hello, hELLO, WORLD!world!";
  s21_size_t num = 7;
  char *s2 = s21_insert(s1, s3, num);
  ck_assert_pstr_eq(s4, s2);
  if (s2) free(s2);
}
END_TEST

START_TEST(s21_insert_2) {
  char s1[30] = "";
  char s3[] = "";
  char *s4 = S21_NULL;
  s21_size_t num = 7;
  char *s2 = s21_insert(s1, s3, num);
  ck_assert_pstr_eq(s4, s2);
  if (s2) free(s2);
}
END_TEST

START_TEST(s21_insert_3) {
  char s1[30] = "abcdefghij";
  char s3[] = "\'I WAS HERE\'";
  char s4[] = "abc\'I WAS HERE\'defghij";
  s21_size_t num = 3;
  char *s2 = s21_insert(s1, s3, num);
  ck_assert_pstr_eq(s4, s2);
  if (s2) free(s2);
}
END_TEST

START_TEST(s21_insert_4) {
  char s1[30] = "abc";
  char s3[] = "333";
  char *s4 = S21_NULL;
  s21_size_t num = 10;
  char *s2 = s21_insert(s1, s3, num);
  ck_assert_pstr_eq(s4, s2);
  if (s2) free(s2);
}
END_TEST

START_TEST(s21_insert_5) {
  char s1[30] = "hello, world!";
  char s3[] = "hELLO, WORLD!";
  char *s4 = S21_NULL;
  s21_size_t num = -1;
  char *s2 = s21_insert(s1, s3, num);
  ck_assert_pstr_eq(s4, s2);
  if (s2) free(s2);
}
END_TEST

START_TEST(s21_insert_6) {
  char s1[30] = "";
  char s3[] = "";
  char s4[] = "";
  s21_size_t num = 0;
  char *s2 = s21_insert(s1, s3, num);
  ck_assert_pstr_eq(s4, s2);
  if (s2) free(s2);
}
END_TEST

int main() {
  Suite *s1 = suite_create("Core");
  TCase *tc1_1 = tcase_create("Core");
  SRunner *sr = srunner_create(s1);
  int nf;

  suite_add_tcase(s1, tc1_1);
  tcase_add_test(tc1_1, s21_memchr_tests_case);
  tcase_add_test(tc1_1, s21_memcmp_tests_case);
  tcase_add_test(tc1_1, s21_memcpy_tests_case);
  tcase_add_test(tc1_1, s21_memmove_tests_case_1);
  tcase_add_test(tc1_1, s21_memmove_tests_case_2);
  tcase_add_test(tc1_1, s21_memmove_tests_case_3);
  tcase_add_test(tc1_1, s21_memmove_tests_case_4);
  tcase_add_test(tc1_1, s21_memmove_S21_NULLdest_tests);
  tcase_add_test(tc1_1, s21_memmove_S21_NULLsrc_tests);
  tcase_add_test(tc1_1, s21_memmove_dest_lower_src_tests);

  tcase_add_test(tc1_1, s21_memset_tests_case);
  tcase_add_test(tc1_1, s21_strchr_tests_case);

  tcase_add_test(tc1_1, s21_strlen_tests_case);
  tcase_add_test(tc1_1, s21_strcpy_tests_case);
  tcase_add_test(tc1_1, s21_strncpy_tests_case);
  tcase_add_test(tc1_1, s21_strcmp_tests_case);

  tcase_add_test(tc1_1, s21_strncmp_tests_case_1);

  tcase_add_test(tc1_1, s21_strstr_tests_case);
  tcase_add_test(tc1_1, s21_strcat_tests_case_1);
  tcase_add_test(tc1_1, s21_strcat_tests_case_2);
  tcase_add_test(tc1_1, s21_strcat_tests_case_3);
  tcase_add_test(tc1_1, s21_strcat_tests_case_4);
  tcase_add_test(tc1_1, s21_strcat_tests_case_5);
  tcase_add_test(tc1_1, s21_strcat_tests_case_6);
  tcase_add_test(tc1_1, s21_strcat_tests_case_7);
  tcase_add_test(tc1_1, s21_strcat_tests_case_8);
  tcase_add_test(tc1_1, s21_strcat_tests_case_9);
  tcase_add_test(tc1_1, s21_strcat_tests_case_10);
  tcase_add_test(tc1_1, s21_strncat_tests_case_1);
  tcase_add_test(tc1_1, s21_strncat_tests_case_2);
  tcase_add_test(tc1_1, s21_strncat_tests_case_3);
  tcase_add_test(tc1_1, s21_strncat_tests_case_4);
  tcase_add_test(tc1_1, s21_strncat_tests_case_5);
  tcase_add_test(tc1_1, s21_strncat_tests_case_6);
  tcase_add_test(tc1_1, s21_strncat_tests_case_7);
  tcase_add_test(tc1_1, s21_strncat_tests_case_8);
  tcase_add_test(tc1_1, s21_strncat_tests_case_9);
  tcase_add_test(tc1_1, s21_strncat_tests_case_10);
  tcase_add_test(tc1_1, s21_strpbrk_tests_case_1);
  tcase_add_test(tc1_1, s21_strpbrk_tests_case_2);
  tcase_add_test(tc1_1, s21_strpbrk_tests_case_3);
  tcase_add_test(tc1_1, s21_strpbrk_tests_case_4);
  tcase_add_test(tc1_1, s21_strpbrk_tests_case_5);
  tcase_add_test(tc1_1, s21_strrchr_tests_case_1);
  tcase_add_test(tc1_1, s21_strrchr_tests_case_2);
  tcase_add_test(tc1_1, s21_strrchr_tests_case_3);
  tcase_add_test(tc1_1, s21_strrchr_tests_case_4);
  tcase_add_test(tc1_1, s21_strrchr_tests_case_5);
  tcase_add_test(tc1_1, s21_strcspn_tests_case);
  tcase_add_test(tc1_1, s21_strtok_tests_case);
  tcase_add_test(tc1_1, s21_strspn_tests_case);
#ifndef __linux__
  tcase_add_test(tc1_1, s21_str_strerror_tests_case);
#endif

  tcase_add_test(tc1_1, s21_str_to_lower_tests_case);
  tcase_add_test(tc1_1, s21_str_to_upper_tests_case);

  tcase_add_test(tc1_1, test_simple_int);
  tcase_add_test(tc1_1, precise_int);
  tcase_add_test(tc1_1, width_int);
  tcase_add_test(tc1_1, minus_width_int);
  tcase_add_test(tc1_1, plus_width_int);
  tcase_add_test(tc1_1, padding_int);
  tcase_add_test(tc1_1, star_width_int);
  tcase_add_test(tc1_1, star_precision_int);
  tcase_add_test(tc1_1, many_flags_many_ints);
  tcase_add_test(tc1_1, flags_long_int);
  tcase_add_test(tc1_1, flags_short_int);
  tcase_add_test(tc1_1, flags_another_long_int);
  tcase_add_test(tc1_1, space_flag_int);
  tcase_add_test(tc1_1, unsigned_val);
  tcase_add_test(tc1_1, unsigned_val_width);
  tcase_add_test(tc1_1, unsigned_val_flags);
  tcase_add_test(tc1_1, unsigned_val_many_flags);
  tcase_add_test(tc1_1, unsigned_val_short);
  tcase_add_test(tc1_1, unsigned_val_long);
  tcase_add_test(tc1_1, unsigned_val_many);
  tcase_add_test(tc1_1, octal);
  tcase_add_test(tc1_1, octal_width);
  tcase_add_test(tc1_1, octal_flags);
  tcase_add_test(tc1_1, octal_precision);
  tcase_add_test(tc1_1, octal_many_flags);
  tcase_add_test(tc1_1, unsigned_val_precision);
  tcase_add_test(tc1_1, octal_short);
  tcase_add_test(tc1_1, octal_long);
  tcase_add_test(tc1_1, octal_many);
  tcase_add_test(tc1_1, octal_zero);
  tcase_add_test(tc1_1, octal_hash);
  tcase_add_test(tc1_1, unsigned_zero);
  tcase_add_test(tc1_1, hex_width);
  tcase_add_test(tc1_1, hex_flags);
  tcase_add_test(tc1_1, hex_precision);
  tcase_add_test(tc1_1, hex_many);
  tcase_add_test(tc1_1, hex_many_flags);
  tcase_add_test(tc1_1, hex_zero);
  tcase_add_test(tc1_1, hex_huge);
  tcase_add_test(tc1_1, hex_short);
  tcase_add_test(tc1_1, hex_long);
  tcase_add_test(tc1_1, hex_one_longer_width);
  tcase_add_test(tc1_1, hex_two_longer_width);
  tcase_add_test(tc1_1, one_char);
  tcase_add_test(tc1_1, one_precision);
  tcase_add_test(tc1_1, one_width);
  tcase_add_test(tc1_1, one_many);
  tcase_add_test(tc1_1, string);
  tcase_add_test(tc1_1, string_precision);
  tcase_add_test(tc1_1, string_width);
  tcase_add_test(tc1_1, string_flags);
  tcase_add_test(tc1_1, string_long);
  tcase_add_test(tc1_1, string_many);
  tcase_add_test(tc1_1, ptr);
  tcase_add_test(tc1_1, ptr_width);
  tcase_add_test(tc1_1, ptr_precision);
  tcase_add_test(tc1_1, null_ptr);
  tcase_add_test(tc1_1, n_specifier);
  tcase_add_test(tc1_1, string_width_huge);
  tcase_add_test(tc1_1, float_precision);
  tcase_add_test(tc1_1, float_width);
  tcase_add_test(tc1_1, float_precision_zero);
  tcase_add_test(tc1_1, float_precision_empty);
  tcase_add_test(tc1_1, float_precision_huge);
  tcase_add_test(tc1_1, float_precision_huge_negative);
  tcase_add_test(tc1_1, float_huge);
  tcase_add_test(tc1_1, float_flags);
  tcase_add_test(tc1_1, float_many);
  // tcase_add_test(tc1_1, e_precision);
  tcase_add_test(tc1_1, e_precision_zero);
  tcase_add_test(tc1_1, e_precision_empty);
  tcase_add_test(tc1_1, e_precision_huge);
  tcase_add_test(tc1_1, e_precision_huge_negative);
  tcase_add_test(tc1_1, e_huge);
  tcase_add_test(tc1_1, e_many);
  tcase_add_test(tc1_1, e_width);
  tcase_add_test(tc1_1, e_flags);
  tcase_add_test(tc1_1, E_int);
  tcase_add_test(tc1_1, all_empty);
  tcase_add_test(tc1_1, empty_format_and_parameters);
  tcase_add_test(tc1_1, test_one_char);
  tcase_add_test(tc1_1, test_many_char);
  tcase_add_test(tc1_1, test_one_string);
  tcase_add_test(tc1_1, test_many_string);
  tcase_add_test(tc1_1, test_one_dec);
  tcase_add_test(tc1_1, test_many_dec);
  tcase_add_test(tc1_1, test_one_int);
  tcase_add_test(tc1_1, test_many_int);
  tcase_add_test(tc1_1, test_one_float);
  tcase_add_test(tc1_1, test_many_float);
  tcase_add_test(tc1_1, test_one_unsigned_dec);
  tcase_add_test(tc1_1, test_many_unsigned_dec);
  tcase_add_test(tc1_1, test_one_char_with_alignment_left);
  tcase_add_test(tc1_1, test_one_char_with_alignment_right);
  tcase_add_test(tc1_1, test_many_char_with_alignment);
  tcase_add_test(tc1_1, test_one_hex_lower);
  tcase_add_test(tc1_1, test_one_hex_upper);
  tcase_add_test(tc1_1, test_many_hex_lower);
  tcase_add_test(tc1_1, test_many_hex_upper);
  tcase_add_test(tc1_1, test_one_hex_lower_with_alignment_left);
  tcase_add_test(tc1_1, test_one_hex_lower_with_alignment_right);
  tcase_add_test(tc1_1, test_one_hex_upper_with_alignment_left);
  tcase_add_test(tc1_1, test_one_hex_upper_with_alignment_right);
  tcase_add_test(tc1_1, test_many_hex_lower_with_alignment);
  tcase_add_test(tc1_1, test_many_hex_upper_with_alignment);
  tcase_add_test(tc1_1, test_one_hex_with_hashtag);
  tcase_add_test(tc1_1, test_one_hex_upper_with_hashtag);
  tcase_add_test(tc1_1, test_many_hex_lower_with_hashtag_and_alignm);
  tcase_add_test(tc1_1, test_many_hex_upper_with_hashtag_and_alignm);
  tcase_add_test(tc1_1, test_one_hex_lower_with_width_star);
  tcase_add_test(tc1_1, test_one_hex_upper_with_width_star);
  tcase_add_test(tc1_1,
                 test_many_hex_lower_with_width_star_and_align_and_hashtag);
  tcase_add_test(tc1_1, test_many_hex_upper_with_width_star);
  tcase_add_test(tc1_1, test_one_hex_lower_with_precision);
  tcase_add_test(tc1_1, test_one_hex_upper_with_precision);
  tcase_add_test(tc1_1, test_many_hex_lower_with_precision_and_other);
  tcase_add_test(tc1_1, test_many_hex_upper_with_precision_and_other);
  tcase_add_test(tc1_1, test_one_hex_lower_with_length);
  tcase_add_test(tc1_1, test_one_hex_upper_with_length);
  tcase_add_test(tc1_1, test_sprintf1);
  tcase_add_test(tc1_1, test_sprintf2);
  tcase_add_test(tc1_1, test_sprintf3);
  tcase_add_test(tc1_1, test_sprintf4);
  tcase_add_test(tc1_1, test_sprintf6);
  tcase_add_test(tc1_1, test_sprintf7);
  tcase_add_test(tc1_1, test_sprintf8);
  tcase_add_test(tc1_1, test_sprintf9);
  tcase_add_test(tc1_1, test_sprintf10);
  tcase_add_test(tc1_1, test_sprintf11);
  // tcase_add_test(tc1_1, test_sprintf12);
  tcase_add_test(tc1_1, test_sprintf14);
  tcase_add_test(tc1_1, test_sprintf15);
  tcase_add_test(tc1_1, test_sprintf16);
  tcase_add_test(tc1_1, test_sprintf17);
  tcase_add_test(tc1_1, test_sprintf18);
  tcase_add_test(tc1_1, test_sprintf19);
  tcase_add_test(tc1_1, test_sprintf20);
  tcase_add_test(tc1_1, test_sprintf24);
  tcase_add_test(tc1_1, test_sprintf25);
  tcase_add_test(tc1_1, test_sprintf28);
  tcase_add_test(tc1_1, test_sprintf29);
  tcase_add_test(tc1_1, test_sprintf30);
  tcase_add_test(tc1_1, test_sprintf31);
  tcase_add_test(tc1_1, test_sprintf32);
  tcase_add_test(tc1_1, test_sprintf33);
  tcase_add_test(tc1_1, test_sprintf35);
  tcase_add_test(tc1_1, test_sprintf36);
  tcase_add_test(tc1_1, test_sprintf37);
  tcase_add_test(tc1_1, test_sprintf38);
  tcase_add_test(tc1_1, test_sprintf39);
  tcase_add_test(tc1_1, test_sprintf40);
  tcase_add_test(tc1_1, test_sprintf41);
  tcase_add_test(tc1_1, test_sprintf42);
  tcase_add_test(tc1_1, test_sprintf43);
  tcase_add_test(tc1_1, test_sprintf44);
  tcase_add_test(tc1_1, test_sprintf26);
  tcase_add_test(tc1_1, test_sprintf27);
  tcase_add_test(tc1_1, g_trailing_zero);
  tcase_add_test(tc1_1, g_large);
  tcase_add_test(tc1_1, g_small);
  tcase_add_test(tc1_1, g_precision);
  tcase_add_test(tc1_1, g_precision_zero);
  tcase_add_test(tc1_1, g_precision_missing);
  tcase_add_test(tc1_1, g_many_zeroes_in_front);
  tcase_add_test(tc1_1, g_one_zero);
  tcase_add_test(tc1_1, g_mantiss);
  tcase_add_test(tc1_1, g_mantiss_flags);
  tcase_add_test(tc1_1, g_short_no_mantiss);
  tcase_add_test(tc1_1, LG);
  tcase_add_test(tc1_1, g_many);
  tcase_add_test(tc1_1, g_zero);
  tcase_add_test(tc1_1, width_char);

  tcase_add_test(tc1_1, s21_trim_1);
  tcase_add_test(tc1_1, s21_trim_2);
  tcase_add_test(tc1_1, s21_trim_3);
  tcase_add_test(tc1_1, s21_trim_4);
  tcase_add_test(tc1_1, s21_trim_5);
  tcase_add_test(tc1_1, s21_trim_6);
  tcase_add_test(tc1_1, s21_trim_7);
  tcase_add_test(tc1_1, s21_trim_8);
  tcase_add_test(tc1_1, s21_insert_1);
  tcase_add_test(tc1_1, s21_insert_2);
  tcase_add_test(tc1_1, s21_insert_3);
  tcase_add_test(tc1_1, s21_insert_4);
  tcase_add_test(tc1_1, s21_insert_5);
  tcase_add_test(tc1_1, s21_insert_6);

  srunner_run_all(sr, CK_ENV);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  return nf == 0 ? 0 : 1;
}
