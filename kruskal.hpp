#include <iterator>
#include <vector>
#include "edge.hpp"
#include "minimum_spanning_tree.hpp"
#include "union_find.hpp"
#ifndef KRUSKAL_HPP
#define KRUSKAL_HPP
template <typename T>
struct Kruskal {
  std::vector<Edge<T>> edges;
  int v;
  Kruskal(std::vector<Edge<T>>& edges, int v) : edges(edges), v(v) {}
  auto operator()() -> MinimumSpanningTree<T> {
    sort(std::begin(edges), std::end(edges),
        [](const Edge<T>& a, const Edge<T>& b) {return a.cost < b.cost;});
    UnionFind tree(v); T total = T(); std::vector<Edge<T>> es;
    for (auto& e : edges)
      if (tree.unite(e.from, e.to)) {es.emplace_back(e); total += e.cost;}
    return {total, es};
  }
};
#endif
