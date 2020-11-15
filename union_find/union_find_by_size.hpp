#include <utility>
#include <vector>
#ifndef UNION_FIND_BY_SIZE_HPP
#define UNION_FIND_BY_SIZE_HPP
struct UnionFindBySize {
  std::vector<int> data, size;
  UnionFindBySize(int size) : data(size, -1), size(size, 0) {}
  auto find(int x) -> int {return (data[x] < 0) ? x : data[x] = find(data[x]);}
  auto unite(int x, int y) -> bool {
    if (x != y) {
      if (size[x] < size[y]) { size[y] += size[x]; data[x] = y; }
      else { size[x] += size[y]; data[y] = x; }
      return true;
    } return false;
  }
  auto same(int x, int y) -> bool {return find(x) == find(y);}
};
#endif
