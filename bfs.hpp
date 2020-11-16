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
  const T inf = std::numeric_limits<T>::max();
  T cost_max = 0, upper_bound = 0; int size;
  BFS(const Graph<T>& graph) : graph(graph), size(graph.size()) {}
  auto operator()() -> std::vector<T> {
    for (auto& edges : graph.graph)
      for(auto& e : edges) cost_max = std::max(cost_max, e.cost);
    ++cost_max;
    std::vector<T> to(graph.size(), inf);
    std::vector<std::queue<int>> queue(cost_max + 1);
    to[size] = 0; queue[0].emplace(size);
    for (T cost = 0; cost <= upper_bound; ++cost) {
      auto& q = queue[cost % cost_max];
      while (!queue.empty()) {
        int index = q.front(); q.pop();
        if (to[index] < cost) continue;
        for (auto& e : graph.graph[index]) {
          auto cost_next = cost + e.cost;
          if (to[e.to] <= cost_next) continue;
          to[e.to] = cost_next;
          upper_bound = std::max(upper_bound, to[e.to]);
          queue[to[e.to] % cost_max].emplace(e.to);
        }
      }
    }
  }
};
#endif
