CPP=g++ -std=c++17 
FLAGS=-Wall -Wextra -Werror -I ./include -I ./tests/include
SANITIZER= -g -fsanitize=address

TEST_MAIN=tests_main.cc
TEST_SRCS=tests/*.cc

all: clean test

test: clean
	mkdir -p build
	$(CPP) $(FLAGS) $(TEST_SRCS) $(TEST_MAIN) -lgtest --coverage -o ./build/test
	mkdir -p bin
	mv build/test bin/
	./bin/test

gcov_report: test
	gcovr -r ./ --object-directory ./build --html --html-details -o build/coverage_report.html
	open build/coverage_report.html

valgrind: test
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes --leak-check=full ./bin/test

clean:
	rm -rf bin build

style:
	cp ../materials/linters/.clang-format ./
	find ./ -iname "*.h" -o -iname "*.cc" | xargs clang-format -n

