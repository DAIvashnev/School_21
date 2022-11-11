SRC = s21_grep.c struct.c
NAME = s21_grep
CC = gcc
CFLAGS = -Wall -Wextra -Werror -c

all: s21_grep

s21_grep: $(SRC)
	$(CC) $(CFLAGS) $(SRC)
	$(CC) *.o -o $(NAME)

clean:
	rm -rf *.o
	rm -rf bash_grep.sh
	rm -rf $(NAME)


rebuild: fclean
	make