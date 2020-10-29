#include <utility>
#include <vector>

#ifndef EDGE_HPP
#define EDGE_HPP
template <typename T>
struct Edge {
  std::pair<int, int> direction;
  int cost;
  Edge(int source, int destination, int cost) :
    direction(source, destination), cost(cost) {}
  Edge(int destination, int cost) :
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
