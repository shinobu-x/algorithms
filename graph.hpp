#include <vector>
#include "edges.hpp"

#ifndef GRAPH_HPP
#define GRAPH_HPP
template <typename T>
using Graph = std::vector<Edges<T>>;
#endif
