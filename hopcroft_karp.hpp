#include <queue>
#include <vector>

#ifndef HOPCROFT_KARP_HPP
#define HOPCROFT_KARP_HPP
template <typename T = int>
struct HopcroftKarp {
  std::vector<std::vector<T>> graph;
  std::vector<T> to, matched;
  std::vector<bool> is_visited, used;
  HopcroftKarp(T vertices_x, T vertices_y) : graph(vertices_x),
  matched(vertices_y, -1), used(vertices_x) {
    to.assign(graph.size(), -1), is_visited.assign(graph.size(), false); }
  void add_edge(T u, T v) {
    graph[u].push_back(v);
  }
  void bfs() {
    std::queue<T> queue;
    for (int i = 0; i < graph.size(); ++i)
      if (!used[i])
        queue.emplace(i), to[i] = 0;
    while (!queue.empty()) {
      int index = queue.front(); queue.pop();
      for (auto& i : graph[index]) {
        int v = matched[i];
        if (v >= 0 && to[v] == -1)
            to[i] = to[index] + 1, queue.emplace(v);
      }
    }
  }

  bool dfs(int index) {
    is_visited[index] = true;
    for (auto& destination : graph[index]) {
      int is_matched = matched[destination];
      if (is_matched < 0 || (!is_visited[is_matched] &&
            to[destination] == to[index] + 1 && dfs(is_matched)))
        matched[destination] = index, used[index] = true; return true;
    }
    return false;
  }

  auto run() -> int {
    int r = 0;
    while (true) {
      bfs();
      int flow = 0;
      for (int i = 0; i < graph.size(); ++i)
        if (!used[i] && dfs(i)) ++flow;
      if (flow == 0) return r;
      r += flow;
    }
  }
};
#endif
