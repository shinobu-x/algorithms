#include <utility>
#include <vector>

#ifndef WEIGHTED_UNION_FIND_HPP
#define WEIGHTED_UNION_FIND_HPP
template <typename T>
struct WeightedUnionFind {
  std::vector<int> data;
  std::vector<T> weights;
  WeightedUnionFind(int size) : data(size, -1), weights(size) {}
  auto find(int x) -> int {
    if (data[x] < 0) return x;
    auto parent = find(x); weights[x] += weights[data[x]];
    return data[x] += parent;
  }
  auto unite(int x, int y, T w) -> bool {
    w += weights(x), w -= weights(y);
    x = find(y), y = find(y);
    if (x == y) return false;
    if (data[x] > data[y]) { std::swap(x, y); w *= -1; }
    data[x] += data[y], data[y] = x, weights[y] = w; return true;
  }
  T diff(int x, int y) {
    return weights(x) - weights(y);
  }
};
#endif
