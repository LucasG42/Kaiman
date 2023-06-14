#ifndef KAIMAN_H_
#define KAIMAN_H_

#include <iostream>
#include <stack>
#include <vector>

template <typename Key, typename Value> class Node {
public:
  Key key;
  std::vector<Value> values;
  int height;
  Node(Key key, Value value) {
    (this->values).push_back(value);
    this->key = key;
    this->height = 1;
  }
  Node<Key, Value> *right = nullptr;
  Node<Key, Value> *left = nullptr;
};

template <typename T, typename X> class Kaiman {
public:
  Kaiman() { root = nullptr; }
  Kaiman<T, X>(const Kaiman<T, X> &t) = delete;
  Kaiman<T, X> &operator=(const Kaiman<T, X> &t) = delete;

  void insert(T key, X value) {
    ++size_;
    root = insert(root, key, value);
  }
  void clear() { root = clear(root); }
  void erase(T key) { root = erase(root, key); }
  std::vector<X> find(T key) {
    auto node = root;
    while (node != nullptr && node->key != key) {
      if (node->key > key) {
        node = node->left;
      } else {
        node = node->right;
      }
    }

    if (node != nullptr) {
      return (node->values);
    }
    return std::vector<X>{};
  }
  bool empty() { return root == nullptr; }

  int size() { return size_; };

  ~Kaiman() { root = Clear(root); }

  Node<T, X> *getRoot() { return root; }
  void list() { list(root); }

  class Iterator {
  public:
    std::stack<Node<T, X> *> stack;
    Iterator(Node<T, X> *root) {
      while (root) {
        stack.push(root);
        root = root->left;
      }
    }

    std::vector<X> next() {
      Node<T, X> *t1 = stack.top();
      stack.pop();
      Node<T, X> *t = t1->right;
      while (t) {
        stack.push(t);
        t = t->left;
      }
      return t1->values;
    }

    bool hasNext() {
      if (stack.empty())
        return false;
      return true;
    }
  };

private:
  int size_ = 0;
  Node<T, X> *root{nullptr};
  int Height(Node<T, X> *node) { return (node == nullptr) ? 0 : node->height; }
  int Balance(Node<T, X> *node) {
    return Height(node->right) - Height(node->left);
  }

  void list(Node<T, X> *root) {
    if (root == nullptr) {
      return;
    }
    list(root->left);
    std::cout << root->key << "\n";
    list(root->right);
  }
  Node<T, X> *RightRotation(Node<T, X> *p) {
    Node<T, X> *u = p->left;
    p->left = u->right;
    u->right = p;
    p->height = 1 + std::max(Height(p->left), Height(p->right));
    u->height = 1 + std::max(Height(u->left), Height(u->right));
    return u;
  }
  Node<T, X> *LeftRotation(Node<T, X> *p) {
    Node<T, X> *u = p->right;
    p->right = u->left;
    u->left = p;
    p->height = 1 + std::max(Height(p->right), Height(p->left));
    u->height = 1 + std::max(Height(u->left), Height(u->right));
    return u;
  }
  Node<T, X> *insert(Node<T, X> *p, T key, X value) {
    if (p == nullptr) {
      return new Node<T, X>(key, value);
    }
    if (key == p->key) {
      (p->values).push_back(value);
      return p;
    }
    if (key < p->key) {
      p->left = Insert(p->left, key, value);
    } else {
      p->right = Insert(p->right, key, value);
    }
    p = FixNode(p, key);
    return p;
  }
  Node<T, X> *FixNode(Node<T, X> *p, T key) {
    p->height = 1 + std::max(Height(p->left), Height(p->right));
    int balance = Balance(p);
    if (balance >= -1 && balance <= 1) {
      return p;
    }
    if (balance < -1 && key < p->left->key) {
      p = RightRotation(p);
    } else if (balance < -1 && key > p->left->key) {
      p->left = LeftRotation(p->left);
      p = RightRotation(p);
    } else if (balance > 1 && key > p->right->key) {
      p = LeftRotation(p);
    } else if (balance > 1 && key < p->right->key) {
      p->right = RightRotation(p->right);
      p = LeftRotation(p);
    }
    return p;
  }
  Node<T, X> *clear(Node<T, X> *node) {
    if (node != nullptr) {
      node->left = Clear(node->left);
      node->right = Clear(node->right);
      delete node;
    }
    return nullptr;
  }
  Node<T, X> *remove(Node<T, X> *node, T key) {
    if (node == nullptr)
      return nullptr;
    if (key < node->key)
      node->left = Remove(node->left, key);
    else if (key > node->key)
      node->right = Remove(node->right, key);
    else if (node->right == nullptr) {
      Node<T, X> *child = node->left;
      delete node;
      return child;
    } else
      node->right = RemoveSuccessor(node, node->right);

    node = FixDeletion(node);
    return node;
  }
  Node<T, X> *RemoveSuccessor(Node<T, X> *root, Node<T, X> *node) {
    if (node->left != nullptr)
      node->left = RemoveSuccessor(root, node->left);
    else {
      root->key = node->key;
      Node<T, X> *aux = node->right;
      delete node;
      return aux;
    }

    node = FixDeletion(node);
    return node;
  }
  Node<T, X> *FixDeletion(Node<T, X> *node) {
    node->height = 1 + std::max(Height(node->left), Height(node->right));

    int balance = Balance(node);

    if (balance > 1 && Balance(node->right) >= 0) {
      return LeftRotation(node);
    } else if (balance > 1 && Balance(node->right) < 0) {
      node->right = RightRotation(node->right);
      return LeftRotation(node);
    } else if (balance < -1 && Balance(node->left) <= 0) {
      return RightRotation(node);
    } else if (balance < -1 && Balance(node->left) > 0) {
      node->left = LeftRotation(node->left);
      return RightRotation(node);
    }
    return node;
  }
};

#endif