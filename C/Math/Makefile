CC=gcc -std=c11 -D_GNU_SOURCE
CFLAGS=-c -Wall -Wextra -Werror
TEST_FLAGS=-lcheck -lm -lpthread
GCOV_FLAGS=--coverage -Wall -Wextra -Werror

SOURCES=$(wildcard s21_*.c)
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=s21_math

TESTS_SOURCES=test.c $(wildcard tests/*.c)
TESTS_OBJECTS=$(TESTS_SOURCES:.c=.o)

ifeq ($(shell uname -s),Linux)
	TEST_FLAGS += -lrt -lsubunit
endif

all: s21_math.a

$(EXECUTABLE): $(OBJECTS)
	$(CC) $^ -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@


s21_math.a: $(OBJECTS)
	ar -rcs s21_math.a $(OBJECTS)
	ranlib s21_math.a

test: $(TESTS_OBJECTS) s21_math.a
	$(CC) $^ -o test $(TEST_FLAGS)
	./test
	
gcov_report: $(TESTS_OBJECTS)
	$(CC) $(GCOV_FLAGS) $(TESTS_OBJECTS) $(SOURCES) $(TEST_FLAGS) -o test
	./test
	gcov *.gcno
	lcov -t "test" -o test.info -c -d . --rc lcov_branch_coverage=1
	genhtml -o report test.info --rc lcov_branch_coverage=1
	open report/index.html

clean:
	rm -rf *.o tests/*.o $(EXECUTABLE) test
	rm -rf *.gcno *.gcov *.gcda *.info report s21_math.a

rebuild: clean all

style:
	clang-format -style=google -n ./s21_math.c
	clang-format -style=google -n ./s21_math.h
	clang-format -style=google -n ./s21_math_test.c
	python3 ./cpplint.py --extensions=c ./s21_math.c
