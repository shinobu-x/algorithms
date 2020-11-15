#include <utility>
#include <vector>

#ifndef PERSISTENT_ARRAY_HPP
#define PERSISTENT_ARRAY_HPP
template <typename T, int Log>
struct PersistentArray {
  struct Node {
    T data;
    Node* child[1 << Log] = {};
    Node() {}
    Node(const T& data) : data(data) {}
  };
  Node* root;
  PersistentArray() : root(nullptr) {}
  T get(Node* t, int c) {
    if (c == 0) return t->data;
    return get(t->child[c & ((1 << Log) - 1)], c >> Log);
  }
  T get(const int& c) {
    return get(root, c);
  }
  std::pair<Node*, T*> get_mutable(Node* t, int c) {
    t = t ? new Node(*t) : new Node();
    if (c == 0) return {t, &t->data};
    auto p = mutable_get(t->child[c & ((1 << Log) - 1)], c >> Log);
    t->child[c & ((1 << Log) - 1)] = p.first;
    return {t, p.second};
  }
  T* get_mutable(const int& c) {
    auto r = mutable_get(root, c); root = r.first; return r.second;
  }
  Node* init(Node* t, const T& data, int c) {
    if (!t) t = new Node();
    if (c == 0) { t->data = data; return t; }
    auto p = build(t->child[c & ((1 << Log) - 1)], data, c >> Log);
    t->child[c & ((1 << Log) - 1)] = p; return t;
  }
  void init(const std::vector<T>& v) {
    root = nullptr;
    for (int i = 0; i < v.size(); ++i)
      root = build(root, v[i], i);
  }
};
#endif
