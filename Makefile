CXX=clang++
CXXFLAGS=-g -fsanitize=address -Wall -Wextra -Wpedantic -std=c++11

all: han-avl

han-avl: main.o
	$(CXX) $(CXXFLAGS) $< -o $@

main.cpp: list.h avl_tree.h

clean:
	rm -f han-avl *.o
