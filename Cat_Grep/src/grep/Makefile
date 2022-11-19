SRC = s21_grep.c struct.c
NAME = s21_grep
TEST = grep_test
CC = gcc
CFLAGS = -Wall -Wextra -Werror -c

all: s21_grep

s21_grep: $(SRC)
	$(CC) $(CFLAGS) $(SRC)
	$(CC) *.o -o $(NAME)

cpp:
	cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h

cl:
	clang-format -style=google -n *.c *.h

clean:
	rm -rf *.o
	rm -rf bash_grep.sh
	rm -rf empty_file.txt
	rm -rf f.txt
	rm -rf ff.txt
	rm -rf test_grep.txt
	rm -rf $(NAME)
	rm -rf $(TEST)

rebuild: clean
	make