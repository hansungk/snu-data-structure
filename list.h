#include <iostream>

template <typename T> class List {
private:
  class listNode {
  public:
    T data;
    listNode *next;
    listNode(T newItem) : data(newItem), next(NULL) {}
  };

public:
  // Dummy node
  List() : head(new listNode(T())) {}
  ~List();
  void insert(int loc, T d);
  void remove(int loc);
  int getSize();
  T &getData(int loc);

  void insertAtFront(T d) { insertAtFront(head->next, d); }
  void print() { print(head->next); }
  void printReverse() { printReverse(head->next); }

private:
  void insertAtFront(listNode *&curr, T d);
  void print(listNode *curr);
  void printReverse(listNode *curr);
  listNode *find(listNode *curr, int k);
  void remove(listNode *curr);

  listNode *head;
  int size;
};

template <typename T> List<T>::~List() {
  listNode *curr = head;
  while (curr) {
    listNode *next = curr->next;
    delete curr;
    curr = next;
  }
  curr = NULL;
}

template <typename T>
void List<T>::insertAtFront(listNode *&curr, T d) {
  listNode *t = new listNode(d);
  t->next = curr;
  curr = t;
}

template <typename T>
void List<T>::print(listNode *curr) {
  if (curr) {
    std::cout << curr->data << " ";
    print(curr->next);
  }
}

template <typename T>
void List<T>::printReverse(listNode *curr) {
  if (curr) {
    printReverse(curr->next);
    std::cout << curr->data << " ";
  }
}

template <typename T>
typename List<T>::listNode *List<T>::find(listNode *curr, int k) {
  if (!curr || k == 0)
    return curr;
  return find(curr->next, k - 1);
}

template <typename T>
void List<T>::insert(int k, T d) {
  listNode *n = new listNode(d);
  listNode *p = find(head, k - 1);
  n->next = p->next;
  p->next = n;
}

template <typename T> void List<T>::remove(int k) { remove(find(head, k)); }

template <typename T> void List<T>::remove(listNode *curr) {
  // Trick!
  if (curr) {
    listNode *t = curr->next;
    curr->data = t->data;
    curr->next = t->next;
    delete t;
  }
#if 0
  listNode *t = head;
  while (t->next != curr)
    t = t->next;
  t->next = curr->next;
  delete curr;
#endif
}
