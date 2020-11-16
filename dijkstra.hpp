#include <functional>
#include <limits>
#include <queue>
#include <vector>
#include "graph.hpp"
#ifndef DIJKSTRA_HPP
#define DIJKSTRA_HPP
template <typename T>
struct Dijkstra {
  template <typename U>
  struct ShortistPath {std::vector<U> to; std::vector<int> from, id;};
  Graph<T> graph;
  const int inf = std::numeric_limits<T>::max();
  std::priority_queue<std::pair<T, int>, std::vector<std::pair<T, int>>,
    std::greater<>> queue;
  int size;
  Dijkstra(const Graph<T>& graph, int size) : graph(graph), size(size) {}
  auto operator()() -> ShortistPath<T> {
    std::vector<T> to(graph.size(), inf);
    std::vector<int> from(graph.size(), -1), id(graph.size(), -1);
    to[size] = 0; queue.emplace(to[size], size);
    while (!queue.empty()) {
      T cost; int index; std::tie(cost, index) = queue.top(); queue.pop();
      if (to[index] < cost) continue;
      for (auto& e : graph.graph[index]) {
        auto cost_next = cost + e.cost;
        if (to[e.to] <= cost_next) continue;
        to[e.to] = cost_next; from[e.to] = index; id[e.to] = e.index;
        queue.emplace(to[e.to], e.to);
      }
    }
  }
};
#endif
