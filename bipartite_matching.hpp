#include <vector>

#ifndef BIPARTITE_MATCHING_HPP
#define BIPARTITE_MATCHING_HPP
template <typename T = int>
struct BipartiteMatching {
  std::vector<std::vector<T>> graph;
  std::vector<T> is_visited, used, matched;
  T t;
  BipartiteMatching(T vertices) : graph(vertices), is_visited(vertices, 1),
    used(vertices, 0), matched(vertices, -1), t(0) {}
  void add_edge(int u, int v) {
    graph[u].push_back(v), graph[v].push_back(u);
  }
  bool dfs(int index) {
    used[index] = t;
    for (auto& destination : graph[index]) {
      int is_matched = matched[destination];
      if (is_visited[destination] == 0) continue;
      if (is_matched == -1 || (used[is_matched] != t && dfs(is_matched))) {
        matched[index] = destination, matched[destination] = index;
        return true;
      }
    }
    return false;
  }
  auto run(int index = 1) -> T {
    T r = 0;
    for (int i = 0; i < graph.size(); ++i) {
      if (is_visited[i] == 0) continue;
      if (matched[i] == -1) ++t, r += dfs(i);
    }
  }
};
#endif
