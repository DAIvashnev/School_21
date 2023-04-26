CC=gcc -std=c11 -pedantic
CFLAGS=-Wall -Wextra -Werror

APPNAME = 3DViewer_v1.app

ifeq ($(OS), Windows_NT)
TFLAGS = 
else
UNAME := $(shell uname)
ifeq ($(UNAME), Darwin)
TFLAGS = -lcheck --coverage -fsanitize=address -g
else
TFLAGS = -lm -lcheck -lm -lpthread -lrt -lsubunit --coverage #-fsanitize=address -g
APPNAME = 3DViewer_v1
endif
endif

SOURCES=affine.c parser.c
TEST_SRC=test.c

all: clean gcov_report install

s21_3DViewer_v1.a: 
	$(CC) $(CFLAGS) -c $(SOURCES) affine.h parser.h
	ar rc s21_3DViewer_v1.a *.o
	ranlib s21_3DViewer_v1.a

install:
	@rm -rf build
	@mkdir build
	@cd 3DViewer_v1 && qmake && make && make clean && rm Makefile && cd ../ && mv 3DViewer_v1/$(APPNAME) build

uninstall:
	@rm -rf build

dvi:
	@doxygen dox/Doxyfile
	@open ./html/index.html

dist:
	@rm -rf dist.zip
	zip -vr dist.zip build/$(APPNAME)

dist_clean:
	rm -rf dist.zip

test: clean s21_3DViewer_v1.a
	@rm -rf models
	@mkdir models
	@unzip Models.zip -d models
	@$(CC) $(CFLAGS) $(SOURCES) $(TEST_SRC) $(TFLAGS) -o test
	./test

gcov_report: test
	@$(CC) $(CFLAGS) $(SOURCES) $(TEST_SRC) $(TFLAGS) -o test
	./test
	@lcov -t "test" -o test.info -c -d .
	@genhtml -o report test.info
	@open report/index.html
	@rm -f *.gcov *.gcda *.gcno *.info report.out *.o

clean:
	rm -rf *.o *.out *.a *.gch *.gcda *.gcno report *.info test headers/*.gch html latex models

valgrind: test
	valgrind --track-origins=yes --leak-check=full ./test -lm

leaks: test
	leaks -atExit -- ./test

style:
	clang-format -style=google -n *.c *.h *.cpp 3DViewer_v1/*.cpp 3DViewer_v1/*.h
	
cppcheck:
	cppcheck —enable=all —suppress=missingIncludeSystem *.c

qt_qmake:
	sudo apt-get install qtbase5-dev qtchooser qt5-qmake qtbase5-dev-tools
