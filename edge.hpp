#include <utility>

#ifndef EDGE_HPP
#define EDGE_HPP
template <typename T>
struct Edge {
  std::pair<int, int> direction;
  T cost;
  Edge(int source, int destination, T cost) :
    direction(source, destination), cost(cost) {}
  Edge(int destination, T cost) :
    direction(-1, destination), cost(cost) {}
  Edge &operator=(const int &vertex) {
    direction.second = vertex;
    return *this;
  }
  operator int () const {
    return direction.second;
  }
};
#endif
