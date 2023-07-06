CC=g++
CFLAGS=-Wall -Wextra -Werror -std=c++17 -g
TFLAGS=--coverage -lgtest -lgtest_main -lm -lpthread -lrt -lsubunit -fprofile-arcs -o
SOURCES=model/*.cc controller/*.cc

all: s21_SmartCalc_v2.a

s21_SmartCalc_v2.a: 
	$(CC) $(CFLAGS) -c $(SOURCES) model/*.h controller/*.h
	ar -rc s21_SmartCalc_v2.a *.o
	ranlib s21_SmartCalc_v2.a

install:
	@rm -rf build
	@mkdir build
	@cd view && qmake && make && make clean && rm Makefile && cd .. && mv view/Smart_Calc_v2 build/
	
uninstall:
	@rm -rf build

dvi:
	@doxygen dox/Doxyfile
	@open ./html/index.html

dist:
	@rm -rf dist.tar
	tar -cvzf dist.tar build/Smart_Calc_v2

dist_clean:
	rm -rf dist.tar

test: clean s21_SmartCalc_v2.a
	$(CC) $(SOURCES) calc_v2_tests/*.cc $(TFLAGS) test_SC_v2
	./test_SC_v2

gcov_report: clean test
	gcov -b -l -p -c *.gcno
	gcovr -g -k -r . --html --html-details -o coverage_report.html
	open coverage_report.html

style:
	clang-format -style=google -n calc_v2_tests/*
	clang-format -style=google -n model/*
	clang-format -style=google -n controller/*
	clang-format -style=google -n view/*.cpp view/*.h

valgrind: clean test
	valgrind --track-origins=yes --leak-check=full ./test_SC_v2

leaks: clean test
	leaks -atExit -- ./test_SC_v2

clean: 
	rm -f *.o *.out *.a *.gch *.gcda *.gcno *.info *.gcov *.html *.css
	rm -f controller/*.gch model/*.gch view/*.gch
	rm -rf report
	rm -rf html latex
	rm -rf test_SC_v2