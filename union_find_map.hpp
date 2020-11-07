#include <map>
#include <utility>
#include <vector>
#include "union_find.hpp"

#ifndef UNION_FIND_MAP_HPP
#define UNION_FIND_MAP_HPP
template <typename T>
struct UnionFindMap {
  std::map<T, int> vertex;
  UnionFind uf;
  UnionFindMap(std::size_t vertices) : uf(vertices) {}
  void make(T x) {
    if (vertex.find(x) == vertex.end()) vertex.insert(std::pair<T, int>(
          x, vertex.size()));
  }
  auto get_index(T x) -> int { make(x); return vertex[x]; }
  auto unite(T x, T y) { return uf.unite(get_index(x), get_index(y)); }
  auto find(T x, T y) { return uf.same(get_index(x), get_index(y)); }
  auto root(T x) { return uf.root(get_index(x)); }
};
#endif
