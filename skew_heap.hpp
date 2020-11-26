// https://en.wikipedia.org/wiki/Skew_heap
#include <functional>
#include <utility>
#ifndef SKEW_HEAP_HPP
#define SKEW_HEAP_HPP
template <typename T, typename U = T>
struct SkewHeap {
  struct Node {T key; U lazy; Node* l, r;};
  const bool x;
  const std::function<T(T, U)> g; const std::function<U(U, U)> h;
  SkewHeap(bool x = false) : g([](const T& a, const U& b) {return a + b;}),
    h([](const U& a, const U& b) {return a + b;}), x(x) {}
  SkewHeap(const std::function<T(T, U)>& g, const std::function<U(U, U)>& h,
      bool x) : g(g), h(h), x(x) {}
  auto propagate(Node* n) -> Node* {
    if (n->lazy != 0) {
      if (n->l) n->l->lazy = h(n->l->lazy, n->lazy);
      if (n->r) n->r->lazy = h(n->r->lazy, n->lazy);
      n->key = g(n->key, n->lazy); n->lazy = 0;
    } return n;
  }
  auto merge(Node* u, Node* v) -> Node* {
    if (!u || !v) return u ? u : v;
    propagate(u); propagate(v);
    if((u->key > v->key) ^ x) std::swap(u, v);
    u->r = merge(v, u->r); std::swap(u->l, u->r);
    return u;
  }
  void push(Node*& root, const T& key) {
    root = merge(root, new Node({key, 0, nullptr, nullptr}));
  }
  auto top(Node* root) -> T {return propagate(root)->key;}
  auto pop(Node*& root) -> T {
    T top = propagate(root)->key; root = merge(root->l, root->r);
    return top;
  }
  auto empty(Node* root) const -> bool {return !root;}
  void add(Node* root, const U& lazy) {
    if (root) {root->lazy = h(root->lazy, lazy); propagate(root);}
  }
  Node* heap() {return nullptr;}
};
#endif
