#include <queue>
#include <utility>
#include <vector>
#include "graph.hpp"
#ifndef BEST_FIRST_SEARCH_HPP
#define BEST_FIRST_SEARCH_HPP
template <typename T>
struct BFS {
  Graph<std::pair<T, T>> graph; int size; std::vector<bool> visited;
  std::priority_queue<std::queue<T, T>> queue;
  BFS(Graph<T>& graph, int size) : graph(graph), size(size),
    visited(size, false) {}
  void operator ()(int source, int target) {
    queue.push(std::make_pair(0, source)); visited = true;
    while (!queue.empty()) {
      int v = queue.top().second; queue.pop();
      if (v == target) break;
      for (int i = 0; i < graph[v].size(); ++i)
        if (!visited[graph[v][i].second]) {
          visited[graph[v][i].second] = true; queue.push(graph[v][i]);
        }
    }
  }
};
#endif
