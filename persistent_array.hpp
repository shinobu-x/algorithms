#include <utility>

#ifndef PERSISTENT_ARRAY_HPP
#define PERSISTENT_ARRAY_HPP
template <typename T, int log>
struct PersistentArray {
  struct Node {
    T data;
    Node* child[1 << log] = {};
    Node() {}
    Node(const T& data) : data(data) {}
  };
  Node* root;
  PersistentArray() : root(nullptr) {}
  T get(Node* t, int c) {
    if (c == 0) return t->data;
    return get(t->child[c & ((1 << log) - 1)], c >> log);
  }
  T get(const int& c) {
    return get(root, c);
  }
  std::pair<Node*, T*> mutable_get(Node* t, int c) {
    t = t ? new Node(*t) : new Node();
    if (c == 0) return {t, &t->data};
    auto p = mutable_get(t->child[c & ((1 << log) - 1)], c >> log);
    t->child[c & ((1 << log) - 1)] = p.first;
    return {t, p.second};
  }
};
#endif
