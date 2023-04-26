CC=gcc
CFLAGS=-Wall -Wextra -Werror
TFLAGS=--coverage -lcheck -lm -lpthread -lrt -lsubunit -o
SOURCES=validation.c stack.c parsing.c
TEST_SRC=tests/*

all: clean gcov_report install

s21_SmartCalc_v1.a: 
	$(CC) $(CFLAGS) -c $(SOURCES) headers/*.h
	ar rc SmartCalc_v1.a *.o
	ranlib SmartCalc_v1.a

install:
	@rm -rf build
	@mkdir build
	@cd qt && qmake && make && make clean && rm Makefile && cd ../ && mv qt/SmartCalc_v1 build
	
	
uninstall:
	@rm -rf build

dvi:
	@doxygen dox/Doxyfile
	@open ./html/index.html

dist:
	@rm -rf dist.tar
	tar -cvzf dist.tar build/SmartCalc_v1

dist_clean:
	rm -rf dist.tar

test: clean s21_SmartCalc_v1.a
	@$(CC) $(CFLAGS) $(SOURCES) $(TEST_SRC) $(TFLAGS) unit_tests_SCv1
	./unit_tests_SCv1

gcov_report: test
	@$(CC) $(CFLAGS) $(SOURCES) $(TEST_SRC) $(TFLAGS) unit_tests_SCv1
	./unit_tests_SCv1
	@lcov -t "unit_tests_SCv1" -o unit_tests_SCv1.info -c -d .
	@genhtml -o report unit_tests_SCv1.info
	@open report/index.html
	@rm -f *.gcov *.gcda *.gcno *.info report.out *.o

clean:
	rm -rf *.o *.out *.a *.gch *.gcda *.gcno report *.info unit_tests_SCv1 headers/*.gch html latex

valgrind: test
	valgrind --track-origins=yes --leak-check=full ./unit_tests_SCv1 -lm

leaks: test
	leaks -atExit -- ./unit_tests_SCv1

style:
	clang-format -style=google -n *.c
	clang-format -style=google -n headers/*
	clang-format -style=google -n tests/*
	
cppcheck:
	cppcheck —enable=all —suppress=missingIncludeSystem *.c
	cppcheck —enable=all —suppress=missingIncludeSystem tests/*.c

qt_qmake:
	sudo apt-get install qtbase5-dev qtchooser qt5-qmake qtbase5-dev-tools