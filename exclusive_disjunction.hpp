#include <algorithm>
#include <iterator>
#include <vector>
#ifndef EXCLUSIVE_DISJUNCTION_HPP
#define EXCLUSIVE_DISJUNCTION_HPP
template <typename T>
struct ExclusiveDisjunction {
  std::vector<T> base; bool update;
  ExclusiveDisjunction() : update(false) {}
  auto add(T bit) -> bool {
    for (auto& exp : base) bit = std::min(bit, bit ^ exp);
    if (bit) {
      base.emplace_back(bit); return update = true;
    } else return false;
  }
  auto check(T bit) -> bool const {
    for (auto& exp : base) bit = std::min(bit, bit ^ exp);
    return bit == 0;
  }
  void normalize() {
    sort();
    for (int i = (int)base.size() - 1; i >= 0; --i)
      for (int j = i - 1; j >= 0; --j)
        chmin(base[i], base[i] ^ base[j]);
  }
  void sort() {
    if (exchange(update, false)) std::sort(std::begin(base), std::end(base));
  }
  auto operator == (ExclusiveDisjunction<T>& a) {
    normalize(), a.normalize(); return base = a.base;
  }
  T get_n(int64_t i) {
    if ((1LL << base.size()) <= i) return -1;
    T r = T(); sort();
    for (int j = (int)base.size() - 1; j >= 0; --j)
      if ( i < (1LL << j)) r = std::min(r, r ^ base[j]);
      else {
        i -= 1LL << j; r = std::max(r, r ^ base[j]);
      } return r;
  }
  auto size() -> std::size_t const { return base.size(); }
};
#endif
