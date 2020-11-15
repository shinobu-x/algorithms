#include <algorithm>
#include <utility>
#include <vector>

#include "graph.hpp"
#include "union_find.hpp"

#ifndef LOW_LINK_HPP
#define LOW_LINK_HPP
template <typename T>
struct LowLink : Graph<T> {
  UnionFind union_find; Graph<T> graph;
  std::vector<Edge<T>> bridge; std::vector<T> visited, ord, low;
  LowLink(int size) : union_find(size), graph(size), ord(size), low(size) {}
  void dfs(int index, int i, int parent = -1) {
    visited[index] = true; ord[index] = low[index] = ++i;
    for (auto& to : graph.graph[index]) {
      if (!visited[to]) {
        dfs(to, i, index); low[index] = std::min(low[index], low[to]);
        if (ord[index] >= low[to]) union_find.unite(index, to);
        else bridge.emplace_back(to);
      } else low[index] = std::min(low[index], ord[to]);
    }
  }
  virtual void init() {
    int i = 0;
    for (int j = 0; j < graph.size(); ++j) if (!visited[j]) dfs(j, i, -1);
  }
};
#endif
