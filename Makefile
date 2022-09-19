SRC = my_cat.c
NAME = cat_21
CC = gcc
CFLAGS = -Wall -Wextra -Werror -c

all: cat

cat: $(SRC)
	$(CC) $(CFLAGS) $(SRC)
	$(CC) *.o -o $(NAME)
	rm -rf *.o

clean:
	rm -rf *.o

fclean:
	rm -rf *.o
	rm -rf $(NAME)

rebuild: fclean
	make