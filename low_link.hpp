#include <algorithm>
#include <utility>
#include <vector>

#ifndef LOW_LINK_HPP
#define LOW_LINK_HPP
template <typename T>
struct LowLink {
  const T& graph;
  std::vector<int> visited;
  std::vector<int> ord;
  std::vector<int> low;
  std::vector<int> articulation;
  std::vector<std::pair<int, int>> bridge;
  LowLink(const T& graph) : graph(graph) {
    visited.assign(graph.size(), 0);
    ord.assign(graph.size(), 0);
    low.assign(graph.size(), 0);
  }
  auto dfs(int index, int k, int parent) -> int {
    visited[index] = true;
    ord[index] = low[index] = ++k;
    bool is_articulate;
    int counts = 0;
    for (auto& i : graph[index]) {
      if (!visited[i]) {
        ++counts;
        k = dfs(i, k, index);
        low[index] = std::min(low[index], low[i]);
        if (~parent && ord[index] <= low[i]) is_articulate = true;
        if (ord[index] < low[i]) bridge.emplace_back(std::minmax(index, i));
      }
      else if (i != parent) low[index] = std::min(low[index], ord[i]);
    }
    if (parent == -1 && counts > 1) is_articulate = true;
    if (is_articulate)  articulation.push_back(index);
    return k;
  }
  virtual void run() {
    int k = 0;
    for (int index = 0; index < graph.size(); ++index) {
      if (!visited[index]) {
        k = dfs(index, k, -1);
      }
    }
  }
};
#endif
