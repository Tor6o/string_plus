NAME = s21_string.h
CC = gcc
CC_FLAGS = -std=c11 -Wall -Wextra -Werror -g
SOURCE = $(wildcard s21_*.c)
TEST_FLAGS = -std=c11 -g
GCOVFLAGS = -L. -ls21_string --coverage
OS = $(shell uname)
ifeq ($(OS), Linux)
	CHECK_FLAGS = -lcheck -pthread -lrt -lm -lsubunit
else
	CHECK_FLAGS = -lcheck
endif

TEST_COMPILE = $(CC) $(TEST_FLAGS) test.c libs21_string.a $(CHECK_FLAGS) -L. -ls21_string

all: clean s21_string.a

s21_string.o:
	$(CC) $(CC_FLAGS) -c s21*.c

s21_string.a: s21_string.o
	ar rcs libs21_string.a *.o
	rm -rf *.o
	ranlib libs21_string.a
	cp libs21_string.a s21_string.a
	cp libs21_string.a ls21_string.a

clean:
	rm -rf *.o s21_test *.g* *.info *.out report *.a *.dSYM debug

re: clean all

test: s21_string.a
	$(TEST_COMPILE)
	./a.out

debug: clean s21_string.a
	gcc -std=c11 -Wall -Wextra -g debug.c libs21_string.a
	./a.out

gcov_report: lcov ${SOURCE}
	${CC} --coverage ${SOURCE} test.c -o s21_test $(CHECK_FLAGS)
	./s21_test
	lcov -t "s21_test" -o s21_test.info -c -d .
	genhtml -o report s21_test.info
	open ./report/index.html

lcov:
ifeq ("", "$(shell PATH=$(PATH) which lcov)")
	$(error Need to install lcov)
endif


check:
	clang-format -style=google -i *.c *.h
	clang-format -style=google -n *.c *.h
	make test
ifeq ($(OS), Darwin)
	CK_FORK=no leaks --atExit -- ./a.out
else
	valgrind ./a.out --leak-check=full
endif
	make clean
