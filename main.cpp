#include <iostream>
#include "list.h"
#include "queue.h"
#include "avl_tree.h"

// Not working.
void queue_test() {
  Queue<int> q(0);
  q.push(1);
  q.print();
  q.push(2);
  q.print();
  q.push(3);
  q.print();
  q.push(4);
  q.print();
  q.push(5);
  q.print();
}

void list_test() {
  List<int> list;
  list.insert(1, 5);
  list.insert(1, 4);
  list.insert(1, 3);
  list.insert(1, 2);
  list.insert(1, 1);
  list.print();
  std::cout << std::endl;

  list.remove(3);
  list.print();
  std::cout << std::endl;
}

void avl_test() {
  AvlTree<int> avl;
  avl.insert(10);
  avl.insert(5);
  avl.insert(17);
  avl.insert(2);
  avl.insert(9);
  avl.insert(12);
  avl.insert(20);
  avl.insert(3);
  avl.insert(11);
  avl.insert(15);
  avl.insert(18);
  avl.insert(30);
  avl.insert(13);
  avl.insert(33);
  avl.print();
  avl.remove(9);
  avl.print();
  avl.remove(12);
  avl.print();
}

int main() {
  avl_test();
}
