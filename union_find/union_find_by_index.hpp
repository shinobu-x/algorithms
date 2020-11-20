#include <utility>
#include <vector>
#ifndef UNION_FIND_BY_INDEX_HPP
#define UNION_FIND_BY_INDEX_HPP
struct UnionFindByIndex {
  std::vector<int> data, index;
  UnionFindByIndex(int size) : data(size, -1), index(size, -1) {}
  auto find(int x) -> int {return (data[x] < 0) ? x : data[x] = find(data[x]);}
  auto unite(int x, int y) -> bool {
    x = find(x), y = find(y);
    if (x != y) {
      if (index[x] > index[y]) std::swap(x, y);
      data[x] = y; return true;
    } return false;
  }
  auto same(int x, int y) -> bool {return find(x) == find(y);}
};
#endif
