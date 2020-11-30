// https://en.wikipedia.org/wiki/Bor%C5%AFvka%27s_algorithm
#include <algorithm>
#include <utility>
#include <vector>
#include "union_find.hpp"
#ifndef BORUVKA_HPP
#define BORUVKA_HPP
template <typename T>
struct Boruvka {
  UnionFind uf;
  std::size_t v;
  const T inf;
  explicit Boruvka(std::size_t v, T inf): v(v), uf(v), inf(inf) {}
  auto find(int v) -> int {return uf.find(v);}
  auto update(std::vector<T>& x, std::vector<T>& y, std::vector<T>& z) {
    std::vector<std::pair<T, T>> r(v, std::make_pair(inf, -1));
    for (int i = 0; i < v; ++i) {
      x[i] = find(x[i]); y[i] = find(y[i]); if (x[i] == y[i]) continue;
      r[x[i]] = std::min(r[x[i]], std::make_pair(z[i], y[i]));
      r[y[i]] = std::min(r[y[i]], std::make_pair(z[i], z[i]));
    } return r;
  }
  auto operator ()(std::vector<T>& x, std::vector<T>& y, std::vector<T>& z) {
    T r = T();
    while (-uf.data[find(0)] < v) {
      std::vector<std::pair<T, int>> p(v, std::make_pair(inf, -1));
      p = update(x, y, z); bool b = false;
      for (int i = 0; i < v; ++i)
        if (p[i].second >= 0 && uf.unite(i, p[i].second)) {
          r += p[i].first; b = true;
        }
    } return r;
  }
};
#endif
