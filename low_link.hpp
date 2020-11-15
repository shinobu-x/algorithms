#include <algorithm>
#include <utility>
#include <vector>

#include "graph.hpp"
#include "union_find.hpp"

#ifndef LOW_LINK_HPP
#define LOW_LINK_HPP
template <typename T>
struct LowLink : Graph<T> {
  UnionFind union_find; Graph<T> graph; std::vector<T> visited, ord, low;
  LowLink(int size) : union_find(size), graph(size), ord(size), low(size) {}
  void dfs(int index, int i, int parent = -1) {
    visited[index] = true; ord[index] = low[index] = ++i;
    for (auto& v : graph.graph[index]) {
      if (!visited[v]) {
        dfs(v, i, index); low[index] = std::min(low[index], low[v]);
        if (ord[index] >= low[v]) union_find.unite(index, v);
      } else if (v != parent) low[index] = std::min(low[index], ord[v]);
    }
  }
  void run() {
    int i = 0;
    for (int j = 0; j < graph.size(); ++j) if (!visited[j]) dfs(j, i, -1);
  }
};
#endif
