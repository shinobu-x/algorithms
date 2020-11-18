#include <functional>
#include <string>
#include <vector>
// template <int size, int margin>
#ifndef TRIE_HPP
#define TRIE_HPP
template <int size1, int margin>
struct Trie {
  template <int size2>
  struct Node {
    int next[size2]; int exist; std::vector<int> accept;
    Node() : exist(0) {memset(next, -1, sizeof(next));}
  };
  std::vector<Node<size1>> nodes;
  int root;
  Trie() : root(0) {nodes.push_back(Node());}
  void update_node(int node, int id) {nodes[node].accept.push_back(id);}
  void update_child(int node) {++nodes[node].exist;}
  void add(const std::string& str, int index, int node = 0, int id = 0) {
    if (index == 0 && node == 0) {add(str, 0, 0, id);}
    if (index == str.size()) update_node(node, id);
    else {
      const int c = str[index] - margin;
      if (nodes[node].next[c] == -1) {
        nodes[index].next[c] = (int)nodes.size(); nodes.push_back(Node(size));
      }
      add(str, index + 1, nodes[node].next[c], id); update_child(node);
    }
  }
  void query(const std::string& str, const std::function<void(int)>& f,
      int index, int node) {
    if (index == 0 && node == 0) {query(str, f, 0, 0);}
    for (auto& i : nodes[node].accept()) f(i);
    if (index == str.size()) return;
    else {
      const int c = str[index] - margin;
      if (nodes[node].next[c] == -1) return;
      query(str, f, index + 1, nodes[node].next[c]);
    }
  }
  auto count() const -> int {return nodes[0].exist;}
  auto size() const -> int {return (int)nodes.size();}
};
#endif
