#ifndef _QUEUE_H
#define _QUEUE_H

#include <memory>
#include <algorithm>

template <typename T> class Queue {
public:
  Queue();
  Queue(size_t cap);

  void push(const T &d);
  T pop();
  bool empty() const { return front == rear; }
  void print() const;

  size_t size() const { return (rear + cap - front) % cap; }
  size_t capacity() const { return cap; }

private:
  bool full() const { return cap == 0 || ((rear + 1) % cap == front); }
  void rearrange();
  void expand();

  std::unique_ptr<T[]> data;
  size_t cap;
  size_t front;
  size_t rear;
};

template <typename T>
Queue<T>::Queue() : data(nullptr), cap(0), front(0), rear(0) {}

template <typename T>
Queue<T>::Queue(size_t cap) : data(new T[cap]), cap(cap), front(0), rear(0) {}

template <typename T> void Queue<T>::rearrange() {
  if (!cap) {
    return;
  }

  std::unique_ptr<T[]> new_data(new T[cap]);
  if (rear > front) {
    std::copy(data.get() + front + 1, data.get() + rear + 1, new_data.get());
  } else {
    std::copy(data.get() + front + 1, data.get() + cap, new_data.get());
    std::copy(data.get(), data.get() + rear + 1, new_data.get() + cap- front - 1);
  }
  rear = size() - 1;
  front = cap - 1;
  data = std::move(new_data);
}

template <typename T> void Queue<T>::expand() {
  size_t new_cap;

  if (cap)
    new_cap = cap * 2;
  else
    new_cap = 2;

  std::unique_ptr<T[]> new_data(new T[new_cap]);
  std::copy(data.get(), data.get() + cap, new_data.get());
  data = std::move(new_data);
  cap = new_cap;
  std::cout << "size(): " << size() << std::endl;
  rear = (cap + size() - 1) % cap;
  front = cap - 1;
}

template <typename T> void Queue<T>::push(const T &d) {
  if (!full()) {
    rear = (rear + 1) % cap;
    data[rear] = d;
  } else {
    std::cout << "Resizing while pushing " << d << ". ";
    rearrange();
    expand();
    std::cout << "Capacity is now " << cap << std::endl;
    push(d);
  }
}

template <typename T> T Queue<T>::pop() {
  if (!empty()) {
    front = (front + 1) % cap;
    return data[front];
  }
}

template <typename T> void Queue<T>::print() const {
  std::cout << "Queue {";
  for (size_t i = (front + 1) % cap; i != rear; i = (i + 1) % cap) {
    std::cout << data[i] << ", ";
  }
  if (!empty())
    std::cout << data[rear];
  std::cout << "}" << std::endl;
}

#endif
