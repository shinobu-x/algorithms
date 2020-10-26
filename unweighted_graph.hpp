#include <vector>
#include "edge.hpp"

#ifndef UNWEIGHTED_GRAPH_HPP
#define UNWEIGHTED_GRAPH_HPP
template <typename T = int>
using UnWeightedGraph = std::vector<std::vector<T>>;
#endif
