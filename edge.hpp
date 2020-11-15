#include <utility>
#include <vector>

#ifndef EDGE_HPP
#define EDGE_HPP
template <typename T>
struct Edge {
  int from, to; T cost; int index;
  Edge(int from, int to, T cost = 1, int index = -1) : from(from), to(to),
    cost(cost), index(index) {}
  operator int() const {return to;}
};
#endif
