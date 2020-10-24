#include "unweighted_graph.hpp"

#ifndef WEIGHTED_GRAPH_HPP
#define WEIGHTED_GRAPH_HPP
template <typename T>
struct WeightedGraph : UnWeightedGraph<T> {
  explicit WeightedGraph(int size, bool is_directed) :
    UnWeightedGraph<T>(size, is_directed) {}
  void add_edge(int source, int destination, T cost) {
    UnWeightedGraph<T>::operator[](source).emplace_back(destination, cost);
    if (!UnWeightedGraph<T>::is_directed) {
      UnWeightedGraph<T>::operator[](destination).emplace_back(source, cost);
    }
  }
};
#endif
