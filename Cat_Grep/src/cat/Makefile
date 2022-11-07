SRC = s21_cat.c
NAME= s21_cat
TEST = cat_test
CC = gcc
CFLAGS = -Wall -Wextra -Werror -c

all: s21_cat

s21_cat: $(SRC)
	$(CC) $(CFLAGS) $(SRC)
	$(CC) s21_cat.o -o $(NAME)
	cp ../test_file_cat/bash_cat.sh ./
	cp ../test_file_cat/ascii.txt ./

clean:
	rm -rf s21_cat.o
	rm -rf ascii.txt
	rm -rf bash_cat.sh
	rm -rf $(NAME)
	rm -rf $(TEST)

rebuild: fclean
	make