#include <vector>
#include "edge.hpp"
#ifndef BELLMAN_FORD_HPP
#define BELLMAN_FORD_HPP
template <typename T>
struct BellmanFord {
  const int inf = std::numeric_limits<T>::max();
  std::vector<Edge<T>> edges; std::vector<T> to; int v; int size;
  BellmanFord(const std::vector<Edge<T>>& edges, int v, int size) :
    edges(edges), to(v, inf), v(v), size(size) {}
  auto operator()() -> std::vector<T> {
    to[size] = 0;
    for (int i = 0; i < v - 1; ++i)
      for (auto& e : edges) {
        if (to[e.from] == inf) continue;
        to[e.to] = std::min(to[e.to], to[e.from] + e.cost);
      }
    for (auto& e : edges) {
      if (to[e.from] == inf) continue;
      if (to[e.from] + e.cost < to[e.to]) return std::vector<T>();
    } return to;
  }
};
#endif
