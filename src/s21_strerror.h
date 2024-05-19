#ifndef SRC_S21_STRERROR_H_
#define SRC_S21_STRERROR_H_

#include "s21_string.h"

#ifdef __linux__
#define MAX_ERRLIST 134
#define MIN_ERRLIST -1
#define UNKNOWN_ERROR "Unknown error "
#endif
#if defined(__MAC__) || defined(__APPLE__)
#define MAX_ERRLIST 107
#define UNKNOWN_ERROR "Unknown error: "
#endif

char *s21_strerror(int errnum);

#endif  // SRC_S21_STRERROR_H_
