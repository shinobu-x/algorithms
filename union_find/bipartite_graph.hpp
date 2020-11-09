#include <vector>
#include "union_find.hpp"

#ifndef BIPARTITE_GRAPH_HPP
#define BIPARTITE_GRAPH_HPP
struct BipartiteGraph : UnionFind {
  std::vector<int> color;
  BipartiteGraph(int vertices) : color(vertices + vertices, -1),
    UnionFind(vertices + vertices) {}
  auto bipartite_graph() {
    for (int i = 0; i < color.size() / 2; ++i) {
      int a = find(i); int b = find(i + (int)color.size() / 2);
      if (a == b) return false;
      if (color[a] < 0) color[a] = 0, color[b] = 1;
    } return true;
  }
  auto operator[](int k) -> bool {
    return (bool)color[find(k)];
  }
};
#endif
