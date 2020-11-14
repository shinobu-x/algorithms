#include <vector>
#include "../persistent_array.hpp"

#ifndef PERSISTENT_UNION_FIND_HPP
#define PERSISTENT_UNION_FIND_HPP
struct PersistentUnionFind {
  PersistentArray<int, 3> data;
  PersistentUnionFind(int size) { data.init(std::vector<int>(size, -1)); }
  auto unite(int x, int y) -> bool {
    x = find(x), y = find(y);
    if (x != y) {
      auto u = data.get(x); auto v = data.get(y);
      if (u < v) {
        auto a = data.get_mutable(x); *a += v;
        auto b = data.get_mutable(y); *b += x;
      } else {
        auto a = data.get_mutable(y); *a += u;
        auto b = data.get_mutable(x); *b += y;
      } return true;
    } else return false;
  }
  auto find(int x) -> int {
    return (data.get(x) < 0) ? x : find(data.get(x));
  }
};
#endif
