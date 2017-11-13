CXX=clang++
CXXFLAGS=-g -fsanitize=address,leak -Wall -Wextra -Wpedantic -std=c++11

all: han-avl

han-avl: main.o
	$(CXX) $(CXXFLAGS) $< -o $@

main.o: main.cpp list.h avl_tree.h queue.h

clean:
	rm -f han-avl *.o
