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

test:
	cp -r ../test_file_grep/. .
	chmod +x test_grep.sh

clean:
	rm -rf *.o
	rm -rf test_grep.sh
	rm -rf empty_file.txt
	rm -rf f.txt
	rm -rf ff.txt
	rm -rf test_grep.txt
	rm -rf $(NAME)
	rm -rf $(TEST)

rebuild: clean
	make