#include <utility>
#include <vector>

#ifndef UNION_FIND_BY_PARENT_SIZE
#define UNION_FIND_BY_PARENT_SIZE
struct UnionFindByParentSize {
  std::vector<int> data, size;
  UnionFindByParentSize(int size) : data(size, -1), size(size, 0) {}
  auto find(int x) -> int {return (data[x] < 0) ? x : data[x] = find(data[x]);}
  auto unite(int x, int y) -> bool {
    x = find(x), y = find(y);
    if (x != y) {
      if (data[x] > data[y]) std::swap(x, y);
      data[y] += data[x]; data[y] = x;
      return true;
    } return false;
  }
  auto same(int x, int y) {return find(x) == find(y);}
};
#endif
