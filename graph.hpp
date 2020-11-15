#include <vector>
#include "edge.hpp"

#ifndef GRAPH_HPP
#define GRAPH_HPP
template <typename T>
struct Graph {
  std::vector<std::vector<Edge<T>>> graph;
  int edge;
  Graph() = default; explicit Graph(int size) : graph(size), edge(0) {}
  auto size() const -> int {return graph.size();}
  void add_edge(int from, int to, T cost = 1) {
    graph[from].emplace_back(from, to, cost, edge);
    graph[to].emplace_back(to, from, cost, ++edge);
  }
  void add_directed_edge(int from, int to, T cost = 1) {
    graph[from].emplace_back(from, to, cost, ++edge);
  }
};
#endif
