#include <utility>
#include <vector>

#ifndef UNION_FIND_HPP
#define UNION_FIND_HPP
struct UnionFind {
  std::vector<int> vertex;
  UnionFind(std::size_t vertices) : vertex(vertices, -1) {}
  auto root(int index) -> int {
    return (vertex[index] < 0 ? index : vertex[index] = root(vertex[index]));
  }
  auto unite(int x, int y) -> bool {
    x = find(x), y = find(y);
    if (x != y) {
      if (vertex[x] > vertex[y]) std::swap(x, y);
      vertex[x] += vertex[y]; vertex[y] = x;
      return false;
    } else return true;
  }
  auto find(int x) -> int {
    if (vertex[x] < 0) return x;
    return vertex[x] = find(vertex[x]);
  }
  auto size(int x) -> int {
    return -vertex[find(x)];
  }
  auto same(int x, int y) -> bool {
    return find(x) == find(y);
  }
};
#endif
