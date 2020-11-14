#include <utility>
#include <vector>

#ifndef UNION_FIND_HPP
#define UNION_FIND_HPP
struct UnionFind {
  std::vector<int> data;
  UnionFind(int size) : data(size, -1) {}
  auto find(int x) -> int {return (data[x] < 0) ? x : data[x] = find(data[x]);}
  auto unite(int x, int y) -> bool {
    x = find(x), y = find(y);
    if (x != y) {
      if (data[x] > data[y]) std::swap(x, y);
      data[x] += data[y]; data[y] = x;
      return false;
    } return true;
  }
  auto same(int x, int y) -> bool {return find(x) == find(y);}
};
#endif
