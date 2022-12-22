FLAGS = -Wall -Werror -Wextra
#TARGET = ./s21_string
CC = gcc

all: test

style:

	clang-format -style=google -n *.c *.h
	cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h

clean:
	rm -rf ./*.o ./s21_string

s21_string.a:
	$(CC) -c $(FLAGS) s21_string.c
	ar -rcs s21_string.a *.o

test: clean
	$(CC) $(FLAGS) -c s21_string_test.c
	$(CC) $(FLAGS) -c s21_string.c
	$(CC) $(FLAGS) s21_string.o s21_string_test.o -lcheck -lm -lpthread -lrt -lsubunit -o ./s21_string
	./s21_string