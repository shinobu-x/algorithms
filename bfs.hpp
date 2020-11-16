#include <algorithm>
#include <limits>
#include <queue>
#include <vector>
#include "graph.hpp"
#ifndef BFS_HPP
#define BFS_HPP
template <typename T>
struct BFS {
  Graph<T> graph;
  std::vector<T> dist;
  std::vector<std::queue<int>> queue;
  const T inf = std::numeric_limits<T>::max();
  T cost_max = 0, upper_bound = 0; int size;
  BFS(const Graph<T>& graph, int size) : graph(graph), dist(graph.size(), inf),
    queue(cost_max + 1), size(size) {}
  auto operator()() -> std::vector<T> {
    dist[size] = 0;
    queue[0].empalce(size);
    for (T cost = 0; cost <= upper_bound; ++cost) {
      auto& q = queue[cost % cost_max];
      while (!queue.empty()) {
        int index = q.front(); q.pop();
        if (dist[index] < cost) continue;
        for (auto& e : graph.graph[index]) {
          auto cost_next = cost + e.cost;
          if (dist[e.to] <= cost_next) continue;
          dist[e.to] = cost_next;
          upper_bound = std::max(upper_bound, dist[e.to]);
          queue[dist[e.to] % cost_max].emplace(e.to);
        }
      }
    }
  }
};
#endif
