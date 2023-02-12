CC=gcc
CFLAGS=-Wall -Wextra -Werror
TFLAGS=--coverage -lcheck -lm -lpthread -lrt -lsubunit -o
SOURCES=s21_*.c support_matrix.c

all: s21_matrix.a

style:
	clang-format -style=google -n *.c *.h

cppcheck:
	cppcheck —enable=all —suppress=missingIncludeSystem *.c *.h

s21_matrix.a: 
	$(CC) $(CFLAGS) -c $(SOURCES) s21_matrix.h
	ar rc s21_matrix.a *.o
	ranlib s21_matrix.a

test: clean s21_matrix.a
	$(CC) $(CFLAGS) $(SOURCES) unit_tests_matrix.c $(TFLAGS) unit_tests_matrix
	./unit_tests_matrix

gcov_report: test
	$(CC) $(CFLAGS) $(SOURCES) unit_tests_matrix.c $(TFLAGS) unit_tests_matrix
	./unit_tests_matrix
	lcov -t "unit_tests_matrix" -o unit_tests_matrix.info -c -d .
	genhtml -o report unit_tests_matrix.info
	open report/index.html

valgrind: test
	valgrind --track-origins=yes --leak-check=full ./unit_tests_matrix

leaks: test
	leaks -atExit -- ./unit_tests_matrix

clean: 
	rm -f *.o *.out *.a *.gch *.gcda *.gcno *.info
	rm -rf report
	rm -rf unit_tests_matrix
