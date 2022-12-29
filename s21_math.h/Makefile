FLAGS = -Wall -Wextra -Werror
CC = gcc

all: test

style:
	clang-format -style=google -n *.c *.h
	cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h

clean:
	rm -rf ./*.o ./s21_math

s21_math.a:
	$(CC) -c $(FLAGS) s21_math.c
	ar -rcs s21_math.a *.o

test: clean
	$(CC) $(FLAGS) -c s21_math_test.c
	$(CC) $(FLAGS) -c s21_math.c
	$(CC) $(FLAGS) s21_math.o s21_math_test.o -lcheck -lm -lpthread -lrt -lsubunit -o ./s21_math
	./s21_math
