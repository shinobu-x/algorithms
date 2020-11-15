#include <vector>
#ifndef UNION_FIND_BY_RANK_HPP
#define UNION_FIND_BY_RANK_HPP
struct UnionFindByRank {
  std::vector<int> data, rank;
  UnionFindByRank(int size) : data(size, -1), rank(size, 0) {}
  auto find(int x) -> int {return (data[x] < 0) ? x : data[x] = find(data[x]);}
  auto unite(int x, int y) -> bool {
    x = find(x), y = find(y);
    if (x != y) {
      if (rank[x] > rank[y]) data[y] = x;
      else {data[x] = y; if (rank[x] == rank[y]) data[y] += 1;}
      return true;
    } return false;
  }
  auto same(int x, int y) -> bool {return find(x) == find(y);}
};
#endif
