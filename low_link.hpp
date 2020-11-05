#include <algorithm>
#include <utility>
#include <vector>
#include "union_find.hpp"

#ifndef LOW_LINK_HPP
#define LOW_LINK_HPP
struct LowLink {
  UnionFind union_find;
  std::vector<std::vector<int>> graph;
  std::vector<int> visited, ord, low;
  LowLink(std::size_t vertices) : union_find(vertices), graph(vertices),
    ord(vertices), low(vertices) {}
  void add_edge(int x, int y) {
    graph[x].push_back(y); graph[y].push_back(x);
  }
  void dfs(int index, int k, int parent = -1) {
    visited[index] = true, ord[index] = low[index] = ++k;
    for (auto& i : graph[index]) {
      if (!visited[i]) {
        dfs(i, k, index);
        low[index] = std::min(low[index], low[i]);
        if (ord[index] >= low[i]) union_find.unite(index, i);
      }
      else if (i != parent) low[index] = std::min(low[index], ord[i]);
    }
  }
  void run() {
    int k = 0;
    for (int index = 0; index < graph.size(); ++index) {
      if (!visited[index]) {
        dfs(index, k, -1);
      }
    }
  }
};
#endif
