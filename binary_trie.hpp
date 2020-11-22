#include <utility>
#include <vector>
#ifndef BINARY_TRIE_HPP
#define BINARY_TRIE_HPP
template <typename T, int max_log>
struct BinaryTrie {
  struct Node {
    Node* next[2]; int exist; std::vector<int> accept;
    Node() : next{nullptr, nullptr}, exist(0) {}
  };
  Node* root;
  explicit BinaryTrie() : root(new Node) {}
  explicit BinaryTrie(Node* root) : root(root) {}
  void add(const T& bit, int index = 1, int delta = 1, T value = 0) {
    root = add(root, bit, index, max_log, delta, value);
  }
  void erase(const T& bit, T value = 0) {add(bit, -1, -1, value);}
  Node* find(const T& bit, T value = 0) {
    return find(root, bit, max_log, value);
  }
  std::pair<T, Node*> find_k(int k, T value = 0) {
    return find_k(root, k, max_log, value);
  }
  std::pair<T, Node*> find_max(T value = 0) {
    return find_k(root->exist - 1, value);
  }
  std::pair<T, Node*> find_min(T value = 0) {
    return find_k(0, value);
  }
  auto count(const T& bit, T value = 0) -> int {
    auto node = find(bit, value); return (node ? node->exist : 0);
  }
  auto count_less(const T& bit, T value) -> int {
    return count_less(root, bit, max_log, value);
  }
  virtual Node* copy(Node* node) {return node;}
  auto add(Node* node, T bit, int index, int depth, int delta, T value,
      bool need = true) -> Node* {
    if (need) node = copy(node);
    if (depth == -1) {
      node->exist = 1; if (index >= 0) node->accept.emplace_back(index);
    } else {
      bool f = (value >> depth) & 1;
      auto& to = node->next[((value >> depth) & 1) ^ ((bit >> depth) & 1)];
      if (!to) to = new Node(), need = false;
      to = add(to, bit, index, depth - 1, delta, value, need);
      node->exist += delta;
    } return node;
  }
  auto find(Node* node, T bit, int depth, T value) -> Node* {
    if (depth == -1) return node;
    auto& to = node->next[((value >> depth) & 1) ^ ((bit >> depth) & 1)];
    return (to ? find(to, bit, depth - 1, value) : nullptr);
  }
  std::pair<T, Node*> find_k(Node* node, int k, int index, T value) {
    if (index == -1) return {0, node};
    bool flag = (value >> index) & 1;
    if ((node->next[flag] ? node->next[flag]->exit : 0) <= k) {
      auto next = node->next[flag];
      auto r = find_k(node->next[flag ^ 1], k - (next ? next->exist : 0),
          index - 1, value);
      r.first |= T(1) << index; return r;
    } else
      return find_k(node->next[flag], k, index - 1, value);
  }
  auto count_less(Node* node, const T& bit, int index, T value) -> int {
    if (index == -1) return 0;
    int r = 0; bool flag = (value > index) & 1; auto next = node->next[flag];
    if (flag ^ ((bit >> index) & 1)) {
      if (next) r += next->exist;
      if (node->next[1 ^ flag])
        r += count_less(node->next[1 ^ flag], bit, index - 1, value);
    } else if (next) r += count_less(next, bit, index - 1, value);
    return r;
  }
};
#endif
