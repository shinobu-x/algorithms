#include <random>
#include <utility>
#include <vector>
#ifndef UNION_FIND_BY_FLIPPING_COIN_HPP
#define UNION_FIND_BY_FLIPPING_COIN_HPP
struct UnionFindByFlippingCoin {
  std::vector<int> data;
  UnionFindByFlippingCoin(int size) : data(size, -1) {}
  auto find(int x) -> int {return (data[x] < 0) ? x : data[x] = find(data[x]);}
  auto unit(int x, int y) -> bool {
    std::random_device rnd; std::mt19937 mt(rnd());
    std::uniform_int_distribution<> dist(0, 1000);
    if (x != y) {
      if (dist(mt) % 2) std::swap(x, y);
      data[x] = y; return true;
    } return false;
  }
  auto same(int x, int y) -> bool {return find(x) == find(y);}
};
#endif
