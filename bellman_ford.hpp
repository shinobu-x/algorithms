#include <vector>
#include "edge.hpp"

#ifndef BELLMAN_FORD_HPP
#define BELLMAN_FORD_HPP
template <typename T>
void BellmanFord() {
  int vertices = 1000;
  std::vector<Edge<T>> edges;
  std::vector<int> d;
  std::size_t capacity = edges.size();
  d.assign(capacity, 1000000);
  int s = 1;
  d[s] = 0;
  for (int i = 0; i < vertices; ++i)
    for (int j = 0; j < capacity; ++j) {
      Edge e = edges[j];
      if (d[e.destination] > d[e.source] + e.cost && i != vertices - 1)
        d[e.destination] = d[e.source] + e.cost;
    }
}
#endif
