SRC_C = my_cat.c
SRC_G = grp.c
NAME_C = cat_21
NAME_G = grep_21
CC = gcc
CFLAGS = -Wall -Wextra -Werror -c

all: cat grap

cat: $(SRC_C)
	$(CC) $(CFLAGS) $(SRC_C)
	$(CC) *.o -o $(NAME_C)
	rm -rf *.o

grep: $(SRC_G)
	$(CC) $(CFLAGS) $(SRC_G)
	$(CC) *.o -o $(NAME_G)
	rm -rf *.o

clean:
	rm -rf *.o

fclean:
	rm -rf *.o
	rm -rf $(NAME_C)
	rm -rf $(NAME_G)

rebuild: fclean
	make