CC=gcc
CFLAGS=-Wall -Werror -Wextra
LDFLAGS="-lgcov"
TESTSFLAGS= -lm -lcheck -lm -lpthread -lrt -lsubunit #-fsanitize=address -g
TESTSFLAGS_MAC= -lcheck
COVERAGE_FLAGS= --coverage
SOURCES= s21_*.c
OBJECTS=$(SOURCES:.c=.o)
SOURCES_STACK=
EXECUTABLE=
FLAG_COV = -lcheck -lgcov -fprofile-arcs --coverage 
GCOVFLAGS=-fprofile-arcs -ftest-coverage
SOURCES_ALL:=$(wildcard *.c)
SOURCES_FUN:=$(shell find . -not -name "s21_decimal_test.c" -name "*.c")
OPEN_CM=open
DIR_O=dir_o

all: s21_decimal.a

s21_decimal.a: library

decimal_objs: 
	$(CC) $(CFLAGS) -c $(SOURCES) $(OBGECTS)

decimal_objs_cov:
	$(CC) $(CFLAGS) $(COVERAGE_FLAGS) -c $(SOURCES) $(OBGECTS)

s21_decimal_test:
	$(CC) -c unit_test.c -o test.o

library: decimal_objs
	ar rc s21_decimal.a $(OBJECTS)

library_cov: decimal_objs_cov
	ar rc s21_decimal.a $(OBJECTS)

create_library: library
	ranlib s21_decimal.a

create_library_cov: library_cov
	ranlib s21_decimal.a

unit_test: create_library s21_decimal_test
	$(CC) test.o s21_decimal.a $(TESTSFLAGS) -o s21_test

unit_test_coverage: create_library_cov s21_decimal_test
	$(CC) test.o s21_decimal.a $(TESTSFLAGS) $(LDFLAGS) -o s21_test

unit_test_mac: create_library s21_decimal_test
	$(CC) test.o s21_decimal.a $(TESTSFLAGS_MAC) -o s21_test

unit_test_mac_cov: create_library_cov s21_decimal_test
	$(CC) test.o s21_decimal.a $(TESTSFLAGS_MAC) $(LDFLAGS) -o s21_test

gcov_report: unit_test_coverage
	./s21_test
	lcov -t "gcov_report" -o s21_decimal.info -c -d .
	genhtml -o report s21_decimal.info
	open report/index.html

gcov_report_mac: unit_test_mac_cov
	./s21_test
	lcov -t "gcov_report" -o s21_decimal.info -c -d .
	genhtml -o report s21_decimal.info

test_mac: unit_test_mac
	./s21_test

test: unit_test
	./s21_test

clean:
	rm -f *.out *.a *.o asd.c s21_test *.html *.gcno *.gcda coverage_report.css *.info *.gch
	rm -rf report cov-report
	rm -rf unit_test
	rm -rf $(DIR_O)

rebuild: clean all


# ==== ENEDINAE ====
eb:
	$(CC) -c *.c s21_decimal.h
	mkdir $(DIR_O)
	mv *.o $(DIR_O)
	ar rc s21_decimal.a $(DIR_O)/*.o
	ranlib s21_decimal.a

et: clean eb
	$(CC) *.c --coverage -lcheck -lm -lpthread -lrt -lsubunit -o unit_test
	./unit_test

eg: 
	$(CC) *.c --coverage -lcheck -lm -lpthread -lrt -lsubunit -o unit_test
	./unit_test
	lcov -t "unit_test" -o unit_test.info -c -d .
	genhtml -o report unit_test.info
	open report/index.html