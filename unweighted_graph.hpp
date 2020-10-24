#include <vector>
#include "edge.hpp"

#ifndef UNWEIGHTED_GRAPH_HPP
#define UNWEIGHTED_GRAPH_HPP
template <typename T>
struct UnWeightedGraph : std::vector<std::vector<Edge<T>>> {
  bool is_directed;
  explicit UnWeightedGraph(int size, bool is_directed) :
    std::vector<std::vector<Edge<T>>>(size), is_directed(is_directed) {}
  void add_edge(int source, int destination) {
    std::vector<std::vector<Edge<T>>
      >::operator[](source).emplace_back(destination, 0);
    if (!is_directed) {
      std::vector<std::vector<Edge<T>>
        >::operator[](destination).emplace_back(source, 0);
    }
  }
};
#endif
