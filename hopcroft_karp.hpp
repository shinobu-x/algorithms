#include <queue>
#include <vector>

#ifndef HOPCROFT_KARP_HPP
#define HOPCROFT_KARP_HPP
template <typename T>
struct HopcroftKarp {
  std::vector<std::vector<T>> graph;
  std::vector<T> dist, matched;
  std::vector<bool> used, visited;
  HopcroftKarp(T n, T m) : graph(n), matched(m, -1), used(n) {}
  void add_edge(T u, T v) { graph[u].push_back(v); }
  auto dfs(int index) -> bool {
    visited[index] = true;
    for (auto& i : graph[index]) {
      int j = matched[i];
      if ( j < 0 || (!visited[j] && dist[j] == dist[index] + 1 && dfs(j)))
        matched[i] = index, used[index] = true; return true;
    } return false;
  }
  void bfs() {
    dist.assign(graph.size(), -1); std::queue<int> queue;
    for (int i = 0; i < graph.size(); ++i)
      if (!used[i]) { queue.emplace(i); dist[i] = 0; }
    while (!queue.empty()) {
      int i = queue.front(); queue.pop();
      for (auto& j : graph[i]) {
        int k = matched[j];
        if (k >= 0 && dist[k] == -1)
          dist[k] = dist[i] + 1; queue.emplace(k);
      }
    }
  }
  auto run() -> int {
    int r = 0;
    while (true) {
      bfs(); visited.assign(graph.size(), false); int flow = 0;
      for (int i = 0; i < graph.size(); ++i)
        if (!used[i] && dfs(i)) ++flow;
      if (flow == 0) return r;
      r += flow;
    }
  }
};
#endif
