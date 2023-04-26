SRC = s21_cat.c
NAME= s21_cat
TEST = cat_test
CC = gcc
CFLAGS = -Wall -Wextra -Werror -c

all: s21_cat

s21_cat: $(SRC)
	$(CC) $(CFLAGS) $(SRC)
	$(CC) s21_cat.o -o $(NAME)

cpp:
	cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h

cl:
	clang-format -style=google -n *.c *.h

test:
	cp -r ../test_file_cat/. .
	chmod +x test_cat.sh

clean:
	rm -rf s21_cat.o
	rm -rf ascii.txt
	rm -rf test_cat.sh
	rm -rf empty_file.txt
	rm -rf $(NAME)
	rm -rf $(TEST)

rebuild: clean
	make