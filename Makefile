CXX=clang++

all: main.cpp
	$(CXX) -fsanitize=address -std=c++11 -g -Wall -Wextra $< -o han-avl

main.cpp: list.h avl_tree.h

clean:
	rm -f han-avl
