SRC_C = my_cat.c
SRC_G = my_grep.c
NAME_C = cat_21
NAME_G = grep_21
NAME_TC = cat_test
CC = gcc
CFLAGS = -Wall -Wextra -Werror -c

all: cat grep

cat: $(SRC_C)
	$(CC) $(CFLAGS) $(SRC_C)
	$(CC) my_cat.o -o $(NAME_C)
	cp test_file_cat/bash_cat.sh ./
	cp test_file_cat/ascii.txt ./

grep: $(SRC_G)
	$(CC) $(CFLAGS) $(SRC_G)
	$(CC) my_grep.o -o $(NAME_G)

cleancat:
	rm -rf my_cat.o
	rm -rf ascii.txt
	rm -rf bash_cat.sh
	rm -rf $(NAME_C)
	rm -rf $(NAME_TC)

cleangrep:
	rm -rf my_grep.o
	rm -rf $(NAME_G)

fclean:
	rm -rf *.o
	rm -rf bash_cat.sh
	rm -rf ascii.txt
	rm -rf $(NAME_C)
	rm -rf $(NAME_G)
	rm -rf $(NAME_TC)

rebuild: fclean
	make