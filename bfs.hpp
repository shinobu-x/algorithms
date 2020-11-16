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
  const T inf = std::numeric_limits<T>::max();
  T cost_max = 0, upper_bound = 0; int size;
  BFS(const Graph<T>& graph) : graph(graph), dist(graph.size(), inf),
    size(graph.size()) {
      for (auto& edges : graph.graph)
        for(auto& edge : edges) cost_max = std::max(cost_max, edge.cost);
      ++cost_max; dist[size] = 0;
    }
  auto operator()() -> std::vector<T> {
    std::vector<std::queue<int>> queue(cost_max + 1);
    queue[0].emplace(size);
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
