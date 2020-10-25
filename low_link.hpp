#include <algorithm>
#include <utility>
#include <vector>

#ifndef LOW_LINK_HPP
#define LOW_LINK_HPP
template <typename T>
struct LowLink {
  const T& graph;
  std::vector<int> used;
  std::vector<int> ord;
  std::vector<int> low;
  std::vector<int> articulation;
  std::vector<std::pair<int, int>> bridge;
  LowLink(const T& graph) : graph(graph) {}
  auto dfs(int index, int k, int parent) -> int {
    used[index] = true;
    ord[index] = ++k;
    low[index] = ord[index];
    bool is_articulate;
    int counts = 0;
    for (auto& destination : graph[index]) {
      if (!used[destination]) {
        ++counts;
        k = dfs(destination, k, index);
        low[index] = std::min(low[index], low[destination]);
        if (ord[index] < low[destination]) {
          bridge.emplace_back(std::minmax(index, (int)destination));
        } else if (destination != parent) {
          low[index] = std::min(low[index], ord[destination]);
        }
      }
    }
    if (is_articulate) {
      articulation.push_back(index);
    }
    return k;
  }
  virtual void build() {
    used.assign(graph.size(), 0);
    ord.assign(graph.size(), 0);
    low.assign(graph.size(), 0);
    int k = 0;
    for (int index = 0; index < graph.size(); ++index) {
      if (!used[index]) {
        k = dfs(index, k, -1);
      }
    }
  }
};
#endif
