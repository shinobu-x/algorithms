#include <utility>
#include <vector>

#ifndef UNION_FIND_HPP
#define UNION_FIND_HPP
struct UnionFind {
  std::vector<int> vertex;
  UnionFind(std::size_t size) : vertex(size, -1) {}
  auto root(int index) -> int {
    return (vertex[index] < 0 ? index : vertex[index] = root(vertex[index]));
  }
  auto same(int x, int y) -> bool {
    return root(x) == root(y);
  }
  void unite(int x, int y) {
    x = root(x), y = root(y);
    if (x != y) {
      if (vertex[x] > vertex[y]) std::swap(x, y);
      vertex[x] += vertex[y]; vertex[y] = x;
    }
  }
  auto size(int x) -> int {
    return -vertex[x];
  }
};
#endif
