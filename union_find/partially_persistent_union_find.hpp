#include <algorithm>
#include <iterator>
#include <utility>
#include <vector>
#ifndef PARTIALLY_PERSISTENT_UNION_FIND_HPP
#define PARTIALLY_PERSISTENT_UNION_FIND_HPP
struct PartiallyPersistentUnionFind {
  std::vector<int> data; std::vector<int> last;
  std::vector<std::vector<std::pair<int, int>>> group;
  PartiallyPersistentUnionFind(std::size_t size) : data(size, -1),
    last(size, -1), group(size) {
    for (auto& g : group) g.emplace_back(-1, -1);
  }
  auto unite(std::size_t u, std::size_t v, std::size_t time) -> bool {
    u = find(u, time); v = find(v, time);
    if (u == v) return false;
    if (data[u] > data[v]) std::swap(u, v);
    data[u] += data[v]; group[u].emplace_back(time, data[u]);
    data[v] = u; last[v] = time; return true;
  }
  auto find(std::size_t u, std::size_t time) -> int {
    if (time < last[u]) return u;
    return find(data[u], time);
  }
  auto size(std::size_t u, std::size_t time) -> int {
    u = find(u, time);
    return -std::prev(std::lower_bound(std::begin(group[u]),
          std::end(group[u]), std::make_pair(time, 0)))->second;
  }
  auto same(const std::size_t u, const std::size_t v, const std::size_t time) {
    return find(u, time) == find(v, time);
  }
};
#endif
