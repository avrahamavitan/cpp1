#avrahamavitan@gmail.com

CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11 -Iinclude

SRC = SquareMat.cpp
HDR = SquareMat.hpp
TEST = test.cpp
MAIN = main.cpp

all: Main test

Main: $(MAIN) $(SRC)
	$(CXX) $(CXXFLAGS) -o Main $(MAIN) $(SRC)

test: $(TEST) $(SRC) $(HDR)
	$(CXX) $(CXXFLAGS) -o test.out $(TEST) $(SRC)
	./test.out


valgrind: test
	valgrind ./test.out


clean:
	rm -f test.out Main
