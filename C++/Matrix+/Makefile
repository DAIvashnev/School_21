CC=g++
CFLAGS=-Wall -Wextra -Werror -std=c++17 -g
TFLAGS=--coverage -lgtest -lgtest_main -lm -lpthread -lrt -lsubunit -fprofile-arcs -o
SOURCES=sources/*.cc

all: s21_matrix_oop.a

s21_matrix_oop.a: 
	$(CC) $(CFLAGS) -c $(SOURCES) s21_matrix_oop.h
	ar -rc s21_matrix_oop.a *.o
	ranlib s21_matrix_oop.a

test: clean s21_matrix_oop.a
	$(CC) $(SOURCES) s21_matrix_tests.cc $(TFLAGS) s21_matrix_tests
	./s21_matrix_tests

gcov_report: clean test
	gcov -b -l -p -c *.gcno
	gcovr -g -k -r . --html --html-details -o coverage_report.html
	open coverage_report.html

style:
	clang-format -style=google -n *.h s21_matrix_tests.cc
	clang-format -style=google -n sources/*.cc

valgrind: clean test
	valgrind --track-origins=yes --leak-check=full ./s21_matrix_tests

leaks: clean test
	leaks -atExit -- ./s21_matrix_tests

clean: 
	rm -f *.o *.out *.a *.gch *.gcda *.gcno *.info *.gcov *.html *.css
	rm -rf report
	rm -rf s21_matrix_tests
