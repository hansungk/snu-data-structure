#include "queue.h"
#define AUTO_HEIGHT 0

template <typename T> const T &max(const T &a, const T &b);

template <typename T> class AvlTree {
private:
  class Node {
  public:
    T key;
    int height;
    Node *left;
    Node *right;

    Node(T k, int h, Node *l, Node *r) : key(k), height(h), left(l), right(r) {}
  };

  Node *root;

  void traverse_preorder(Node *curr_node);
  void traverse_inorder(Node *curr_node);
  void clear(Node *curr_node);

  void insert(const T &x, Node *&t);
  void remove(const T &x, Node *&t);
  void do_removal(Node *&curr_node);
  void no_child_remove(Node *&curr_node);
  void one_child_remove(Node *&curr_node);
  void two_child_remove(Node *&curr_node);
  Node *&rightmost_child(Node *&curr_node);
  void rotate_right(Node *&x);
  void rotate_left(Node *&x);
  void rotate_left_right(Node *&x);
  void rotate_right_left(Node *&x);

  // Access functions
  int height(const Node *node) {
    if (!node)
      return -1;
#if AUTO_HEIGHT
    return max(height(node->left), height(node->right)) + 1;
#else
    return node->height;
#endif
  }
  int bf(const Node *node) {
    if (node)
      return height(node->left) - height(node->right);
    return 0;
  }

public:
  AvlTree() : root(NULL) {}
  ~AvlTree() { clear(); }

  void print() {
    std::cout << "In-order: ";
    traverse_inorder(root);
    std::cout << std::endl;
    std::cout << "Pre-order: ";
    traverse_preorder(root);
    std::cout << std::endl;
  }
  void insert(const T &x) { insert(x, root); }
  void remove(const T &x) { remove(x, root); }
  void clear() { clear(root); }
};

template <typename T>
void AvlTree<T>::traverse_preorder(Node *curr_node) {
  if (curr_node) {
    std::cout << curr_node->key << " ";
    traverse_preorder(curr_node->left);
    traverse_preorder(curr_node->right);
  }
}

template <typename T>
void AvlTree<T>::traverse_inorder(Node *curr_node) {
  if (curr_node) {
    traverse_inorder(curr_node->left);
    std::cout << curr_node->key << " ";
    traverse_inorder(curr_node->right);
  }
}

template <typename T>
void AvlTree<T>::clear(Node *curr_node) {
  if (curr_node) {
    clear(curr_node->left);
    clear(curr_node->right);
    delete curr_node;
  }
}

template <typename T> const T &max(const T &a, const T &b) {
  if (a > b)
    return a;
  else
    return b;
}

template <typename T> void AvlTree<T>::insert(const T &x, Node *&t) {
  if (t == NULL) {
    t = new Node(x, 0, nullptr, nullptr);
    return;
  }
  if (x < t->key) {
    // std::cout << x << " is smaller than " << t->key << std::endl;
    insert(x, t->left);
    if (bf(t) == 2) {
      if (bf(t->left) == 1)
        rotate_right(t);
      else
        rotate_left_right(t);
    }
  } else if (x > t->key) {
    // std::cout << x << " is larger than " << t->key << std::endl;
    insert(x, t->right);
    if (bf(t) == -2) {
      if (bf(t->right) == -1)
        rotate_left(t);
      else
        rotate_right_left(t);
    }
  }
  t->height = max(height(t->left), height(t->right)) + 1;
}

template <typename T> void AvlTree<T>::remove(const T &x, Node *&t) {
  if (t) {
    if (x == t->key) {
      do_removal(t);
    } else if (x < t->key) {
      remove(x, t->left);
    } else {
      remove(x, t->right);
    }

    if (!t) return;

    t->height = max(height(t->left), height(t->right)) + 1;

    std::cout << "Checking bf of " << t->key << ": " << bf(t) << std::endl;
    if (bf(t) == 2) {
      std::cout << "Checking bf of subnode " << t->left->key << ": " << bf(t->left) << std::endl;
      if (bf(t->left) == 1)
        rotate_right(t);
      else // favor double rotation
        rotate_left_right(t);
    } else if (bf(t) == -2) {
      std::cout << "Checking bf of subnode " << t->right->key << ": " << bf(t->right) << std::endl;
      if (bf(t->right) == -1)
        rotate_left(t);
      else
        rotate_right_left(t);
    }
  }
}

template <typename T> void AvlTree<T>::do_removal(Node *&curr_node) {
  if (curr_node->left == NULL && curr_node->right == NULL)
    no_child_remove(curr_node);
  else if (curr_node->left != NULL && curr_node->right != NULL)
    two_child_remove(curr_node);
  else
    one_child_remove(curr_node);
}

template <typename T> void AvlTree<T>::no_child_remove(Node *&curr_node) {
  std::cout << "No child remove " << curr_node->key << std::endl;
  Node *temp = curr_node;
  curr_node = NULL;
  delete temp;
}

template <typename T> void AvlTree<T>::one_child_remove(Node *&curr_node) {
  std::cout << "One child remove " << curr_node->key << std::endl;
  Node *temp = curr_node;
  if (curr_node->left == NULL)
    curr_node = curr_node->right;
  else
    curr_node = curr_node->left;
  delete temp;
}

template <typename T> void AvlTree<T>::two_child_remove(Node *&curr_node) {
  std::cout << "Two child remove " << curr_node->key << std::endl;
  Node *&iop = rightmost_child(curr_node->left);
  curr_node->key = iop->key;
  // do_removal(iop); // Error - doesn't update heights!
  remove(iop->key, curr_node->left);
}

template <typename T>
typename AvlTree<T>::Node *&AvlTree<T>::rightmost_child(Node *&curr_node) {
  if (curr_node->right == NULL)
    return curr_node;
  return rightmost_child(curr_node->right);
}

template <typename T>
void AvlTree<T>::rotate_right(Node *&x) {
  std::cout << "Rotate right " << x->key << std::endl;
  Node *y = x->left;
  x->left = y->right;
  y->right = x;
  x = y;

  // Height update
  y->right->height = max(height(y->right->left), height(y->right->right)) + 1;
  y->height = max(height(y->left), height(y->right)) + 1;
}

template <typename T>
void AvlTree<T>::rotate_left(Node *&x) {
  std::cout << "Rotate left " << x->key << std::endl;
  Node *y = x->right;
  x->right = y->left;
  y->left = x;
  x = y;

  // Height update
  y->left->height = max(height(y->left->left), height(y->left->right)) + 1;
  y->height = max(height(y->left), height(y->right)) + 1;
}

template <typename T>
void AvlTree<T>::rotate_left_right(Node *&x) {
  rotate_left(x->left);
  rotate_right(x);
}

template <typename T>
void AvlTree<T>::rotate_right_left(Node *&x) {
  rotate_right(x->right);
  rotate_left(x);
}
