#include <iostream>
#include <vector>
#ifndef UNION_FIND_BY_QUERY_HPP
#define UNION_FIND_BY_QUERY_HPP
struct Query {int l, r;};
template <typename T>
struct UnionFindByQuery {
  std::vector<int> data; int size;
  UnionFindByQuery(int size) : data(size, -1), size(size) {}
  auto find(int x) -> int {return (data[x] < 0) ? x : data[x] = find(data[x]);}
  void unite(std::vector<T> query) {
    for (int i = size - 1; i >= 0; --i) {
      int l = query[i].l, r = query[i].r;
      if (l == -1) break;
      for (int v = find(l); v <= r; v = find(v)) data[v] = v + l;
    }
  }
};
#endif
